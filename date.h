#pragma once

bool isLeapYear(unsigned year);

unsigned getDaysInMonth(
	unsigned month,
	unsigned year);

void incrementDate();

void incrementDate(char* const date);

void numsToDate(
	char* const date,
	unsigned day,
	unsigned month,
	unsigned year);

bool addDate();

char* getDate();

unsigned extractDayFromDate(const char* date);

unsigned extractMonthFromDate(const char* date);

unsigned extractYearFromDate(const char* date);

bool isValidDate(const char* date);

bool isBefore(
	const char* date1,
	const char* date2);

void displayDate();