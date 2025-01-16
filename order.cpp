#include "generalConstants.h";
#include "io.h"
#include "menu.h";
#include "menuConstants.h";
#include "order.h"
#include "orderConstants.h"
#include "orderItem.h"
#include "orderValidator.h"
#include "stream.h"
#include "string.h"
#include <fstream>
#include "garbageCollector.h"
#include "validator.h"

bool addToOrder(OrderItem* item, int*& failCodes)
{
	if (!item)
	{
		return false;
	}

	return addToOrder(item->menuItemName, failCodes);
}

bool addToOrder(const char const* menuItemName, int*& failCodes)
{
	bool isValidMenuItem = validateOrderItemMenuItem(menuItemName, failCodes);

	if (!isValidMenuItem)
	{
		return false;
	}

	return appendToOrder(menuItemName);
}

void addToOrder(std::ofstream& ofs, unsigned id, const char const* menuItemName)
{
	ofs << id << ';' << menuItemName << std::endl;
}

bool appendToOrder(const char const* menuItemName)
{
	unsigned nextId = getAndIncrementNextId();

	std::ofstream ofs(ORDER_CONSTANTS::FILE_NAME, std::ios::app);
	if (!isValidStream(ofs))
	{
		return false;
	}

	addToOrder(ofs, nextId, menuItemName);

	ofs.close();

	return true;
}

bool removeOrder(unsigned id, int*& failCodes, OrderItem** items)
{
	bool exists = orderExists(id);

	if (!exists)
	{
		addFailCode(ORDER_CONSTANTS::REMOVAL_FAIL_CODE, failCodes);
		return false;
	}

	if (!items)
	{
		items = getAllOrders();
	}
	unsigned currentId = getCurrentId();

	std::ofstream ofs(ORDER_CONSTANTS::FILE_NAME);
	if (!isValidStream(ofs))
	{
		return false;
	}

	ofs << currentId << std::endl;

	unsigned indx = 0;
	while (items[indx])
	{
		OrderItem* item = items[indx];
		if (item->id != id)
		{
			addToOrder(ofs, item->id, item->menuItemName);
		}

		indx++;
	}

	ofs.close();

	return true;

}

OrderItem* getOrder(unsigned id)
{
	std::ifstream ifs(ORDER_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	ifs.ignore(GENERAL_CONSTANTS::INPUT_BUFFER_SIZE, '\n');
	if (!ifs.good())
	{
		return nullptr;
	}

	while (!ifs.eof() && ifs.good())
	{
		OrderItem* item = new OrderItem;
		setItemValues(ifs, item);

		if (item->id == id)
		{
			return item;
		}

		ifs.peek();
	}

	ifs.close();

	return nullptr;
}

bool orderExists(unsigned id)
{
	OrderItem* item = getOrder(id);

	if (!item)
	{
		return false;
	}

	freeMemory(item);
	return true;
}

OrderItem** getAllOrders()
{
	std::ifstream ifs(ORDER_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	ifs.ignore(GENERAL_CONSTANTS::INPUT_BUFFER_SIZE, '\n');
	ifs.peek();
	if (!ifs.good() || ifs.eof())
	{
		return nullptr;
	}

	unsigned itemsCount = getLinesCount(ifs);
	OrderItem** items = new OrderItem * [itemsCount + 1];

	unsigned itemsIndx = 0;
	while (itemsIndx < itemsCount)
	{
		OrderItem* item = new OrderItem;
		setItemValues(ifs, item);

		items[itemsIndx++] = item;
	}
	items[itemsIndx] = nullptr;

	return items;
}


void setItemValues(std::ifstream& ifs, OrderItem*& item)
{
	char idBuffer[GENERAL_CONSTANTS::MAX_UINT_DIGITS_COUNT + 1]{};
	ifs.getline(idBuffer, GENERAL_CONSTANTS::MAX_UINT_DIGITS_COUNT + 1, ';');
	item->id = strToUnsigned(idBuffer);

	ifs.getline(item->menuItemName, MENU_CONSTANTS::MAX_NAME_LENGTH + 1, '\n');
}

unsigned getAndIncrementNextId()
{
	unsigned currentId = getCurrentId();
	unsigned nextId = currentId + 1;

	std::ofstream ofs(ORDER_CONSTANTS::FILE_NAME, std::ios::out | std::ios::in);
	if (!isValidStream(ofs))
	{
		return 0;
	}

	ofs << nextId;

	if (currentId == 0)
	{
		ofs << std::endl;
	}

	ofs.close();

	return nextId;
}

unsigned getCurrentId()
{
	std::ifstream ifs(ORDER_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return 0;
	}

	unsigned id = 0;
	ifs >> id;

	ifs.close();

	return id;
}

unsigned getItemsCount(OrderItem** items)
{
	unsigned count = 0;
	unsigned indx = 0;

	while (items[indx])
	{
		indx++;
		count++;
	}

	return count;
}

void sortOrderItems(OrderItem** items)
{
	unsigned count = getItemsCount(items);

	for (int i = 0; i < count - 1; ++i)
	{
		for (int j = 0; j < count - i - 1; ++j)
		{
			if (strcmp(items[j]->menuItemName, items[j + 1]->menuItemName) > 0)
			{
				OrderItem* temp = items[j];
				items[j] = items[j + 1];
				items[j + 1] = temp;
			}
		}
	}
}

void displayOrderItems(OrderItem** items, bool withCount)
{
	if (!items)
	{
		return;
	}

	if (withCount)
	{
		sortOrderItems(items);
	}

	unsigned count = 1;

	unsigned indx = 0;
	while (items[indx])
	{
		OrderItem* item = items[indx];
		OrderItem* nextItem = items[indx + 1];

		bool nextItemIsSameAsCurrent = nextItem
			&& !strcmp(item->menuItemName, nextItem->menuItemName);

		bool shouldIncrementCount = withCount && nextItem && nextItemIsSameAsCurrent;

		if (shouldIncrementCount)
		{
			count++;
			indx++;
			continue;
		}

		if (withCount)
		{
			print(count, 0);
			print(" - ", 0);
		}

		displayOrderItem(item, withCount);

		if (nextItem)
		{
			printNewLine();
		}

		indx++;
	}
}

void displayOrderItem(OrderItem* item, bool withCount)
{
	if (!item)
	{
		return;
	}

	print(item->menuItemName, 0);
	
	if (withCount)
	{
		printNewLine();
		return;
	}
	
	print(" (ID: ", 0);
	print(item->id, 0);
	print(")");
}