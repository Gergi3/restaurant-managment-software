#include "garbageCollector.h"
#include "generalConstants.h"
#include "inventory.h"
#include "io.h"
#include "menu.h"
#include "menuConstants.h"
#include "order.h"
#include "orderConstants.h"
#include "orderItem.h"
#include "orderValidator.h"
#include "stream.h"
#include "string.h"
#include "validator.h"
#include <fstream>

bool addToOrder(
	const char* const menuItemName,
	int*& failCodes)
{
	bool isValidMenuItem = validateOrderItemMenuItem(menuItemName, failCodes);
	if (!isValidMenuItem)
	{
		return false;
	}

	MenuItem* menuItem = getFromMenu(menuItemName);

	bool isDecreased = decreaseQuantityFromInventoryItems(menuItem->ingredients, failCodes);

	if (!isDecreased)
	{
		return false;
	}

	bool isAdded = appendToOrder(menuItemName);

	if (!isAdded)
	{
		addManyToInventory(menuItem->ingredients, failCodes);
	}

	freeMemory(menuItem);

	return isAdded;
}

void addToOrder(
	std::ofstream& ofs,
	unsigned id,
	const char* const menuItemName)
{
	ofs << id << ';' << menuItemName << std::endl;
}

bool appendToOrder(const char* const menuItemName)
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

bool removeAllOrders()
{
	std::ofstream ofs(ORDER_CONSTANTS::FILE_NAME);
	if (!isValidStream(ofs))
	{
		return false;
	}

	ofs.close();
	return true;
}

bool removeOrder(
	unsigned id,
	int*& failCodes,
	OrderItem** items)
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

	OrderItem* order = getOrder(id);
	MenuItem* menuItem = getFromMenu(order->menuItemName);
	InventoryItem** ingredientsToAdd = menuItem->ingredients;
	freeMemory(order);
	freeMemory(menuItem, false);
	
	std::ofstream ofs(ORDER_CONSTANTS::FILE_NAME);
	if (!isValidStream(ofs))
	{
		return false;
	}

	ofs << currentId << std::endl;

	unsigned indx = 0;
	while (items[indx])
	{
		OrderItem* order = items[indx];

		if (order->id != id)
		{
			addToOrder(ofs, order->id, order->menuItemName);
		}

		indx++;
	}

	ofs.close();

	addManyToInventory(ingredientsToAdd, failCodes);
	freeMemory(ingredientsToAdd);

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
	ifs.peek();
	if (!ifs.good() || ifs.eof())
	{
		ifs.close();
		return nullptr;
	}

	while (!ifs.eof() && ifs.good())
	{
		OrderItem* order = new OrderItem;
		setItemValues(ifs, order);

		if (order->id == id)
		{
			ifs.close();
			return order;
		}

		ifs.peek();
	}

	ifs.close();
	return nullptr;
}

bool orderForMenuItemExists(const char* const menuItemName)
{
	OrderItem** orders = getAllOrders();
	if (!orders)
	{
		return false;
	}

	bool exists = false;
	unsigned indx = 0;
	while (orders[indx])
	{
		OrderItem* order = orders[indx];

		if (!strcmp(order->menuItemName, menuItemName))
		{
			exists = true;
			break;
		}

		indx++;
	}

	freeMemory(orders);

	return exists;
}

bool orderExists(unsigned id)
{
	OrderItem* order = getOrder(id);

	if (!order)
	{
		return false;
	}

	freeMemory(order);
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
		ifs.close();
		return nullptr;
	}

	unsigned itemsCount = getLinesCount(ifs);
	if (itemsCount == 0)
	{
		ifs.close();
		return nullptr;
	}

	OrderItem** orders = new OrderItem * [itemsCount + 1];

	unsigned indx = 0;
	while (indx < itemsCount)
	{
		OrderItem* item = new OrderItem;
		setItemValues(ifs, item);

		orders[indx++] = item;
	}
	orders[indx] = nullptr;

	ifs.close();
	return orders;
}


void setItemValues(
	std::ifstream& ifs,
	OrderItem*& item)
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

	while (items[count])
	{
		count++;
	}

	return count;
}

void sortOrderItems(OrderItem** items)
{
	unsigned count = getItemsCount(items);

	unsigned end = count - 1;
	for (unsigned i = 0; i < end; i++)
	{
		unsigned innerEnd = count - i - 1;
		for (unsigned j = 0; j < innerEnd; j++)
		{
			char* currentMenuItemName = items[j]->menuItemName;
			char* nextMenuItemName = items[j + 1]->menuItemName;
			if (strcmp(currentMenuItemName, nextMenuItemName) > 0)
			{
				OrderItem* temp = items[j];
				items[j] = items[j + 1];
				items[j + 1] = temp;
			}
		}
	}
}

void displayOrderItems(
	OrderItem** items,
	bool withCount)
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

		bool nextItemIsSame = nextItem && !strcmp(item->menuItemName, nextItem->menuItemName);
		bool shouldIncrementCount = withCount && nextItem && nextItemIsSame;
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

void displayOrderItem(
	OrderItem* item,
	bool withCount)
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