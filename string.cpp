#include "misc.h"
#include "role.h"
#include "string.h"
#include "userConstants.h"
#include <iostream>

const char* toString(Role role)
{
	switch (role)
	{
		case Role::Manager:
		{
			return USER_CONSTANTS::MANAGER_ROLE_LONG;
		}
		case Role::Server:
		{
			return USER_CONSTANTS::SERVER_ROLE_LONG;
		}
		default:
		{
			return nullptr;
		}
	}
}

char* toString(unsigned num)
{
	unsigned len = getDigitsCount(num);
	char* strNum = new char[len + 1]
		{};

	for (unsigned i = 0; i < len; i++)
	{
		strNum[i] = digitToChar(num % 10);
		num /= 10;
	}

	reverseStringMutate(strNum, len);

	return strNum;
}

void reverseStringMutate(
	char* str,
	unsigned len)
{
	if (!str)
	{
		return;
	}

	unsigned end = len / 2;
	for (unsigned i = 0; i < end; i++)
	{
		swap(str[i], str[len - i - 1]);
	}
}

void reverseStringMutate(char* str)
{
	if (!str)
	{
		return;
	}

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

unsigned charToDigit(char ch)
{
	if (!isDigitChar(ch))
	{
		return 0;
	}

	return ch - '0';
}

bool isDigitChar(char ch)
{
	return ch >= '0' && ch <= '9';
}

int strToNum(const char* const str)
{
	if (!str)
	{
		return 0;
	}

	if (*str == '-')
	{
		return -1 * strToUnsigned(str + 1);
	}

	return strToUnsigned(str);
}

unsigned strToUnsigned(const char* str)
{
	if (!str)
	{
		return 0;
	}

	unsigned int result = 0;

	while (*str)
	{
		if (!isDigitChar(*str))
		{
			return 0;
		}

		result = result * 10 + charToDigit(*str);
		str++;
	}

	return result;
}

void concatMutate(
	char* lhs,
	unsigned num)
{
	if (!lhs)
	{
		return;
	}

	char* numAsStr = toString(num);
	concatMutate(lhs, numAsStr);

	delete[] numAsStr;
	numAsStr = nullptr;
}

void concatMutate(
	char* lhs,
	const char* rhs)
{
	if (!lhs || !rhs)
	{
		return;
	}

	size_t lhsLen = length(lhs);
	lhs += lhsLen;

	copyMutate(lhs, rhs);
}

void copyMutate(
	char* dest,
	const char* source)
{
	if (!source || !dest)
	{
		return;
	}

	while (*source)
	{
		*dest = *source;

		dest++;
		source++;
	}

	*dest = '\0';
}

unsigned length(const char* str)
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

unsigned countSuffixChars(
	const char* str,
	char ch)
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

unsigned countPrefixChars(
	const char* str,
	char ch)
{
	if (!str || !strcmp(str, ""))
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

void shiftLeftMutate(
	char* str,
	unsigned pos)
{
	if (!str || !strcmp(str, ""))
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

void trimLeftMutate(
	char* str,
	char ch)
{
	if (!str || !strcmp(str, ""))
	{
		return;
	}

	unsigned counter = countSuffixChars(str, ch);
	shiftLeftMutate(str, counter);
}

void trimRightMutate(
	char* str,
	char ch)
{
	if (!str || !strcmp(str, ""))
	{
		return;
	}

	unsigned counter = countPrefixChars(str, ch);
	unsigned strLen = length(str);

	str[strLen - counter] = '\0';
}

void trimMutate(
	char* str,
	char ch)
{
	if (!str || !strcmp(str, ""))
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

unsigned countCharOccurances(
	const char* str,
	char toContain)
{
	if (!str)
	{
		return 0;
	}

	unsigned count = 0;
	while (*str)
	{
		count += *str == toContain;
		str++;
	}

	return count;
}

bool contains(
	const char* str,
	const char* const toContain,
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
	const char* str,
	const char* suffix,
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

