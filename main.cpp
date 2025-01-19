/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University * Winter semester 2024/2025
*
* @author Georgi Petrov
* @idnumber 5MI0600421
* @compiler VC
*
* Entry point for the project
*
*/

#include "io.h"
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
		routeToOption(option, role);
	}

	return 0;
}
