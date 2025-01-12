#include <iostream>
#include "system.h"
#include "string.h"
#include "user.h"

int main()
{
	bool systemIsUp = initializeSystem();

	if (!systemIsUp)
	{
		return -1;
	}

	Role role = getRole();
}
