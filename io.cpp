#include <iostream>
#include "io.h"


void input(
	char* result,
	unsigned maxInputChars)
{
	if (maxInputChars == 0)
	{
		return;
	}

	std::cin.getline(result, maxInputChars);
}

void print(
	const char const* toPrint,
	unsigned newLinesCount)
{
	std::cout << toPrint;
	printNewLines(newLinesCount);
}

void printNewLines(unsigned count)
{
	while (count)
	{
		printNewLine();
		count--;
	}
}

void printNewLine()
{
	std::cout << std::endl;
}