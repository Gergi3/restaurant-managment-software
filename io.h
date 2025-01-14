#pragma once

void input(
	char* result,
	unsigned maxInputChars = 1024);

void input(int& result);

void input(unsigned& result);

void print(
	const char const* toPrint,
	unsigned newLinesCount = 1);

void print(
	unsigned toPrint,
	unsigned newLinesCount = 1);

void printNewLines(unsigned count = 1);

void printNewLine();

void clearErrorFlagsFromCin();

void forceClearErrorFlagsFromCin();

void clearConsole();