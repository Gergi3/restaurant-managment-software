#pragma once
#include "inventoryItem.h"

bool validateInventoryItem(
	InventoryItem item,
	int*& failCodes);

bool validateInventoryItem(
	const char* const name,
	unsigned quantity,
	int*& failCodes);

bool validateInventoryItemName(
	const char* const name,
	int*& failCodes);

bool validateInventoryItemName(const char* const name);

bool validateInventoryItemQuantity(
	unsigned quantity,
	int*& failCodes);

bool validateInventoryItemQuantity(unsigned quantity);

void displayInventoryItemFailCodeMessage(int failCode);