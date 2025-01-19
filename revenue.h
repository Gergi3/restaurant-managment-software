#pragma once

unsigned getCurrentRevenue();

bool displayRevenueFromDateToNow(
	char* date,
	int*& failCodes);

bool endCurrentRevenue();

void saveRevenue(
	std::ofstream& ofs, 
	unsigned revenue, 
	const char* const date);

void displayCurrentRevenue();

void displayRevenue(
	unsigned revenue, 
	const char* const date);