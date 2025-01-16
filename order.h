#pragma once
#include "orderItem.h"

bool addToOrder(
	OrderItem* item,
	int*& failCodes);

bool addToOrder(const char const* menuItemName, int*& failCodes);

void addToOrder(std::ofstream& ofs, unsigned id, const char const* menuItemName);

bool appendToOrder(const char const* menuItemName);

OrderItem** getAllOrders();

void setItemValues(std::ifstream& ifs, OrderItem*& item);

OrderItem* getOrder(unsigned id);

bool removeOrder(unsigned id, int*& failCodes, OrderItem** items = nullptr);

bool orderExists(unsigned id);

unsigned getAndIncrementNextId();

unsigned getCurrentId();

unsigned getItemsCount(OrderItem** items);

void sortOrderItems(OrderItem** items);

void displayOrderItems(OrderItem** items, bool withCount = false);

void displayOrderItem(OrderItem* item, bool withCount = false);