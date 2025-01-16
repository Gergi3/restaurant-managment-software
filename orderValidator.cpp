#include "io.h"
#include "menu.h"
#include "orderConstants.h"
#include "orderItem.h"
#include "orderValidator.h"
#include "validator.h"

bool validateOrderItem(OrderItem* item, int*& failCodes)
{
	if (!item)
	{
		return false;
	}
	
	bool isValidMenuItem = validateOrderItemMenuItem(item->menuItemName, failCodes);

	return isValidMenuItem;
}

bool validateOrderItemMenuItem(const char const* name, int*& failCodes)
{
	if (!name)
	{
		return false;
	}

	bool exists = menuItemExists(name);
	if (!exists)
	{
		addFailCode(ORDER_CONSTANTS::MENU_ITEM_NOT_FOUND_FAIL_CODE, failCodes);
		return false;
	}

	return true;
}

void displayOrderItemFailCodeMessage(int failCode)
{
	switch (failCode)
	{
		case ORDER_CONSTANTS::MENU_ITEM_NOT_FOUND_FAIL_CODE:
		{
			print(ORDER_CONSTANTS::MENU_ITEM_NOT_FOUND_FAIL_MESSAGE);
			break;
		}
		case ORDER_CONSTANTS::REMOVAL_FAIL_CODE:
		{
			print(ORDER_CONSTANTS::REMOVAL_FAIL_MESSAGE);
			break;
		}
	}
}
