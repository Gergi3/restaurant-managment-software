#include "garbageCollector.h";
#include "generalConstants.h";
#include "inventory.h";
#include "inventoryItem.h";
#include "inventoryValidator.h"
#include "io.h";
#include "menu.h"
#include "menu.h"
#include "menuValidator.h"
#include "panel.h"
#include "panelConstants.h"
#include "role.h"
#include "string.h";
#include "validator.h"

void displayPanel(Role role)
{
	print("1. Exit");
	print("2. Show menu");
	print("3. Add to menu");
	print("4. Remove from menu");
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

	const unsigned bufferSize = GENERAL_CONSTANTS::INPUT_BUFFER_SIZE;

	switch (option)
	{
		case 2:
		{
			print("-- Menu items --");
			printNewLine();

			MenuItem** items = getAllFromMenu();
			displayMenuItems(items);

			freeMemory(items);
			break;
		}
		case 3:
		{
			char menuItemName[bufferSize];
			unsigned ingredientsCount = 0;
			unsigned price = 0;

			print("-- Add to menu -- ", 2);

			print("Name for the menu item: ", 0);
			input(menuItemName);

			bool exists = menuItemExists(menuItemName);
			if (exists)
			{
				addFailCode(MENU_CONSTANTS::ALREADY_EXISTS_FAIL_CODE, failCodes);
				displayFailCodeMessages(failCodes);
				break;
			}

			print("Price for the menu item: ", 0);
			input(price);

			print("Please input how many ingredients the menu item needs: ", 0);
			input(ingredientsCount);

			bool isValid = validateMenuItem(menuItemName, price, ingredientsCount, failCodes);
			if (!isValid)
			{
				clearConsole();
				print("Menu item was not added.");
				displayFailCodeMessages(failCodes);

				break;
			}

			MenuItem* menuItem = new MenuItem;
			
			copyMutate(menuItem->name, menuItemName);
			menuItem->price = price;
			InventoryItem** chosenIngredients = new InventoryItem * [ingredientsCount + 1]
				{};
			menuItem->ingredients = chosenIngredients;

			printNewLine();
			print("-- Ingredients -- ");
			InventoryItem** ingredients = getAllFromInventory();
			displayInventoryItems(ingredients);
			printNewLine();

			print("Choose ingredients from above", 2);

			unsigned indx = 0;
			while (indx < ingredientsCount)
			{
				char ingredientName[bufferSize]{};
				unsigned quantityNeeded = 0;

				print("Ingredient ", 0);
				print(indx + 1, 0);
				print(": ", 0);
				input(ingredientName);

				bool isValidIngredientName = validateInventoryItemName(ingredientName, failCodes);
				if (!isValidIngredientName)
				{
					displayFailCodeMessages(failCodes);
					resetFailCodes(failCodes);
					printNewLine();
					continue;
				}

				InventoryItem* ingredient = getFromInventory(ingredientName, ingredients);
				if (!ingredient)
				{
					print("No such ingredient was found, please chose an ingredient from the list above.", 2);
					continue;
				}

				InventoryItem* chosenIngredient = getFromInventory(ingredientName, chosenIngredients);
				if (chosenIngredient)
				{
					print("Ingredient was already chosen, you must choose an ingredient which has not been chosen.");
					continue;
				}

				print("Quantity needed: ", 0);
				input(quantityNeeded);

				bool isValidIngredient = validateInventoryItemQuantity(quantityNeeded, failCodes);
				if (!isValidIngredient)
				{
					displayFailCodeMessages(failCodes);
					resetFailCodes(failCodes);
					printNewLine();
					continue;
				}

				ingredient->quantity = quantityNeeded;

				chosenIngredients[indx] = ingredient;
				indx++;
				chosenIngredients[indx] = nullptr;

				printNewLines(1);
			}
			
			addToMenu(menuItem, failCodes);
			print("Menu item added succesfully!");
			
			freeMemory(ingredients);
			freeMemory(chosenIngredients, false);
			freeMemory(menuItem, false);

			break;
		}
		case 4:
		{
			char name[bufferSize];
			print("-- Remove from menu -- ", 2);

			MenuItem** items = getAllFromMenu();
			displayMenuItems(items);
			freeMemory(items);
			printNewLine();

			print("Choose an item from above to remove.");
			print("Name for the menu item: ", 0);
			input(name);

			clearConsole();

			bool isRemoved = removeFromMenu(name, failCodes);
			if (isRemoved)
			{
				print("Item removed successsfully!");
			}

			displayFailCodeMessages(failCodes);

			break;
		}
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
			char name[bufferSize];
			unsigned quantity = 0;

			print("-- Add to inventory -- ", 2);

			print("Name for the inventory item: ", 0);
			input(name);

			print("Please input quantity for the inventory item: ", 0);
			input(quantity);

			bool isValid = addToInventory(name, quantity, failCodes);

			clearConsole();

			print(isValid ? "Item added successfully!" : "Item was not added!");
			displayFailCodeMessages(failCodes);

			break;
		}
		case 11: // Remove from inventory
		{
			char name[bufferSize];
			print("-- Remove from inventory -- ", 2);

			InventoryItem** items = getAllFromInventory();
			displayInventoryItems(items);
			freeMemory(items);
			printNewLine();
			
			print("Choose an item from above to remove.");
			print("Name for the inventory item: ", 0);
			input(name);

			bool isRemoved = removeFromInventory(name, failCodes);
			if (isRemoved)
			{
				print("Item removed successfully!");
			}

			displayFailCodeMessages(failCodes);

			break;
		}
	}

	freeMemory(failCodes);

	printNewLine();
	system("pause");
	clearConsole();
}

bool isValidOption(int option, Role role)
{
	return option >= PANEL_CONSTANTS::MIN_SERVER_OPTION
		&& option <= PANEL_CONSTANTS::MAX_SERVER_OPTION
		&& role == Role::Server
		|| option >= PANEL_CONSTANTS::MIN_MANAGER_OPTION
		&& option <= PANEL_CONSTANTS::MAX_MANAGER_OPTION
		&& role == Role::Manager;
}

void displayExitMessage()
{
	clearConsole();
	print("Exitting managment software..");
	print("Successfully exited!");
}