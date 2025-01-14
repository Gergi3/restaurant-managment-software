#include "io.h";
#include "panel.h"
#include "role.h"

const unsigned MIN_SERVER_OPTION = 1;
const unsigned MIN_MANAGER_OPTION = 1;
const unsigned MAX_SERVER_OPTION = 7;
const unsigned MAX_MANAGER_OPTION = 15;

void displayPanel(Role role)
{
	print("1. -");
	print("2. -");
	print("3. -");
	print("4. -");
	print("5. -");
	print("6. -");
	print("7. -");

	if (role != Role::Manager)
	{
		return;
	}

	print("8. See inventory");
	print("9. Add to inventory");
	print("10. Remove from inventory");
	print("10. -");
	print("11. -");
	print("12. -");
	print("13. -");
	print("14. -");
	print("15. Exit");
}

int promptForOption(Role role)
{
	print("Go to: ", 0);
	int chosenOption = -1;
	input(chosenOption);

	if (!isValidOption(chosenOption, role))
	{
		clearErrorFlagsFromCin();
		return -1;
	}

	return chosenOption;
}

void routeToOption(int option)
{
	if (option == -1)
	{
		print("You must choose an option from below!");
		return;
	}
}

bool isValidOption(int option, Role role)
{
	return option >= MIN_SERVER_OPTION && option <= MAX_SERVER_OPTION && role == Role::Server
		|| option >= MIN_MANAGER_OPTION && option <= MAX_MANAGER_OPTION && role == Role::Manager;
}

void displayExitMessage()
{
	print("Exitting managment software..");
	print("Successfully exited!");
}