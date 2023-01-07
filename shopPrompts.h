#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#include "customerItem.h"
#include "customers.h"

#ifndef _SHOP_H_
#define _SHOP_H_

#pragma warning(disable:4996)

// create buy prompt function
void buyPrompt(nodeCustomer** customers, nodeItem** items, customerItem** customerItems, int* size) {
	int customerId;
	int itemId;
	printf("Enter customer id: ");
	scanf("%d", &customerId);

	// search customer by id
	nodeCustomer* customer = searchCustomerById(*customers, customerId);
	if (customer == NULL) {
		printf("Wrong customer id");
		return;
	}
	printf("Enter item id: ");
	scanf("%d", &itemId);
	// search item by id
	nodeItem* item = searchByIdItem(*items, itemId);
	if (item == NULL) {
		printf("Wrong item id");
		return;
	}
	addCustomerItem(customerItems, size, customerId, itemId);
	saveCustomerItems(*customerItems, *size);
}


// create refund function prompt and only refund if purchaseDate in last 14 days
void refundPrompt(nodeCustomer** customers, nodeItem** items, customerItem** customerItems, int* size) {
	int customerId;
	int itemId;
	printf("Enter customer id: ");
	scanf("%d", &customerId);

	// search customer by id
	nodeCustomer* customer = searchCustomerById(*customers, customerId);
	if (customer == NULL) {
		printf("Wrong customer id");
		return;
	}
	printf("Enter item id: ");
	scanf("%d", &itemId);
	// search item by id
	nodeItem* item = searchByIdItem(*items, itemId);
	if (item == NULL) {
		printf("Wrong item id");
		return;
	}
	// search customer item by customer id and item id
	customerItem* customerItem = searchCustomerItemByCustomerIdAndItemId(*customerItems, *size, customerId, itemId);
	if (customerItem == NULL) {
		printf("Customer didn't buy this item");
		return;
	}
	// check if purchase date is in last 14 days
	if (isPurchaseDateInLast14Days(*customerItems, *size, customerId)) {
		removeCustomerItem(customerItems, size, customerId, itemId);
		saveCustomerItems(*customerItems, *size);
	}
	else {
		printf("Can't refund because purchase date is not in last 14 days");
	}
}

#endif