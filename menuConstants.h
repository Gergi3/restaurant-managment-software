#pragma once
#include "inventoryConstants.h"

namespace MENU_CONSTANTS
{
	constexpr char const* FILE_NAME = "menu.txt";

	constexpr unsigned MIN_NAME_LENGTH = 3;
	constexpr unsigned MAX_NAME_LENGTH = 100;

	constexpr unsigned MIN_PRICE = 1;
	constexpr unsigned MAX_PRICE = 1000; // DEPENDANT ON MAX_PRICE_DIGITS_COUNT
	constexpr unsigned MAX_PRICE_DIGITS_COUNT = 4; // DEPENDANT ON MAX_PRICE

	constexpr unsigned MIN_INGREDIENTS_COUNT = 1;
	constexpr unsigned MAX_INGREDIENTS_COUNT = 30;

	constexpr unsigned NAME_FAIL_CODE = 200;
	constexpr char const* NAME_FAIL_MESSAGE = "Name must be between ";

	constexpr unsigned REMOVAL_FAIL_CODE = 201;
	constexpr char const* REMOVAL_FAIL_MESSAGE =
		"The menu item was not removed because no such item was found.";

	constexpr unsigned ADD_FAIL_CODE = 202;
	constexpr char const* ADD_FAIL_MESSAGE =
		"The menu item was not added because it already exists.";

	constexpr unsigned INGREDIENTS_COUNT_FAIL_CODE = 203;
	constexpr char const* INGREDIENTS_FAIL_MESSAGE = "Ingredients must be between ";

	constexpr unsigned PRICE_FAIL_CODE = 204;
	constexpr char const* PRICE_FAIL_MESSAGE = "Price must be between ";

	constexpr unsigned ORDER_EXISTS_FAIL_CODE = 205;
	constexpr char const* ORDER_EXISTS_FAIL_MESSAGE =
		"The menu item was not removed because an order is placed for it.";

	constexpr unsigned FAIL_CODE_START = 200;
	constexpr unsigned FAIL_CODE_END = 299;
}