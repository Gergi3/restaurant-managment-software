#pragma once

#include "inventoryItem.h"
#include <fstream>

void addToInventory(InventoryItem item);

void addToInventory(const char const* name, unsigned quantity);

void addToInventory(std::ofstream& ofs, const char const* name, unsigned quantity);

void removeFromInventory(InventoryItem item);

void removeFromInventory(const char const* name);

void mutateInventory(const char const* name, unsigned quantity, bool isDelete = false);

void appendToInventory(const char const* name, unsigned quantity);

bool inventoryItemExists(const char const* name);

InventoryItem* getFromInventory(const char const* name);

InventoryItem** getAllFromInventory();

void setItemValues(std::ifstream& ifs, InventoryItem*& item);
