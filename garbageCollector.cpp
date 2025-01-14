#include "garbageCollector.h"
#include "inventoryItem.h"

void free(InventoryItem** items)
{
	unsigned indx = 0;
	while (items[indx])
	{
		free(items[indx]);
		indx++;
	}

	delete[] items;
	items = nullptr;
}

void free(InventoryItem* item)
{
	delete item;
	item = nullptr;
}