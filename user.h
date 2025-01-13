#pragma once

#include "role.h"

Role getRole();

bool isValidRoleString(
	const char const* str,
	const char const* expected,
	char expectedShort);