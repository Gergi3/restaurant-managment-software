#include "generalConstants.h"
#include "inventoryConstants.h"
#include "inventoryValidator.h"
#include "menuConstants.h"
#include "menuValidator.h"
#include "orderConstants.h"
#include "orderValidator.h"

void displayFailCodeMessages(int*& failCodes)
{
	if (!failCodes)
	{
		return;
	}

	for (size_t i = 0; i < GENERAL_CONSTANTS::FAIL_CODES_LENGTH; i++)
	{
		int failCode = failCodes[i];

		if (failCode >= INVENTORY_CONSTANTS::FAIL_CODE_START
			&& failCode <= INVENTORY_CONSTANTS::FAIL_CODE_END)
		{
			displayInventoryItemFailCodeMessage(failCode);
		}
		else if (failCode >= MENU_CONSTANTS::FAIL_CODE_START
				 && failCode <= MENU_CONSTANTS::FAIL_CODE_END)
		{
			displayMenuItemFailCodeMessage(failCode);
		}
		else if (failCode >= ORDER_CONSTANTS::FAIL_CODE_START
				 && failCode <= ORDER_CONSTANTS::FAIL_CODE_END)
		{
			displayOrderItemFailCodeMessage(failCode);
		}
	}
}

void addFailCode(
	unsigned failCode,
	int*& failCodes)
{
	if (!failCodes)
	{
		return;
	}

	unsigned indx = 0;

	while (indx < GENERAL_CONSTANTS::FAIL_CODES_LENGTH)
	{
		if (failCodes[indx] == GENERAL_CONSTANTS::EMPTY_CODE)
		{
			failCodes[indx] = failCode;
			return;
		}

		indx++;
	}
}

void resetFailCodes(int*& failCodes)
{
	if (!failCodes)
	{
		return;
	}

	for (size_t i = 0; i < GENERAL_CONSTANTS::FAIL_CODES_LENGTH; i++)
	{
		failCodes[i] = GENERAL_CONSTANTS::EMPTY_CODE;
	}
}
