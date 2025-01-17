#pragma once
#include "dateConstants.h"
#include "inventoryConstants.h"
#include "menuConstants.h"
#include "orderConstants.h"
#include "revenueConstants.h";

namespace GENERAL_CONSTANTS
{
	constexpr unsigned FILES_COUNT = 5;
	constexpr char const* FILE_NAMES[GENERAL_CONSTANTS::FILES_COUNT] =
	{
		ORDER_CONSTANTS::FILE_NAME,
		MENU_CONSTANTS::FILE_NAME,
		INVENTORY_CONSTANTS::FILE_NAME,
		REVENUE_CONSTANTS::FILE_NAME,
		DATE_CONSTANTS::FILE_NAME
	};


	constexpr unsigned FAIL_CODES_LENGTH = 10;
	constexpr unsigned EMPTY_CODE = 0;
	constexpr unsigned INPUT_BUFFER_SIZE = 1024;
	constexpr unsigned MAX_UINT_DIGITS_COUNT = 10;
}