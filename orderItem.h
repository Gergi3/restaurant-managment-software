#pragma once

#include "menuConstants.h"

struct OrderItem
{
	unsigned id = 0;
	char menuItemName[MENU_CONSTANTS::MAX_NAME_LENGTH + 1]{};
};