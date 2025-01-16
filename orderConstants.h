#pragma once

namespace ORDER_CONSTANTS
{
	constexpr char const* FILE_NAME = "orders.txt";

	constexpr unsigned MENU_ITEM_NOT_FOUND_FAIL_CODE = 300;
	constexpr char const* MENU_ITEM_NOT_FOUND_FAIL_MESSAGE =
		"The order was cancelled because no such menu item was found.";

	constexpr unsigned REMOVAL_FAIL_CODE = 301;
	constexpr char const* REMOVAL_FAIL_MESSAGE =
		"The order was not cancelled because no such order was found.";

	constexpr unsigned FAIL_CODE_START = 300;
	constexpr unsigned FAIL_CODE_END = 399;
}