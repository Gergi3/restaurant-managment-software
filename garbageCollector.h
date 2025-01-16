#pragma once
#include "inventoryItem.h"
#include "menuItem.h"
#include "orderItem.h"

void freeMemory(InventoryItem** items, bool freeItems = true);

void freeMemory(InventoryItem* item);

void freeMemory(int* nums);

void freeMemory(char* str);

void freeMemory(MenuItem* item, bool freeIngredients = true);

void freeMemory(MenuItem** items, bool freeMenuItems = true, bool freeIngredients = true);

void freeMemory(OrderItem* item);

void freeMemory(OrderItem** items);
