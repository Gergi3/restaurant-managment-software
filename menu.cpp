#include "garbageCollector.h"
#include "inventory.h"
#include "inventoryConstants.h"
#include "inventoryItem.h"
#include "io.h"
#include "menu.h"
#include "menuConstants.h";
#include "menuItem.h"
#include "misc.h"
#include "stream.h"
#include "string.h"
#include "validator.h"
#include <fstream>
#include <iostream>

bool addToMenu(
	MenuItem* item,
	int*& failCodes)
{
	bool exists = menuItemExists(item->name);

	if (exists)
	{
		addFailCode(MENU_CONSTANTS::ADD_FAIL_CODE, failCodes);
		return false;
	}

	appendToMenu(item);

	return true;
}

void addToMenu(
	std::ofstream& ofs,
	MenuItem* item)
{
	ofs << item->name << ';' << item->price << std::endl;

	InventoryItem** ingredients = item->ingredients;

	if (!ingredients)
	{
		return;
	}

	unsigned indx = 0;
	while (ingredients[indx])
	{
		InventoryItem* ingredient = ingredients[indx];

		ofs << ingredient->name << '=' << ingredient->quantity << ';';

		indx++;
	}
	ofs << std::endl;
}

bool appendToMenu(MenuItem* item)
{
	std::ofstream ofs(MENU_CONSTANTS::FILE_NAME, std::ios::app);
	if (!isValidStream(ofs))
	{
		return false;
	}

	addToMenu(ofs, item);

	ofs.close();

	return true;
}

bool removeFromMenu(
	MenuItem* item,
	int*& failCodes)
{
	return removeFromMenu(item->name, failCodes);
}

bool removeFromMenu(
	const char const* name,
	int*& failCodes)
{
	bool exists = menuItemExists(name);

	if (!exists)
	{
		addFailCode(MENU_CONSTANTS::REMOVAL_FAIL_CODE, failCodes);
		return false;
	}

	MenuItem** items = getAllFromMenu();
	if (!items)
	{
		return false;
	}

	std::ofstream ofs(INVENTORY_CONSTANTS::FILE_NAME);
	if (!isValidStream(ofs))
	{
		return false;
	}

	unsigned indx = 0;
	while (items[indx])
	{
		MenuItem* item = items[indx++];

		if (strcmp(item->name, name))
		{
			addToMenu(ofs, item);
		}
	}

	ofs.close();

	freeMemory(items);
	return true;
}

MenuItem* getFromMenu(const char const* name)
{
	std::ifstream ifs(MENU_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	MenuItem* item = new MenuItem;

	while (!ifs.eof() && ifs.good())
	{
		setItemValues(ifs, item);
		if (!strcmp(item->name, name))
		{
			ifs.close();
			return item;
		}

		freeMemory(item->ingredients);
		ifs.peek();
	}

	ifs.close();

	freeMemory(item, false);
	return nullptr;
}

bool menuItemExists(const char const* name)
{
	MenuItem* item = getFromMenu(name);

	if (!item)
	{
		return false;
	}

	freeMemory(item);
	return true;
}

MenuItem** getAllFromMenu()
{
	std::ifstream ifs(MENU_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	unsigned itemsCount = getLinesCount(ifs) / 2;
	if (itemsCount == 0)
	{
		return nullptr;
	}

	MenuItem** items = new MenuItem * [itemsCount + 1];

	unsigned itemsIndx = 0;
	while (itemsIndx < itemsCount)
	{
		MenuItem* item = new MenuItem;
		setItemValues(ifs, item);

		items[itemsIndx++] = item;
	}
	items[itemsIndx] = nullptr;

	return items;
}


void setItemValues(
	std::ifstream& ifs,
	MenuItem*& item)
{
	ifs.getline(item->name, MENU_CONSTANTS::MAX_NAME_LENGTH, ';');

	char priceStr[MENU_CONSTANTS::MAX_PRICE_DIGITS_COUNT + 1]{};
	ifs.getline(priceStr, MENU_CONSTANTS::MAX_PRICE_DIGITS_COUNT + 1, '\n');
	item->price = strToUnsigned(priceStr);

	unsigned ingredientsCount = getCharCountCurrentLine(ifs, ';');
	item->ingredients = new InventoryItem * [ingredientsCount + 1];

	unsigned indx = 0;
	while (indx < ingredientsCount)
	{
		InventoryItem* currentIngredient = new InventoryItem;

		ifs.getline(currentIngredient->name, INVENTORY_CONSTANTS::MAX_NAME_LENGTH, '=');

		char quantityStr[INVENTORY_CONSTANTS::MAX_QUANTITY_DIGITS_COUNT + 1]{};
		ifs.getline(quantityStr, INVENTORY_CONSTANTS::MAX_QUANTITY_DIGITS_COUNT, ';');
		currentIngredient->quantity = strToUnsigned(quantityStr);

		item->ingredients[indx++] = currentIngredient;
	}
	item->ingredients[indx] = nullptr;

	ifs.ignore();
}

void displayMenuItems(
	MenuItem** items,
	bool showIngredients)
{
	if (!items)
	{
		return;
	}

	unsigned indx = 0;
	while (items[indx])
	{
		MenuItem* item = items[indx];

		displayMenuItem(item, showIngredients);

		if (items[indx + 1] != nullptr)
		{
			printNewLine();
		}

		indx++;
	}
}

void displayMenuItem(
	MenuItem* item,
	bool showIngredients)
{
	if (!item)
	{
		return;
	}

	print(item->name, 0);
	print(" - $", 0);
	print(item->price);

	if (showIngredients)
	{
		displayInventoryItems(item->ingredients, 2);
	}
}