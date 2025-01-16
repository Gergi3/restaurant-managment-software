#pragma once

bool validateMenuItem(const char const* name, unsigned price, unsigned ingredientsCount, int*& failCodes);

bool validateMenuItemName(const char const* name);

bool validateMenuItemName(const char const* name, int*& failCodes);

bool validateMenuItemPrice(unsigned price);

bool validateMenuItemPrice(unsigned price, int*& failCodes);

bool validateMenuItemIngredientsCount(unsigned count);

bool validateMenuItemIngredientsCount(unsigned count, int*& failCodes);

void displayMenuItemFailCodeMessage(int failCode);
