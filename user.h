#pragma once

enum Role;

Role getRole();

bool isValidRoleString(
	const char const* str,
	const char const* expected,
	char expectedShort);