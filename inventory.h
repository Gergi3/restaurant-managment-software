#pragma once

#include "inventoryItem.h"

void addToInventory(InventoryItem item);

void addToInventory(const char const* name, unsigned quantity);

InventoryItem* getFromInventory(const char const* name);

InventoryItem** getAllFromInventory();

void setItemValues(std::ifstream& ifs, InventoryItem*& item);
