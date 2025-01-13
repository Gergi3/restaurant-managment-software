#include <fstream>
#include "stream.h"
#include "inventory.h";
#include "inventoryItem.h"

void addToInventory(InventoryItem item)
{
	addToInventory(item.name, item.quantity);
}

void addToInventory(const char const* name, unsigned quantity)
{
	InventoryItem** items = getAllFromInventory();
	unsigned indx = 0;

	std::ofstream ofs("inventory.txt");
	if (!isValidStream(ofs))
	{
		return;
	}

	bool exists = false;
	while (items[indx])
	{
		InventoryItem* item = items[indx];

		if (!strcmp(item->name, name))
		{
			item->quantity += quantity;
			exists = true;
		}
		ofs << item->name << ';' << item->quantity << std::endl;
		
		delete[] item;
		item = nullptr;

		indx++;
	}
	delete[] items;
	items = nullptr;

	if (!exists)
	{
		ofs << name << ';' << quantity << std::endl;
	}

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
