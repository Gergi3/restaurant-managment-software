#include <fstream>
#include "stream.h"
#include "inventory.h";
#include "inventoryItem.h"
#include "garbageCollector.h"

void addToInventory(InventoryItem item)
{
	addToInventory(item.name, item.quantity);
}

void addToInventory(const char const* name, unsigned quantity)
{
	mutateInventory(name, quantity);
}

void addToInventory(std::ofstream& ofs, const char const* name, unsigned quantity)
{
	ofs << name << ';' << quantity << std::endl;
}

void removeFromInventory(InventoryItem item)
{
	removeFromInventory(item.name);
}

void removeFromInventory(const char const* name)
{
	mutateInventory(name, 0, true);
}

void mutateInventory(const char const* name, unsigned quantity, bool isDelete)
{
	bool itemExists = inventoryItemExists(name);
	if (!itemExists && !isDelete)
	{
		appendToInventory(name, quantity);
		return;
	}
	else if (!itemExists && isDelete)
	{
		return;
	}

	InventoryItem** items = getAllFromInventory();

	std::ofstream ofs("inventory.txt");
	if (!isValidStream(ofs))
	{
		return;
	}
	
	unsigned indx = 0;
	while (items[indx])
	{
		InventoryItem* item = items[indx++];

		bool toFindIsCurrentItem = !strcmp(item->name, name);
		bool shouldOutputCurrentItem = !(toFindIsCurrentItem && isDelete);
		
		if (toFindIsCurrentItem)
		{
			item->quantity += quantity;
		}

		if (shouldOutputCurrentItem)
		{
			addToInventory(item->name, item->quantity);
		}
	}

	free(items);

	ofs.close();
}

void appendToInventory(const char const* name, unsigned quantity)
{
	std::ofstream ofs("inventory.txt", std::ios::app);
	if (!isValidStream(ofs))
	{
		return;
	}

	addToInventory(ofs, name, quantity);

	ofs.close();
}

InventoryItem* getFromInventory(const char const* name)
{
	std::ifstream ifs("inventory.txt");
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	bool isFetched = false;

	InventoryItem* item = new InventoryItem;

	while (!ifs.eof())
	{
		setItemValues(ifs, item);

		if (!strcmp(item->name, name))
		{
			isFetched = true;
			break;
		}
	}

	ifs.close();

	return isFetched ? item : nullptr;
}

bool inventoryItemExists(const char const* name)
{
	InventoryItem* item = getFromInventory(name);

	bool exists = item != nullptr;

	free(item);

	return exists;
}

InventoryItem** getAllFromInventory()
{
	std::ifstream ifs("inventory.txt");
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	unsigned itemsCount = getLinesCount(ifs) + 1;
	InventoryItem** items = new InventoryItem * [itemsCount];

	unsigned itemsIndx = 0;
	while (itemsIndx != itemsCount - 1)
	{
		InventoryItem* item = new InventoryItem;
		setItemValues(ifs, item);

		items[itemsIndx++] = item;
	}
	items[itemsIndx] = nullptr;

	return items;
}

void setItemValues(std::ifstream& ifs, InventoryItem*& item)
{
	ifs.getline(item->name, MAX_INVENTORY_NAME_SIZE, ';');
	ifs >> item->quantity;
	ifs.ignore();
}
