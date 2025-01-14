#pragma once
#include "inventoryConstants.h"

struct InventoryItem
{
	char name[INVENTORY_CONSTANTS::MAX_NAME_LENGTH + 1];
	unsigned quantity = 0;
};