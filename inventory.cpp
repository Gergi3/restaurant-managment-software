#include "garbageCollector.h"
#include "inventory.h"
#include "inventoryConstants.h"
#include "inventoryItem.h"
#include "inventoryValidator.h"
#include "io.h"
#include "stream.h"
#include "validator.h"
#include <fstream>

bool addToInventory(
	const char* const name,
	unsigned quantity,
	int*& failCodes)
{
	bool isValid = validateInventoryItem(name, quantity, failCodes);
	if (!isValid)
	{
		return false;
	}

	bool exists = inventoryItemExists(name);
	if (exists)
	{
		return mutateInventory(name, quantity);
	}

	return appendToInventory(name, quantity);
}

void addToInventory(
	std::ofstream& ofs,
	const char* const name,
	unsigned quantity)
{
	ofs << name << ';' << quantity << std::endl;
}

void addManyToInventory(InventoryItem** items, int*& failCodes)
{
	if (!items)
	{
		return;
	}

	unsigned indx = 0;
	while (items[indx])
	{
		InventoryItem* item = items[indx];

		addToInventory(item->name, item->quantity, failCodes);

		indx++;
	}
}

bool removeFromInventory(
	const char* const name,
	int*& failCodes)
{
	bool exists = inventoryItemExists(name);
	if (!exists)
	{
		addFailCode(INVENTORY_CONSTANTS::REMOVAL_FAIL_CODE, failCodes);
		return false;
	}

	return mutateInventory(name, 0, true);
}

bool canDecreaseQuantityFromInventoryItems(
	InventoryItem** items,
	int*& failCodes)
{
	if (!items)
	{
		return false;
	}

	unsigned indx = 0;
	while (items[indx])
	{
		InventoryItem* item = items[indx];

		bool canDecreaseCurrent = canDecreaseQuantityFromInventoryItem(item->name, item->quantity, failCodes);

		if (!canDecreaseCurrent)
		{
			return false;
		}

		indx++;
	}

	return true;
}

bool canDecreaseQuantityFromInventoryItem(
	const char* const name,
	unsigned quantity,
	int*& failCodes)
{
	bool exists = inventoryItemExists(name);
	if (!exists)
	{
		addFailCode(INVENTORY_CONSTANTS::QUANTITY_DECREASE_NOT_FOUND_FAIL_CODE, failCodes);
		return false;
	}

	bool canBeDecreased = mutateInventory(name, -(int)quantity, false, true);

	if (!canBeDecreased)
	{
		addFailCode(INVENTORY_CONSTANTS::QUANTITY_DECREASE_FAIL_CODE, failCodes);
		return false;
	}

	return canBeDecreased;
}

bool decreaseQuantityFromInventoryItem(
	const char* const name,
	unsigned quantity,
	int*& failCodes)
{
	bool exists = inventoryItemExists(name);
	if (!exists)
	{
		addFailCode(INVENTORY_CONSTANTS::QUANTITY_DECREASE_NOT_FOUND_FAIL_CODE, failCodes);
		return false;
	}

	return mutateInventory(name, -(int)quantity);
}

bool decreaseQuantityFromInventoryItems(
	InventoryItem** items,
	int*& failCodes)
{
	if (!items)
	{
		return false;
	}

	bool inventoryIsSufficient = canDecreaseQuantityFromInventoryItems(items, failCodes);
	if (!inventoryIsSufficient)
	{
		return false;
	}

	unsigned indx = 0;
	while (items[indx])
	{
		InventoryItem* item = items[indx];

		decreaseQuantityFromInventoryItem(item->name, item->quantity, failCodes);

		indx++;
	}

	return true;
}

bool mutateInventory(
	const char* const name,
	int quantity,
	bool isDelete,
	bool skipMutation)
{
	InventoryItem** items = getAllFromInventory();
	if (!items)
	{
		return false;
	}

	std::ofstream ofs(INVENTORY_CONSTANTS::FILE_NAME);
	if (!isValidStream(ofs))
	{
		return false;
	}

	bool success = true;

	unsigned indx = 0;
	while (items[indx])
	{
		InventoryItem* item = items[indx];

		bool isCurrentItem = !strcmp(item->name, name);

		bool newQuantityIsNegative = ((int)item->quantity + quantity) < 0;
		if (isCurrentItem && newQuantityIsNegative && skipMutation)
		{
			success = false;
		}

		if (isCurrentItem && !skipMutation)
		{
			if (newQuantityIsNegative || isDelete)
			{
				item->quantity = 0;
			}
			else
			{
				item->quantity += quantity;
			}
		}

		addToInventory(ofs, item->name, item->quantity);

		indx++;
	}

	freeMemory(items);

	ofs.close();

	return success;
}

bool appendToInventory(
	const char* const name,
	unsigned quantity)
{
	std::ofstream ofs(INVENTORY_CONSTANTS::FILE_NAME, std::ios::app);
	if (!isValidStream(ofs))
	{
		return false;
	}

	addToInventory(ofs, name, quantity);

	ofs.close();

	return true;
}

InventoryItem* getFromInventory(
	const char* const name,
	InventoryItem** items)
{
	if (!items)
	{
		return nullptr;
	}

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

InventoryItem* getFromInventory(const char* const name)
{
	std::ifstream ifs(INVENTORY_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	InventoryItem* item = new InventoryItem;

	while (!ifs.eof() && ifs.good())
	{
		setItemValues(ifs, item);

		if (!strcmp(item->name, name))
		{
			ifs.close();
			return item;
		}

		ifs.peek();
	}

	ifs.close();

	freeMemory(item);
	return nullptr;
}

bool inventoryItemExists(const char* const name)
{
	InventoryItem* item = getFromInventory(name);
	if (!item)
	{
		return false;
	}

	freeMemory(item);
	return true;
}

InventoryItem** getAllFromInventory()
{
	std::ifstream ifs(INVENTORY_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	unsigned itemsCount = getLinesCount(ifs);
	if (itemsCount == 0)
	{
		ifs.close();
		return nullptr;
	}

	InventoryItem** items = new InventoryItem * [itemsCount + 1];

	unsigned itemsIndx = 0;
	while (itemsIndx < itemsCount)
	{
		InventoryItem* item = new InventoryItem;
		setItemValues(ifs, item);

		items[itemsIndx] = item;
		itemsIndx++;
	}
	items[itemsIndx] = nullptr;

	ifs.close();
	return items;
}

unsigned getInventoryCount(InventoryItem** items)
{
	if (!items)
	{
		return 0;
	}
	
	unsigned count = 0;
	while (items[count])
	{
		count++;
	}

	return count;
}

void setItemValues(
	std::ifstream& ifs,
	InventoryItem*& item)
{
	ifs.getline(item->name, INVENTORY_CONSTANTS::MAX_NAME_LENGTH, ';');
	ifs >> item->quantity;
	ifs.ignore();
}

void displayInventoryItems(
	InventoryItem** items,
	unsigned indent,
	char indentCh)
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

void displayInventoryItem(
	InventoryItem* item,
	unsigned indent,
	char indentCh)
{
	if (!item)
	{
		return;
	}

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