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

unsigned getDaysInMonth(
	unsigned month,
	unsigned year)
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

void incrementDate(char* const date)
{
	unsigned day = extractDayFromDate(date);
	unsigned month = extractMonthFromDate(date);
	unsigned year = extractYearFromDate(date);

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

	numsToDate(date, day, month, year);
}

void numsToDate(
	char* const date,
	unsigned day,
	unsigned month,
	unsigned year)
{
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

	return true;
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

unsigned extractDayFromDate(const char* date)
{
	return charToDigit(date[0]) * 10
		+ charToDigit(date[1]);
}

unsigned extractMonthFromDate(const char* date)
{
	return charToDigit(date[3]) * 10
		+ charToDigit(date[4]);
}

unsigned extractYearFromDate(const char* date)
{
	return charToDigit(date[6]) * 1000
		+ charToDigit(date[7]) * 100
		+ charToDigit(date[8]) * 10
		+ charToDigit(date[9]);
}

bool isValidDate(const char* date)
{
	for (int i = 0; i < 10; ++i)
	{
		if (i == 2 || i == 5)
		{
			if (date[i] != '.')
			{
				return false;
			}
		}
		else
		{
			if (date[i] < '0' || date[i] > '9')
			{
				return false;
			}
		}
	}

	unsigned day = extractDayFromDate(date);
	unsigned month = extractMonthFromDate(date);
	unsigned year = extractYearFromDate(date);

	if (month < 1 || month > 12)
	{
		return false;
	}

	unsigned daysInMonth = getDaysInMonth(month, year);
	if (day < 1 || day > daysInMonth)
	{
		return false;
	}

	return true;
}

bool isBefore(const char* date1, const char* date2)
{
	unsigned day1 = extractDayFromDate(date1);
	unsigned month1 = extractMonthFromDate(date1);
	unsigned year1 = extractYearFromDate(date1);

	unsigned day2 = extractDayFromDate(date2);
	unsigned month2 = extractMonthFromDate(date2);
	unsigned year2 = extractYearFromDate(date2);

	if (year1 < year2)
	{
		return true;
	}
	
	if (year1 > year2)
	{
		return false;
	}

	if (month1 < month2)
	{
		return true;
	}
	if (month1 > month2)
	{
		return false;
	}

	return day1 <= day2;
}

void displayDate()
{
	char* date = getDate();

	print("Date: ", 0);
	print(date);

	freeMemory(date);
}