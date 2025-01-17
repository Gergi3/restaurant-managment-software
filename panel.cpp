#include "date.h"
#include "garbageCollector.h"
#include "generalConstants.h"
#include "inventory.h"
#include "inventoryItem.h"
#include "inventoryValidator.h"
#include "io.h"
#include "menu.h"
#include "menuValidator.h"
#include "order.h"
#include "panel.h"
#include "panelConstants.h"
#include "role.h"
#include "string.h"
#include "validator.h"

void displayPanel(Role role)
{
	displayDate();
	print("1. Exit");
	print("2. Show menu");
	print("3. Add to menu");
	print("4. Remove from menu");
	print("5. Show orders");
	print("6. Show orders with count");
	print("7. Place order");
	print("8. Cancel order");

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
		print(PANEL_CONSTANTS::INVALID_OPTION_MESSAGE);
		return;
	}

	int* failCodes = new int[GENERAL_CONSTANTS::FAIL_CODES_LENGTH]
		{};

	const unsigned bufferSize = GENERAL_CONSTANTS::INPUT_BUFFER_SIZE;

	switch (option)
	{
		case EXIT_OPTION:
		{
			incrementDate();
			displayExitMessage();

			break;
		}
		case 2:
		{
			print("-- Menu --", 2);

			MenuItem** menuItems = getAllFromMenu();
			if (!menuItems)
			{
				print("Menu is currently empty!");
				break;
			}

			displayMenuItems(menuItems);

			freeMemory(menuItems);
			break;
		}
		case 3:
		{
			print("-- Add to menu -- ", 2);

			char menuItemName[bufferSize]{};
			unsigned ingredientsCount = 0;
			unsigned price = 0;

			print("Name of dish: ", 0);
			input(menuItemName);

			bool exists = menuItemExists(menuItemName);
			if (exists)
			{
				clearConsole();
				addFailCode(MENU_CONSTANTS::ADD_FAIL_CODE, failCodes);
				displayFailCodeMessages(failCodes);

				break;
			}

			print("Price of dish: ", 0);
			input(price);

			print("Please specify the number of ingredients for this dish: ", 0);
			input(ingredientsCount);

			bool isValid = validateMenuItem(menuItemName, price, ingredientsCount, failCodes);
			if (!isValid)
			{
				clearConsole();
				print("The dish could not be added!");
				displayFailCodeMessages(failCodes);

				break;
			}

			MenuItem* menuItem = new MenuItem;
			copyMutate(menuItem->name, menuItemName);
			menuItem->price = price;

			InventoryItem** chosenIngredients = new InventoryItem * [ingredientsCount + 1]
				{};
			menuItem->ingredients = chosenIngredients;

			InventoryItem** ingredients = getAllFromInventory();

			printNewLine();
			print("-- Ingredients -- ");
			displayInventoryItems(ingredients);

			printNewLine();
			print("Select ingredients from the list provided above.", 2);

			unsigned indx = 0;
			while (indx < ingredientsCount)
			{
				char ingredientName[bufferSize]{};
				unsigned quantityNeeded = 0;

				print("Ingredient ", 0);
				print(indx + 1, 0);
				print(": ", 0);
				input(ingredientName);

				//bool isValidIngredientName = validateInventoryItemName(ingredientName, failCodes);
				//if (!isValidIngredientName)
				//{
				//	displayFailCodeMessages(failCodes);
				//	resetFailCodes(failCodes);
				//	printNewLine();

				//	continue;
				//}

				InventoryItem* ingredient = getFromInventory(ingredientName, ingredients);
				if (!ingredient)
				{
					print("Ingredient not found. ", 0);
					print("Please select an ingredient from the list provided above.", 2);

					continue;
				}

				InventoryItem* chosenIngredient = getFromInventory(ingredientName, chosenIngredients);
				if (chosenIngredient)
				{
					print("This ingredient has already been selected. ", 0);
					print("Please choose an ingredient that has not been selected yet.", 2);

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
				chosenIngredients[indx++] = ingredient;
				chosenIngredients[indx] = nullptr;

				printNewLine();
			}

			bool isAdded = addToMenu(menuItem, failCodes);
			if (isAdded)
			{
				print("Dish added succesfully!");
			}

			displayFailCodeMessages(failCodes);

			freeMemory(ingredients);
			freeMemory(chosenIngredients, false);
			freeMemory(menuItem, false);

			break;
		}
		case 4:
		{
			print("-- Remove from menu -- ", 2);

			char name[bufferSize];

			MenuItem** menuItems = getAllFromMenu();
			displayMenuItems(menuItems);
			freeMemory(menuItems);

			printNewLine();
			print("Please select a dish from the list above to remove.");
			print("Name of dish: ", 0);
			input(name);

			clearConsole();
			
			bool isRemoved = removeFromMenu(name, failCodes);
			if (isRemoved)
			{
				print("Dish removed successsfully!");
			}

			displayFailCodeMessages(failCodes);

			break;
		}
		case 5:
		{
			print("-- Orders --", 2);

			OrderItem** orders = getAllOrders();
			if (!orders)
			{
				print("There are no orders currently placed.");
				break;
			}
			displayOrderItems(orders);
			freeMemory(orders);

			break;
		}
		case 6:
		{
			print("-- Orders with count --", 2);

			OrderItem** orders = getAllOrders();
			if (!orders)
			{
				print("There are no orders currently placed.");
				break;
			}
			displayOrderItems(orders, true);
			freeMemory(orders);

			break;
		}
		case 7:
		{
			print("-- Place order -- ", 2);

			MenuItem** menuItems = getAllFromMenu();
			displayMenuItems(menuItems);
			freeMemory(menuItems);

			printNewLine();

			print("Name of dish for order: ", 0);
			char menuItemName[bufferSize];
			input(menuItemName);

			clearConsole();

			bool isAdded = addToOrder(menuItemName, failCodes);
			if (isAdded)
			{
				print("Order placed successfully!");
			}

			displayFailCodeMessages(failCodes);

			break;
		}
		case 8:
		{
			print("-- Cancel order --", 2);

			OrderItem** orders = getAllOrders();
			if (!orders)
			{
				print("There are no orders currently placed.");
				break;
			}
			displayOrderItems(orders);

			printNewLine();
			print("Select an order from the list provided above.");

			print("Order ID to remove: ", 0);
			unsigned id = 0;
			input(id);

			clearConsole();

			bool isRemoved = removeOrder(id, failCodes, orders);
			print(isRemoved ? "Order cancelled successfully." : "The order could not be canceled.");
			displayFailCodeMessages(failCodes);

			freeMemory(orders);
			break;
		}
		case 9:
		{
			print("-- Show inventory -- ", 2);

			InventoryItem** inventoryItems = getAllFromInventory();
			if (!inventoryItems)
			{
				print("Inventory is currently empty!");
				break;
			}

			displayInventoryItems(inventoryItems);

			freeMemory(inventoryItems);
			break;
		}
		case 10:
		{
			print("-- Add to inventory -- ", 2);

			char name[bufferSize];
			unsigned quantity = 0;

			print("Name of ingredient: ", 0);
			input(name);

			print("Quantity of ingredient: ", 0);
			input(quantity);

			clearConsole();

			bool isValid = addToInventory(name, quantity, failCodes);
			print(isValid ? "Ingredient added successfully." : "The ingredient could not be added.");
			displayFailCodeMessages(failCodes);

			break;
		}
		case 11:
		{
			print("-- Remove from inventory -- ", 2);

			char name[bufferSize];

			InventoryItem** inventoryItems = getAllFromInventory();
			if (!inventoryItems)
			{
				print("Inventory is currently empty!");
				break;
			}
			displayInventoryItems(inventoryItems);
			freeMemory(inventoryItems);

			printNewLine();
			print("Select ingredient from the list provided above.");
			print("Name of ingredient: ", 0);
			input(name);

			bool isRemoved = removeFromInventory(name, failCodes);
			if (isRemoved)
			{
				print("Ingredient removed successfully!");
			}

			displayFailCodeMessages(failCodes);

			break;
		}
	}

	freeMemory(failCodes);

	if (option == EXIT_OPTION)
	{
		return;
	}

	printNewLine();
	system("pause");
	clearConsole();
}

bool isValidOption(
	int option,
	Role role)
{
	bool isAllowed = false;

	switch (role)
	{
		case Role::Server:
		{
			isAllowed = option >= PANEL_CONSTANTS::MIN_SERVER_OPTION
				&& option <= PANEL_CONSTANTS::MAX_SERVER_OPTION;

			break;
		}
		case Role::Manager:
		{
			isAllowed = option >= PANEL_CONSTANTS::MIN_MANAGER_OPTION
				&& option <= PANEL_CONSTANTS::MAX_MANAGER_OPTION;

			break;
		}
	}

	return isAllowed;
}

void displayExitMessage()
{
	clearConsole();

	print("Exitting managment software..");
	print("Successfully exited!");
}