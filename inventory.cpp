#include "garbageCollector.h"
#include "inventory.h";
#include "inventoryItem.h"
#include "inventoryValidator.h"
#include "io.h"
#include "stream.h"
#include "string.h";
#include "validator.h"
#include <fstream>

bool addToInventory(InventoryItem item, int*& failCodes)
{
	return addToInventory(item.name, item.quantity, failCodes);
}

bool addToInventory(const char const* name, unsigned quantity, int*& failCodes)
{
	bool isValid = validateInventoryItem(name, quantity, failCodes);

	if (!isValid)
	{
		return false;
	}

	inventoryItemExists(name)
		? mutateInventory(name, quantity)
		: appendToInventory(name, quantity);

	return true;
}

void addToInventory(std::ofstream& ofs, const char const* name, unsigned quantity)
{
	ofs << name << ';' << quantity << std::endl;
}

bool removeFromInventory(InventoryItem item, int*& failCodes)
{
	return removeFromInventory(item.name, failCodes);
}

bool removeFromInventory(const char const* name, int*& failCodes)
{
	bool itemExists = inventoryItemExists(name);

	if (!itemExists)
	{
		addFailCode(INVENTORY_CONSTANTS::REMOVAL_FAIL_CODE, failCodes);
		return false;
	}

	mutateInventory(name, 0, true);
}

void mutateInventory(const char const* name, unsigned quantity, bool isDelete)
{
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
			addToInventory(ofs, item->name, item->quantity);
		}
	}

	freeMemory(items);

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

InventoryItem* getFromInventory(const char const* name, InventoryItem** items)
{
	unsigned indx = 0;

	while (items[indx])
	{
		InventoryItem* item = items[indx];

		if (!strcmp(item->name, name))
		{
			return item;
		}

		indx++;
	}

	return nullptr;
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

	while (!ifs.eof() && ifs.good())
	{
		setItemValues(ifs, item);

		if (!strcmp(item->name, name))
		{
			isFetched = true;
			break;
		}

		ifs.peek();
	}

	ifs.close();

	if (isFetched)
	{
		return item;
	}
	else
	{
		freeMemory(item);
		return nullptr;
	}
}

bool inventoryItemExists(const char const* name)
{
	InventoryItem* item = getFromInventory(name);

	bool exists = item != nullptr;

	freeMemory(item);

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
	ifs.getline(item->name, INVENTORY_CONSTANTS::MAX_NAME_LENGTH, ';');
	ifs >> item->quantity;
	ifs.ignore();
}

void displayInventoryItems(InventoryItem** items, unsigned indent, char indentCh)
{
	if (!items)
	{
		return;
	}

	unsigned indx = 0;
	while (items[indx])
	{
		displayInventoryItem(items[indx], indent, indentCh);

		indx++;
	}
}

void displayInventoryItem(InventoryItem* item, unsigned indent, char indentCh)
{
	while (indent)
	{
		print(indentCh, 0);
		indent--;
	}
	print(item->name, 0);
	print(" - ", 0);
	print(item->quantity, 0);
	print("g.");

}