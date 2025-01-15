#pragma once
#include "inventoryItem.h"

void freeMemory(InventoryItem** items, bool freeItems = true);

void freeMemory(InventoryItem* item);

void freeMemory(int* nums);