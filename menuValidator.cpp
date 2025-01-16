#include "io.h"
#include "menuConstants.h"
#include "menuValidator.h"
#include "string.h"
#include "validator.h"

bool validateMenuItem(const char const* name, unsigned price, unsigned ingredientsCount, int*& failCodes)
{
	bool isValidName = validateMenuItemName(name, failCodes);
	bool isValidPrice = validateMenuItemPrice(price, failCodes);
	bool isValidCount = validateMenuItemIngredientsCount(ingredientsCount, failCodes);

	return isValidCount && isValidName && isValidPrice;
}

bool validateMenuItemName(const char const* name)
{
	unsigned nameLen = length(name);
	return nameLen >= MENU_CONSTANTS::MIN_NAME_LENGTH
		&& nameLen <= MENU_CONSTANTS::MAX_NAME_LENGTH;
}

bool validateMenuItemName(const char const* name, int*& failCodes)
{
	bool isValid = validateMenuItemName(name);
	if (!isValid)
	{
		addFailCode(MENU_CONSTANTS::NAME_FAIL_CODE, failCodes);
	}

	return isValid;
}

bool validateMenuItemPrice(unsigned price)
{
	return price >= MENU_CONSTANTS::MIN_PRICE
		&& price <= MENU_CONSTANTS::MAX_PRICE;
}

bool validateMenuItemPrice(unsigned price, int*& failCodes)
{
	bool isValid = validateMenuItemPrice(price);

	if (!isValid)
	{
		addFailCode(MENU_CONSTANTS::PRICE_FAIL_CODE, failCodes);
	}

	return isValid;
}

bool validateMenuItemIngredientsCount(unsigned count)
{
	return count >= MENU_CONSTANTS::MIN_INGREDIENTS_COUNT
		&& count <= MENU_CONSTANTS::MAX_INGREDIENTS_COUNT;
}

bool validateMenuItemIngredientsCount(unsigned count, int*& failCodes) 
{
	bool isValid = validateMenuItemIngredientsCount(count);
	if (!isValid)
	{
		addFailCode(MENU_CONSTANTS::INGREDIENTS_COUNT_FAIL_CODE, failCodes);
	}

	return isValid;
}

void displayMenuItemFailCodeMessage(int failCode)
{
	switch (failCode)
	{
		case MENU_CONSTANTS::PRICE_FAIL_CODE:
		{
			print(MENU_CONSTANTS::PRICE_FAIL_MESSAGE, 0);
			print(MENU_CONSTANTS::MIN_PRICE, 0);
			print(" and ", 0);
			print(MENU_CONSTANTS::MAX_PRICE);

			break;
		}
		case MENU_CONSTANTS::INGREDIENTS_COUNT_FAIL_CODE:
		{
			print(MENU_CONSTANTS::INGREDIENTS_FAIL_MESSAGE, 0);
			print(MENU_CONSTANTS::MIN_INGREDIENTS_COUNT, 0);
			print(" and ", 0);
			print(MENU_CONSTANTS::MAX_INGREDIENTS_COUNT);

			break;
		}
		case MENU_CONSTANTS::NAME_FAIL_CODE:
		{
			print(MENU_CONSTANTS::NAME_FAIL_MESSAGE, 0);
			print(MENU_CONSTANTS::MIN_NAME_LENGTH, 0);
			print(" and ", 0);
			print(MENU_CONSTANTS::MAX_NAME_LENGTH, 0);
			print(" characters long.");

			break;
		}
		case MENU_CONSTANTS::ALREADY_EXISTS_FAIL_CODE:
		{
			print(MENU_CONSTANTS::ALREADY_EXISTS_FAIL_MESSAGE);

			break;
		}
		case MENU_CONSTANTS::NOT_FOUND_FAIL_CODE:
		{
			print(MENU_CONSTANTS::NOT_FOUND_FAIL_MESSAGE);
			break;
		}
	}
}