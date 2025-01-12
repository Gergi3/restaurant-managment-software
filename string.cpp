#include "string.h";

char toLower(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		return ch + 'a' - 'A';
	}
	return ch;
}

bool contains(
	const char const* str,
	const char const* toContain,
	bool isCaseSensitive)
{
	if (!str || !toContain)
	{
		return false;
	}

	while (*str)
	{
		if (isSuffix(str, toContain, isCaseSensitive))
		{
			return true;
		}

		str++;
	}

	return false;
}

bool isSuffix(
	const char const* str,
	const char const* suffix,
	bool isCaseSensitive)
{
	if (!str || !suffix)
	{
		return false;
	}

	while (*suffix)
	{
		char strCharToCheck = isCaseSensitive ? *str : toLower(*str);
		char suffixCharToCheck = isCaseSensitive ? *suffix : toLower(*suffix);
		
		if (strCharToCheck != suffixCharToCheck)
		{
			return false;
		}
		str++;
		suffix++;
	}

	return true;
}

