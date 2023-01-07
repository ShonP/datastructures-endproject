#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customerItem.h"
#include "item.h"

#ifndef _CUSTOMER_ITEM_PROMPTS_H_
#define _CUSTOMER_ITEM_PROMPTS_H_

#pragma warning(disable:4996)

// create addCustomerItemPrompt with array of customerItems and size
void addCustomerItemPrompt(customerItem** customerItems, int* size) {
	int customerId;
	int itemId;
	printf("Enter customer id: ");
	scanf("%d", &customerId);
	printf("Enter item id: ");
	scanf("%d", &itemId);
	addCustomerItem(customerItems, size, customerId, itemId);
}

// create view all customer items prompt function
void viewAllCustomerItemsPrompt(customerItem* customerItems, int size, item* root, customer* customers) {
	viewAllCustomerItems(customerItems, size, root, customers);
}

#endif