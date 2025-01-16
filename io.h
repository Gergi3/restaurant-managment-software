#pragma once

void input(char* result);

void input(int& result);

void input(unsigned& result);

void print(
	const char* const toPrint,
	unsigned newLinesCount = 1);

void print(
	const char toPrint,
	unsigned newLinesCount = 1);

void print(
	unsigned toPrint,
	unsigned newLinesCount = 1);

void printNewLines(unsigned count = 1);

void printNewLine();

void clearErrorFlagsFromCin();

void forceClearErrorFlagsFromCin();

void clearConsole();