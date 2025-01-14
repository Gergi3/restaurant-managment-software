#include "string.h"
#include "system.h"
#include "user.h"
#include <iostream>

int main()
{
	bool systemIsUp = initializeSystem();

	if (!systemIsUp)
	{
		return -1;
	}

	Role role = getRole();
}
