#include "generalConstants.h"
#include "inventoryItem.h"
#include "inventoryValidator.h"
#include "io.h";
#include "string.h"
#include "validator.h"

bool validateInventoryItem(InventoryItem item, int*& failCodes)
{
	if (!failCodes)
	{
		return false;
	}

	return validateInventoryItem(item.name, item.quantity, failCodes);
}

bool validateInventoryItem(const char const* name, unsigned quantity, int*& failCodes)
{
	if (!failCodes)
	{
		return false;
	}

	bool isValidName = validateInventoryItemName(name, failCodes);
	bool isValidQuantity = validateInventoryItemQuantity(quantity, failCodes);

	return isValidName && isValidQuantity;
}

bool validateInventoryItemName(const char const* name, int*& failCodes)
{
	bool isValid = validateInventoryItemName(name);

	if (!isValid)
	{
		addFailCode(INVENTORY_CONSTANTS::NAME_FAIL_CODE, failCodes);
	}

	return isValid;
}

bool validateInventoryItemName(const char const* name)
{
	unsigned nameLen = length(name);
	return nameLen >= INVENTORY_CONSTANTS::MIN_NAME_LENGTH
		&& nameLen <= INVENTORY_CONSTANTS::MAX_NAME_LENGTH;
}

bool validateInventoryItemQuantity(unsigned quantity , int*& failCodes)
{
	bool isValid = validateInventoryItemQuantity(quantity);

	if (!isValid)
	{
		addFailCode(INVENTORY_CONSTANTS::QUANTITY_FAIL_CODE, failCodes);
	}

	return isValid;
}


bool validateInventoryItemQuantity(unsigned quantity)
{
	return quantity >= INVENTORY_CONSTANTS::MIN_QUANTITY
		&& quantity <= INVENTORY_CONSTANTS::MAX_QUANTITY;
}

void displayInventoryItemFailCodeMessage(int failCode)
{
	switch (failCode)
	{
		case INVENTORY_CONSTANTS::NAME_FAIL_CODE:
		{
			print(INVENTORY_CONSTANTS::NAME_FAIL_MESSAGE, 0);
			print(INVENTORY_CONSTANTS::MIN_NAME_LENGTH, 0);
			print(" and ", 0);
			print(INVENTORY_CONSTANTS::MAX_NAME_LENGTH, 0);
			print(" characters long.");

			break;
		}
		case INVENTORY_CONSTANTS::QUANTITY_FAIL_CODE:
		{
			print(INVENTORY_CONSTANTS::QUANTITY_FAIL_MESSAGE, 0);
			print(INVENTORY_CONSTANTS::MIN_QUANTITY, 0);
			print(" and ", 0);
			print(INVENTORY_CONSTANTS::MAX_QUANTITY, 0);
			print(".");

			break;
		}
		case INVENTORY_CONSTANTS::REMOVAL_FAIL_CODE:
		{
			print(INVENTORY_CONSTANTS::REMOVAL_FAIL_MESSAGE);

			break;
		}
	}
}