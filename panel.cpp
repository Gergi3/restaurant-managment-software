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
#include "revenue.h"
#include "role.h"
#include "string.h"
#include "validator.h"

void displayPanel(Role role)
{
	displayDate();
	if (role == Role::Manager)
	{
		print("1. Exit and end revenue");
	}
	else if (role == Role::Server)
	{
		print("1. Exit");
	}

	printNewLine();

	print("-- Menu --");
	print("2. Show menu");
	if (role == Role::Manager)
	{
		print("3. Add to menu");
		print("4. Remove from menu");
	}

	printNewLine();

	print("-- Orders --");
	print("5. Show orders");
	print("6. Show orders with count");
	print("7. Place order");
	print("8. Cancel order");

	printNewLine();

	if (role == Role::Manager)
	{
		print("-- Inventory --");
		print("9. Show inventory");
		print("10. Add to inventory");
		print("11. Remove from inventory", 2);
	}

	print("-- Revenue --");
	print("12. Get current revenue");
	if (role == Role::Manager)
	{
		print("13. End current revenue");
		print("14. Check revenue from date to today");
	}
}

int promptForOption(Role role)
{
	printNewLine();
	print("Go to: ", 0);
	int chosenOption = -1;
	input(chosenOption);

	if (!isValidOption(chosenOption, role))
	{
		return -1;
	}

	return chosenOption;
}

void routeToOption(int option, Role role)
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
			if (role == Role::Manager)
			{
				print("Ending current revenue..");
				bool isEnded = endCurrentRevenue();
				if (!isEnded)
				{
					print("There was an error with ending current revenue!");
					print("Please try again!");
				}
				else
				{
					print("Successfully ended current revenue!");
				}

				printNewLine();
			}


			print("Exitting managment software..");
			print("Successfully exited!");

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

			InventoryItem** ingredients = getAllFromInventory();
			unsigned inventoryCount = getInventoryCount(ingredients);

			if (inventoryCount == 0)
			{
				clearConsole();
				print("Cannot add to menu because inventory is empty!");

				break;
			}

			char menuItemName[bufferSize]{};
			unsigned ingredientsCount = 0;
			unsigned price = 0;

			print("Name of dish: ", 0);
			input(menuItemName);

			bool isValidName = validateMenuItemName(menuItemName, failCodes);
			if (!isValidName) 
			{
				clearConsole();
				print("The dish could not be added!");
				displayFailCodeMessages(failCodes);

				break;
			}

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

			bool isValidPrice = validateMenuItemPrice(price, failCodes);
			if (!isValidPrice)
			{
				clearConsole();
				print("The dish could not be added!");
				displayFailCodeMessages(failCodes);
				
				break;
			}

			print("Please specify the number of ingredients for this dish: ", 0);
			input(ingredientsCount);

			if (ingredientsCount > inventoryCount)
			{
				clearConsole();
				print("The dish could not be added!");
				print("The dish cannot have ", 0);
				print(ingredientsCount, 0);
				print(" ingredients, because", 0);
				print(" there are only ", 0);
				print(inventoryCount, 0);
				print(" available ingredients in the inventory");

				break;
			}

			bool isValidCount = validateMenuItemIngredientsCount(ingredientsCount, failCodes);
			if (!isValidCount)
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
			if (!menuItems)
			{
				print("Menu is currently empty!");
				break;
			}
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
			if (!menuItems)
			{
				print("Menu is currently empty!");
				break;
			}
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
			print("The item will not be completely deleted from the inventory, its quantity will be reduced to 0.");
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
		case 12:
		{
			print("-- Current revenue --", 2);

			displayCurrentRevenue();

			break;
		}
		case 13:
		{
			print("-- End current revenue --");
			displayCurrentRevenue();

			printNewLine();

			bool isEnded = endCurrentRevenue();
			if (!isEnded)
			{
				print("There was an error with ending current revenue!");
				print("Please try again!");
			}
			else
			{
				print("Successfully ended current revenue!");
			}

			break;
		}
		case 14:
		{
			print("-- Revenue from date to today --", 2);

			char date[bufferSize]{};
			print("From date (dd.mm.yyyy): ", 0);
			input(date);
			print("To today: ", 0);
			print(getDate(), 2);

			bool isValid = displayRevenueFromDateToNow(date, failCodes);
			if (!isValid)
			{
				clearConsole();
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
			unsigned serverOptionsCount = PANEL_CONSTANTS::SERVER_OPTIONS_COUNT;
			while (serverOptionsCount)
			{
				unsigned serverOption = PANEL_CONSTANTS::SERVER_OPTIONS[serverOptionsCount - 1];
				if (serverOption == option)
				{
					isAllowed = true;
				}
				serverOptionsCount--;
			}
			break;
		}
		case Role::Manager:
		{
			unsigned managerOptionsCount = PANEL_CONSTANTS::MANAGER_OPTIONS_COUNT;
			while (managerOptionsCount)
			{
				unsigned managerOption = PANEL_CONSTANTS::MANAGER_OPTIONS[managerOptionsCount - 1];
				if (managerOption == option)
				{
					isAllowed = true;
				}
				managerOptionsCount--;
			}

			break;
		}
	}

	return isAllowed;
}

