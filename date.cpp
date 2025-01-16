#include "date.h"
#include "dateConstants.h"
#include "garbageCollector.h"
#include "io.h"
#include "stream.h"
#include "string.h"
#include <fstream>
#include <iostream>

bool isLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned getDaysInMonth(unsigned month, unsigned year)
{
	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 4: case 6: case 9: case 11:
			return 30;
		case 2:
			return isLeapYear(year) ? 29 : 28;
		default:
			return 0;
	}
}

void incrementDate()
{
	char* date = getDate();
	incrementDate(date);

	std::ofstream ofs(DATE_CONSTANTS::FILE_NAME);
	if (!isValidStream(ofs))
	{
		return;
	}

	ofs << date;

	freeMemory(date);

	ofs.close();
}

void incrementDate(char* date)
{
	unsigned day = charToDigit(date[0]) * 10 + charToDigit(date[1]);
	unsigned month = charToDigit(date[3]) * 10 + charToDigit(date[4]);
	unsigned year = charToDigit(date[6]) * 1000 + charToDigit(date[7]) * 100 + charToDigit(date[8]) * 10 + charToDigit(date[9]);

	day++;

	if (day > getDaysInMonth(month, year))
	{
		day = 1;
		month++;

		if (month > 12)
		{
			month = 1;
			year++;
		}
	}

	date[0] = digitToChar(day / 10);
	date[1] = digitToChar(day % 10);
	date[3] = digitToChar(month / 10);
	date[4] = digitToChar(month % 10);
	date[6] = digitToChar(year / 1000);
	date[7] = digitToChar((year / 100) % 10);
	date[8] = digitToChar((year / 10) % 10);
	date[9] = digitToChar(year % 10);
}

bool addDate()
{
	std::fstream fs(DATE_CONSTANTS::FILE_NAME, std::ios::in | std::ios::out);
	if (!isValidStream(fs))
	{
		return false;
	}

	fs.peek();
	if (fs.eof())
	{
		fs.clear();
		fs << DATE_CONSTANTS::DEFAULT_DATE;
	}

	fs.close();
}

char* getDate()
{
	std::ifstream ifs(DATE_CONSTANTS::FILE_NAME);
	if (!isValidStream(ifs))
	{
		return nullptr;
	}

	char* date = new char[DATE_CONSTANTS::DATE_LENGTH + 1];
	ifs.getline(date, DATE_CONSTANTS::DATE_LENGTH + 1);

	ifs.close();

	return date;
}

void displayDate()
{
	char* date = getDate();

	print("Date: ", 0);
	print(date);

	freeMemory(date);
}