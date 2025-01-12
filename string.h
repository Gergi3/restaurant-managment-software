#pragma once

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

