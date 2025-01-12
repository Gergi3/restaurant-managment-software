#pragma once

char toLower(char ch);

bool contains(
	const char const* str,
	const char const* toContain,
	bool isCaseSensitive = true);

bool isSuffix(
	const char const* str,
	const char const* suffix,
	bool isCaseSensitive = true);

