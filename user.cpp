#include "io.h"
#include "string.h"
#include "user.h"
#include <iostream>

const unsigned MAX_ROLE_LENGTH = 64;

Role getRole()
{
	char inputStr[MAX_ROLE_LENGTH];

	bool isServer = false, isManager = false;

	while (!isManager && !isServer)
	{
		print("What role are you? Server (s) or Manager (m)?");
		input(inputStr, MAX_ROLE_LENGTH);

		trimMutate(inputStr);

		isServer = isValidRoleString(inputStr, "server", 's');
		isManager = isValidRoleString(inputStr, "manager", 'm');

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
		|| length(str) == 1 && str[0] == expectedShort;
}

