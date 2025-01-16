#include "garbageCollector.h"
#include "inventoryItem.h"
#include "menuItem.h"
#include "orderItem.h"

void freeMemory(InventoryItem** items, bool freeItems)
{
	if (freeItems)
	{
		unsigned indx = 0;
		while (items[indx])
		{
			freeMemory(items[indx]);
			indx++;
		}
	}

	delete[] items;
	items = nullptr;
}

void freeMemory(InventoryItem* item)
{
	delete item;
	item = nullptr;
}

void freeMemory(int* nums)
{
	delete[] nums;
	nums = nullptr;
}

void freeMemory(char* str)
{
	delete str;
	str = nullptr;
}

void freeMemory(MenuItem* item, bool freeIngredients)
{
	if (freeIngredients)
	{
		freeMemory(item->ingredients);
	}
	
	delete item;
	item = nullptr;
}

void freeMemory(MenuItem** items, bool freeMenuItems, bool freeIngredients)
{
	if (freeMenuItems)
	{
		unsigned indx = 0;
		while (items[indx])
		{
			freeMemory(items[indx], freeIngredients);
			indx++;
		}
	}

	delete[] items;
	items = nullptr;
}

void freeMemory(OrderItem* item)
{
	delete item;
	item = nullptr;
}

void freeMemory(OrderItem** items)
{
	unsigned indx = 0;
	while (items[indx])
	{
		freeMemory(items[indx]);
		indx++;
	}

	delete[] items;
	items = nullptr;
}