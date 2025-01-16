#pragma once
#include "inventoryItem.h"
#include <fstream>

bool addToInventory(
	const char* const name,
	unsigned quantity,
	int*& failCodes);

void addToInventory(
	std::ofstream& ofs,
	const char* const name,
	unsigned quantity);

bool removeFromInventory(
	const char* const name,
	int*& failCodes);

bool mutateInventory(
	const char* const name,
	unsigned quantity,
	bool isDelete = false);

bool appendToInventory(
	const char* const name,
	unsigned quantity);

bool inventoryItemExists(const char* const name);

InventoryItem* getFromInventory(
	const char* const name,
	InventoryItem** items);

InventoryItem* getFromInventory(const char* const name);

InventoryItem** getAllFromInventory();

void setItemValues(
	std::ifstream& ifs,
	InventoryItem*& item);

void displayInventoryItems(
	InventoryItem** items,
	unsigned indent = 0,
	char indentCh = ' ');

void displayInventoryItem(
	InventoryItem* item,
	unsigned indent = 0,
	char indentCh = ' ');
