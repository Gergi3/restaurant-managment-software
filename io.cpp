#include "generalConstants.h"
#include "io.h"
#include "string.h";
#include <iostream>

const unsigned MAX_CIN_BUFFER_SIZE = GENERAL_CONSTANTS::INPUT_BUFFER_SIZE;

void input(char* result)
{
	std::cin.getline(result, MAX_CIN_BUFFER_SIZE, '\n');
}

void input(int& result)
{
	char resultStr[MAX_CIN_BUFFER_SIZE]{};

	std::cin.getline(resultStr, MAX_CIN_BUFFER_SIZE, '\n');

	result = strToNum(resultStr);
}

void input(unsigned& result)
{
	char resultStr[MAX_CIN_BUFFER_SIZE]{};

	std::cin.getline(resultStr, MAX_CIN_BUFFER_SIZE, '\n');

	result = strToUnsigned(resultStr);
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
	const char toPrint,
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