#include "panel.h"
#include "role.h"
#include "system.h"
#include "user.h"

int main()
{
	bool systemIsUp = initializeSystem();

	if (!systemIsUp)
	{
		return -1;
	}

	Role role = getRole();

	while (true)
	{
		displayPanel(role);
		int option = promptForOption(role);
		
		if (option == EXIT_OPTION)
		{
			break;
		}
		
		routeToOption(option);
	}

	displayExitMessage();
	return 0;
}
