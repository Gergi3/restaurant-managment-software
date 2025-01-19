#include "date.h"
#include "dateConstants.h"
#include "garbageCollector.h"
#include "generalConstants.h"
#include "io.h"
#include "menu.h"
#include "order.h"
#include "revenue.h"
#include "stream.h"
#include "validator.h"

unsigned getCurrentRevenue()
{
	OrderItem** orders = getAllOrders();
	if (!orders)
	{
		return 0;
	}

	unsigned revenue = 0;

	unsigned indx = 0;
	while (orders[indx])
	{
		OrderItem* order = orders[indx];
		MenuItem* menuItem = getFromMenu(order->menuItemName);
		if (menuItem)
		{
			revenue += menuItem->price;
			freeMemory(menuItem);
		}

		indx++;
	}

	freeMemory(orders);

	return revenue;
}

bool displayRevenueFromDateToNow(char* date, int*& failCodes)
{
	bool valid = isValidDate(date);
	if (!valid)
	{
		addFailCode(REVENUE_CONSTANTS::INVALID_REVENUE_DATE_FAIL_CODE, failCodes);
		return false;
	}

	char* currentDate = getDate();
	
	bool isInPast = isBefore(date, currentDate);
	if (!isInPast)
	{
		addFailCode(REVENUE_CONSTANTS::FUTURE_REVENUE_DATE_FAIL_CODE, failCodes);
		return false;
	}

	std::ifstream ifs(REVENUE_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return false;
	}

	bool shouldPrint = false;

	char dateBuffer[DATE_CONSTANTS::DATE_LENGTH + 1]{};
	unsigned revenue = 0;
	while (!ifs.eof() && ifs.good())
	{
		ifs.getline(dateBuffer, DATE_CONSTANTS::DATE_LENGTH + 1, ';');
		ifs >> revenue;
		ifs.ignore();

		if (!shouldPrint && isBefore(date, dateBuffer))
		{
			shouldPrint = true;
		}

		if (shouldPrint)
		{
			displayRevenue(revenue, dateBuffer);
		}

		ifs.peek();
	}

	ifs.close();
	
	displayCurrentRevenue();

	return true;
}

bool endCurrentRevenue()
{
	unsigned revenue = getCurrentRevenue();
	bool ordersAreRemoved = removeAllOrders();

	if (!ordersAreRemoved)
	{
		return false;
	}

	std::ofstream ofs(REVENUE_CONSTANTS::FILE_NAME, std::ios::app);
	if (!isValidStream(ofs))
	{
		return false;
	}

	saveRevenue(ofs, revenue, getDate());
	ofs.close();

	incrementDate();

	return true;
}

void saveRevenue(std::ofstream& ofs, unsigned revenue, const char* const date)
{
	ofs << date << ';' << revenue << std::endl;
}

void displayCurrentRevenue()
{
	unsigned revenue = getCurrentRevenue();
	char* date = getDate();
	
	displayRevenue(revenue, date);
}

void displayRevenue(unsigned revenue, const char* const date)
{
	print(date, 0);
	print(" - $", 0);
	print(revenue);
}