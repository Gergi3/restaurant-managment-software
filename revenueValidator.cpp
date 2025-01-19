#include "io.h"
#include "revenueConstants.h"

void displayRevenueFailCodeMessage(int failCode)
{
	switch (failCode)
	{
		case REVENUE_CONSTANTS::INVALID_REVENUE_DATE_FAIL_CODE:
		{
			print(REVENUE_CONSTANTS::INVALID_REVENUE_DATE_FAIL_MESSAGE);

			break;
		}
		case REVENUE_CONSTANTS::FUTURE_REVENUE_DATE_FAIL_CODE:
		{
			print(REVENUE_CONSTANTS::FUTURE_REVENUE_DATE_FAIL_MESSAGE);

			break;
		}
	}
}
