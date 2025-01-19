#pragma once
#include "role.h"

const unsigned EXIT_OPTION = 1;

void displayPanel(Role role);

int promptForOption(Role role);

void routeToOption(int option, Role role);

bool isValidOption(
	int option,
	Role role);
