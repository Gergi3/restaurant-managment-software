#include "garbageCollector.h";
#include "generalConstants.h";
#include "inventory.h";
#include "inventoryItem.h";
#include "io.h";
#include "panel.h"
#include "role.h"
#include "validator.h"

const unsigned MIN_SERVER_OPTION = 1;
const unsigned MIN_MANAGER_OPTION = 1;
const unsigned MAX_SERVER_OPTION = 7;
const unsigned MAX_MANAGER_OPTION = 15;

void displayPanel(Role role)
{
	print("1. Exit");
	print("2. -");
	print("3. -");
	print("4. -");
	print("5. -");
	print("6. -");
	print("7. -");
	print("8. -");

	if (role != Role::Manager)
	{
		return;
	}

	print("9. Show inventory");
	print("10. Add to inventory");
	print("11. Remove from inventory");
	print("12. -");
	print("13. -");
	print("14. -");
	print("15. -");
}

int promptForOption(Role role)
{
	print("Go to: ", 0);
	int chosenOption = -1;
	input(chosenOption);

	forceClearErrorFlagsFromCin();

	if (!isValidOption(chosenOption, role))
	{
		return -1;
	}

	return chosenOption;
}

void routeToOption(int option)
{
	clearConsole();

	if (option == -1)
	{
		print("You must choose an option from below!");
		return;
	}

	int* failCodes = new int[GENERAL_CONSTANTS::FAIL_CODES_LENGTH]
		{};

	switch (option)
	{
		case 9: // Show inventory
		{
			print("-- Show inventory -- ", 2);

			InventoryItem** items = getAllFromInventory();
			displayInventoryItems(items);
			freeMemory(items);

			break;
		}
		case 10: // Add to inventory
		{
			char name[INVENTORY_CONSTANTS::MAX_NAME_LENGTH];
			unsigned quantity = 0;

			print("-- Add to inventory -- ", 2);

			print("Name for the inventory item: ", 0);
			input(name, INVENTORY_CONSTANTS::MAX_NAME_LENGTH);

			print("Please input quantity for the inventory item: ", 0);
			input(quantity);

			bool isValid = addToInventory(name, quantity, failCodes);

			clearConsole();

			print(isValid ? "Item added successfully!" : "Item was not added!");
			displayFailCodeMessages(failCodes);

			break;
		}
		case 11:
		{
			char name[INVENTORY_CONSTANTS::MAX_NAME_LENGTH];
			print("-- Remove from inventory -- ", 2);

			print("Name for the inventory item: ", 0);
			input(name, INVENTORY_CONSTANTS::MAX_NAME_LENGTH);

			bool removedSuccessfully = removeFromInventory(name, failCodes);

			if (removedSuccessfully)
			{
				print("Item removed successfully!");
			}

			displayFailCodeMessages(failCodes);

			break;
		}
	}

	freeMemory(failCodes);

	system("pause");
	clearConsole();
}

bool isValidOption(int option, Role role)
{
	return option >= MIN_SERVER_OPTION && option <= MAX_SERVER_OPTION && role == Role::Server
		|| option >= MIN_MANAGER_OPTION && option <= MAX_MANAGER_OPTION && role == Role::Manager;
}

void displayExitMessage()
{
	clearConsole();
	print("Exitting managment software..");
	print("Successfully exited!");
}