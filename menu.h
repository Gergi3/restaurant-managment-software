#pragma once
#include "menuItem.h"
#include <fstream>

bool addToMenu(
	MenuItem* item,
	int*& failCodes);

void addToMenu(
	std::ofstream& ofs,
	MenuItem* item);

bool appendToMenu(MenuItem* item);

bool removeFromMenu(
	MenuItem* item,
	int*& failCodes);

bool removeFromMenu(
	const char* const name,
	int*& failCodes);

MenuItem* getFromMenu(const char* const name);

bool menuItemExists(const char* const name);

void setItemValues(
	std::ifstream& ifs,
	MenuItem*& item);

MenuItem** getAllFromMenu();

void displayMenuItems(
	MenuItem** items,
	bool showIngredients = true);

void displayMenuItem(
	MenuItem* item,
	bool showIngredients = true);