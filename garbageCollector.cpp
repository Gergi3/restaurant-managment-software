#include "garbageCollector.h"
#include "inventoryItem.h"

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