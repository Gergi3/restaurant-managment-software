#pragma once

namespace INVENTORY_CONSTANTS
{
	constexpr unsigned MAX_NAME_LENGTH = 100;
	constexpr unsigned MIN_NAME_LENGTH = 2;

	constexpr unsigned MIN_QUANTITY = 1;
	constexpr unsigned MAX_QUANTITY = 100'000; // DEPENDANT ON MAX_QUANTITY_DIGITS_COUNT
	constexpr unsigned MAX_QUANTITY_DIGITS_COUNT = 6; // DEPENDANT ON MAX_QUANTITY

	constexpr unsigned NAME_FAIL_CODE = 100;
	constexpr char const* NAME_FAIL_MESSAGE = "Name must be between ";

	constexpr unsigned QUANTITY_FAIL_CODE = 101;
	constexpr char const* QUANTITY_FAIL_MESSAGE = "Quantity must be between ";

	constexpr unsigned REMOVAL_FAIL_CODE = 102;
	constexpr char const* REMOVAL_FAIL_MESSAGE = "The item was not removed because no such item was found.";

	constexpr unsigned FAIL_CODE_START = 100;
	constexpr unsigned FAIL_CODE_END = 199;
}