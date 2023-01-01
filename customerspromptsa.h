#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"
#include "customers.h"

#ifndef _CUSTOMERS_PROMPTS_H
#define _CUSTOMERS_PROMPTS_H

#pragma warning(disable:4996)

// Create a new customer prompt with empty items
void createCustomerPrompt(nodeCustomer** customers) {
	customer data;
	printf("Enter customer id: ");
	scanf("%d", &data.id);
	printf("Enter customer name: ");
	scanf("%s", data.name);
	printf("Enter customer address: ");
	scanf("%s", data.address);
	data.itemsCount = 0;
	data.items = NULL;
	data.date = time(NULL);

	addCustomer(customers, data);

	char log[100];
	snprintf(log, sizeof(log), "%s created customer successfully", data.name);
	logMessage(&log);
	saveCustomers(*customers);
}

// Remove a customer prompt
void deleteCustomerPrompt(nodeCustomer** customers) {
	int id;
	printf("Enter id: ");
	scanf("%d", &id);
	removeCustomer(customers, id);

	char log[100];
	snprintf(log, sizeof(log), "%d removed customer successfully", id);
	logMessage(&log);
	saveCustomers(*customers);
}

#endif