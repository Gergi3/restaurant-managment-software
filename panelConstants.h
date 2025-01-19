#pragma once

namespace PANEL_CONSTANTS
{
	constexpr unsigned MANAGER_OPTIONS_COUNT = 14;
	constexpr unsigned MANAGER_OPTIONS[MANAGER_OPTIONS_COUNT] =
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	constexpr unsigned SERVER_OPTIONS_COUNT = 7;
	constexpr unsigned SERVER_OPTIONS[] = 
		{ 1, 2, 5, 6, 7, 8, 12 };

	constexpr char const* INVALID_OPTION_MESSAGE = "You must choose an option from below!";
}