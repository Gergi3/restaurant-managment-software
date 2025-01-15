#include "generalConstants.h"
#include "io.h"
#include "string.h"
#include "user.h"
#include "userConstants.h"
#include <iostream>

Role getRole()
{
	char inputStr[GENERAL_CONSTANTS::INPUT_BUFFER_SIZE];

	bool isServer = false, isManager = false;

	while (!isManager && !isServer)
	{
		print("What role are you? ", 0);
		
		print(USER_CONSTANTS::SERVER_ROLE_LONG, 0);
		print(" (", 0);
		print(USER_CONSTANTS::SERVER_ROLE_SHORT, 0);
		print(") or ", 0);
		print(USER_CONSTANTS::MANAGER_ROLE_LONG, 0);
		print(" (", 0);
		print(USER_CONSTANTS::MANAGER_ROLE_SHORT, 0);
		print(")?");

		input(inputStr);

		trimMutate(inputStr);

		isServer = isValidRoleString(inputStr, 
			USER_CONSTANTS::SERVER_ROLE_LONG,
			USER_CONSTANTS::SERVER_ROLE_SHORT);
		
		isManager = isValidRoleString(inputStr,
			USER_CONSTANTS::MANAGER_ROLE_LONG,
			USER_CONSTANTS::MANAGER_ROLE_SHORT);

		clearConsole();

		if (!isManager && !isServer)
		{
			print(inputStr, 0);
			print(" is not a valid role. Please try again!", 2);
		}
	}

	Role role = isManager ? Role::Manager : Role::Server;

	print("You have logged in as a ", 0);
	print(toString(role));

	return role;
}

bool isValidRoleString(
	const char* str,
	const char const* expected,
	char expectedShort)
{
	return contains(str, expected, false)
		|| length(str) == 1 && toLower(str[0]) == toLower(expectedShort);
}

