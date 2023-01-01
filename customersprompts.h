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
	printf("Enter the id: ");
	int id;
	scanf("%d", &id);
	if (searchCustomerById(*customers, id) != NULL) {
		printf("Customer with id %d already exists\n", id);
		return;
	}
	printf("Enter the name: ");
	char name[32];
	scanf("%s", name);
	printf("Enter the address: ");
	char address[32];
	scanf("%s", address);
	customer data;
	data.id = id;
	strcpy(data.name, name);
	strcpy(data.address, address);
	data.itemsCount = 0;
	data.items = NULL;
	data.date = time(NULL);
	addCustomer(customers, data);
	saveCustomers(*customers);
	logMessage("Customer created" + id);
}

// Remove a customer prompt
void removeCustomerPrompt(nodeCustomer** customers) {
	printf("Enter the id: ");
	int id;
	scanf("%d", &id);
	nodeCustomer* customer = searchCustomerById(*customers, id);
	if (customer == NULL) {
		printf("Customer with id %d does not exist\n", id);
		return;
	}
	removeCustomer(customers, customer->data.id);
	saveCustomers(*customers);
	logMessage("Customer removed" + id);
}

#endif