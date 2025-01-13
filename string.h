#pragma once
#include "role.h"
#include "inventoryItem.h";

char* toString(unsigned num);

const char* toString(Role role);

void reverseStringMutate(char* str);

void reverseStringMutate(char* str, unsigned len);

char digitToChar(unsigned num);

void concatMutate(char* lhs, const char* rhs);

void concatMutate(char* lhs, unsigned num);

void copyMutate(char* dest, const char* source);

unsigned length(const char const* str);

unsigned countSuffixChars(const char const* str, char ch);

unsigned countPrefixChars(const char const* str, char ch);

void shiftLeftMutate(char* str, unsigned pos = 1);

void trimLeftMutate(char* str, char ch = ' ');

void trimRightMutate(char* str, char ch = ' ');

void trimMutate(char* str, char ch = ' ');

char toLower(char ch);

bool contains(
	const char const* str,
	const char const* toContain,
	bool isCaseSensitive = true);

bool isSuffix(
	const char const* str,
	const char const* suffix,
	bool isCaseSensitive = true);

