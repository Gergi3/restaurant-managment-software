#pragma once
#include "role.h"

const unsigned EXIT_OPTION = 1;

void displayPanel(Role role);

int promptForOption(Role role);

void routeToOption(
	int option,
	Role role);

bool isValidOption(
	int option,
	Role role);

void runExitOption(Role role);

void runShowMenuOption();

void runAddToMenuOption(int*& failCodes);

void runRemoveFromMenuOption(int*& failCodes);

void runShowOrdersOption();

void runShowOrdersWithCountOption();

void runPlaceOrderOption(int*& failCodes);

void runCancelOrderOption(int*& failCodes);

void runShowInventoryOption();

void runAddToInventoryOption(int*& failCodes);

void runRemoveFromInventoryOption(int*& failCodes);

void runCurrentRevenueOption();

void runEndRevenueOption();

void runRevenueFromDateToTodayOption(int*& failCodes);
