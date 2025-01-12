#include "string.h";

unsigned length(const char const* str)
{
	if (!str)
	{
		return 0;
	}

	unsigned counter = 0;
	while (*str)
	{
		counter++;
		str++;
	}

	return counter;
}

unsigned countSuffixChars(const char const* str, char ch)
{
	if (!str)
	{
		return 0;
	}

	unsigned count = 0;
	while (*str == ch)
	{
		count++;
		str++;
	}

	return count;
}

unsigned countPrefixChars(const char const* str, char ch)
{
	if (!str)
	{
		return 0;
	}

	str += length(str) - 1;
	
	unsigned count = 0;
	while (*str == ch)
	{
		count++;
		str--;
	}

	return count;
}

void shiftLeftMutate(char* str, unsigned pos)
{
	if (!str)
	{
		return;
	}

	unsigned rhs = pos;
	unsigned lhs = 0;

	while (str[rhs])
	{
		str[lhs] = str[rhs];
		rhs++;
		lhs++;
	}

	str[lhs] = '\0';
}

void trimLeftMutate(char* str, char ch)
{
	if (!str)
	{
		return;
	}

	unsigned counter = countSuffixChars(str, ch);
	shiftLeftMutate(str, counter);
}

void trimRightMutate(char* str, char ch)
{
	if (!str)
	{
		return;
	}

	unsigned counter = countPrefixChars(str, ch);
	unsigned strLen = length(str);

	str[strLen - counter] = '\0';
}

void trimMutate(char* str, char ch)
{
	if (!str)
	{
		return;
	}

	trimLeftMutate(str, ch);
	trimRightMutate(str, ch);
}

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

