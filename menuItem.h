#pragma once
#include "inventoryItem.h"
#include "menuConstants.h"

struct MenuItem
{
	char name[MENU_CONSTANTS::MAX_NAME_LENGTH + 1];
	unsigned price = 0;
	InventoryItem** ingredients;
};