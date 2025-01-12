#include <iostream>
#include "string.h"
#include "io.h"
#include "user.h"

const int MAX_ROLE_LENGTH = 64;

enum Role
{
	Server = 1,
	Manager = 2
};

Role getRole()
{
	char inputStr[MAX_ROLE_LENGTH];

	bool isServer, isManager = false;

	do
	{
		print("What role are you? Server (s) or Manager (m)?");
		input(inputStr, MAX_ROLE_LENGTH);
		
		trimMutate(inputStr);

		isServer = isValidRoleString(inputStr, "server", 's');
		isManager = isValidRoleString(inputStr, "manager", 'm');

		if (isManager)
		{
			print("You have logged in as a Manager");
			break;
		}
		else if (isServer)
		{
			print("You have logged in as a Server");
			break;
		}
		else
		{
			print(inputStr, 0);
			print(" is not a valid role. Please try again!", 2);
		}

	} while (true);

	return isServer ? Role::Server : Role::Manager;
}

bool isValidRoleString(
	const char* str, 
	const char const* expected,
	char expectedShort)
{
	return contains(str, expected, false) 
		|| length(str) == 1 && str[0] == expectedShort;
}

