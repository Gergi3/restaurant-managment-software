#include "io.h"
#include <iostream>

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

void input(int& result)
{
	std::cin >> result;
}

void input(unsigned& result)
{
	std::cin >> result;
}

void clearErrorFlagsFromCin()
{
	if (std::cin.fail())
	{
		forceClearErrorFlagsFromCin();
	};
}

void forceClearErrorFlagsFromCin()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void print(
	const char const* toPrint,
	unsigned newLinesCount)
{
	std::cout << toPrint;
	printNewLines(newLinesCount);
}

void print(
	unsigned toPrint,
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

void clearConsole()
{
	system("cls");
}

