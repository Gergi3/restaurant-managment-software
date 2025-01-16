#include "io.h";
#include "panel.h"
#include "role.h"
#include "system.h"
#include "user.h"

int main()
{
	bool systemIsUp = initializeSystem();

	if (!systemIsUp)
	{
		print("Fatal error! Shutting down!");
		return -1;
	}

	Role role = getRole();

	int option = -1;
	while (option != EXIT_OPTION)
	{
		displayPanel(role);
		option = promptForOption(role);
		routeToOption(option);
	}

	return 0;
}
