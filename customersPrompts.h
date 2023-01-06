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
	system("cls");
	customer* customer = malloc(sizeof(customer));

	printf("Enter customer id: ");
	scanf("%d", &customer->id);
	printf("Enter customer name: ");
	scanf("%s", customer->name);
	printf("Enter customer address: ");
	scanf("%s", customer->address);
	customer->date = time(NULL);

	addCustomer(customers, customer);

	char log[100];
	snprintf(log, sizeof(log), "%s created customer successfully", customer->name);
	logMessage(&log);
	saveCustomers(*customers);
}

// Remove a customer prompt
void deleteCustomerPrompt(nodeCustomer** customers) {
	system("cls");
	int id;
	printf("Enter id: ");
	scanf("%d", &id);
	removeCustomer(customers, id);

	char log[100];
	snprintf(log, sizeof(log), "%d removed customer successfully", id);
	logMessage(&log);
	saveCustomers(*customers);
}

// search customer by full name prompt with searchCustomerByName
void searchCustomerByNamePrompt(nodeCustomer* customers) {
	system("cls");
	char name[32];
	printf("Enter name: ");
	scanf("%s", name);
	nodeCustomer* result = searchCustomerByName(customers, name);
	if (result == NULL) {
		printf("No customer found with name %s");
	}
	else {
		printCustomer(result);
	}
}

// view all customers prompt with printCustomers
void viewAllCustomersPrompt(nodeCustomer* customers) {
	system("cls");
	printCustomers(customers);
}

#endif