#pragma once

namespace REVENUE_CONSTANTS
{
	constexpr char const* FILE_NAME = "revenues.txt";

	constexpr unsigned INVALID_REVENUE_DATE_FAIL_CODE = 400;
	constexpr char const* INVALID_REVENUE_DATE_FAIL_MESSAGE = 
		"The revenues were not shown because the date given is invalid";

	constexpr unsigned FUTURE_REVENUE_DATE_FAIL_CODE = 401;
	constexpr char const* FUTURE_REVENUE_DATE_FAIL_MESSAGE =
		"The revenues were not shown because the date given is in the future.";

	constexpr unsigned FAIL_CODE_START = 400;
	constexpr unsigned FAIL_CODE_END = 499;
}