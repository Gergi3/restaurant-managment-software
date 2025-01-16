#pragma once
#include "menuItem.h"
#include "orderItem.h"

bool validateOrderItem(
	OrderItem* item,
	int*& failCodes);

bool validateOrderItemMenuItem(
	const char* const name,
	int*& failCodes);

void displayOrderItemFailCodeMessage(int failCode);
