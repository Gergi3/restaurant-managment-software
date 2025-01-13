#include "string.h"
#include "user.h"
#include "inventoryItem.h"
#include <iostream>
#include "misc.h"

const char* toString(Role role)
{
	switch (role)
	{
		case Role::Manager: return "Manager";
		case Role::Server: return "Server";
		default: nullptr;
	}
}

char* toString(unsigned num)
{
	unsigned len = getDigitsCount(num);
	char* strNum = new char[len + 1]
		{};

	for (int i = 0; i < len; i++)
	{
		strNum[i] = digitToChar(num % 10);
		num /= 10;
	}

	reverseStringMutate(strNum, len);

	return strNum;
}

void reverseStringMutate(char* str, unsigned len)
{
	if (!str)
	{
		return;
	}

	for (int i = 0; i < len / 2; i++)
	{
		swap(str[i], str[len - i - 1]);
	}
}

void reverseStringMutate(char* str)
{
	unsigned len = length(str);
	reverseStringMutate(str, len);
}

char digitToChar(unsigned num)
{
	if (num >= 10)
	{
		return ' ';
	}

	return num + '0';
}

void concatMutate(char* lhs, unsigned num)
{
	char* numAsStr = toString(num);
	concatMutate(lhs, numAsStr);
	
	delete[] numAsStr;
	numAsStr = nullptr;
}

void concatMutate(char* lhs, const char* rhs)
{
	if (!lhs || !rhs)
	{
		return;
	}

	size_t lhsLen = length(lhs);
	lhs += lhsLen;
	copyMutate(lhs, rhs);
}

void copyMutate(char* dest, const char* source)
{
	if (!source || !dest)
		return;

	while (*source)
	{
		*dest = *source;

		dest++;
		source++;
	}

	*dest = '\0';
}

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

