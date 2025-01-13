#pragma once

const unsigned MAX_INVENTORY_NAME_SIZE = 32;

struct InventoryItem
{
	char name[MAX_INVENTORY_NAME_SIZE];
	unsigned quantity = 0;
};