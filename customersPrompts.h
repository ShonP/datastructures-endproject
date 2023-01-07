#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"
#include "customer.h"

#ifndef _CUSTOMERS_PROMPTS_H
#define _CUSTOMERS_PROMPTS_H

#pragma warning(disable:4996)

// delete a customer prompt
void deleteCustomerPrompt(nodeCustomer** customers) {
	int id;
	printf("Enter customer id: ");
	scanf("%d", &id);
	if (removeCustomer(customers, id)) {
		char log[100];
		snprintf(log, sizeof(log), "%d removed employee successfully", id);
		logMessage(&log);
		saveCustomers(*customers);
	}
	else {
		printf("Customer not found\n");
	}
}

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
	printCustomers(customers);
}


void level1CustomerPrompts(nodeCustomer** customers) {
	int choice;
	do {
		printf("1. View all customers\n");
		printf("2. Search customer by name\n");
		printf("3. Create customer\n");
		printf("0. Back\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			viewAllCustomersPrompt(*customers);
			break;
		case 2:
			searchCustomerByNamePrompt(*customers);
			break;
		case 3:
			createCustomerPrompt(&customers);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);
}

void level2CustomerPrompts(nodeCustomer** customers) {
	int choice;
	do {
		system("cls");
		printf("1. View all customers\n");
		printf("2. Search customer by name\n");
		printf("3. Create customer\n");
		printf("0. Back\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			viewAllCustomersPrompt(*customers);
			break;
		case 2:
			searchCustomerByNamePrompt(*customers);
			break;
		case 3:
			createCustomerPrompt(customers);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);
}

void level3CustomerPrompts(nodeCustomer** customers) {
	int choice;
	do {
		system("cls");
		printf("1. View all customers\n");
		printf("2. Search customer by name\n");
		printf("3. Create customer\n");
		printf("4. Delete customer\n");
		printf("0. Back\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			viewAllCustomersPrompt(*customers);
			break;
		case 2:
			searchCustomerByNamePrompt(*customers);
			break;
		case 3:
			createCustomerPrompt(customers);
			break;
		case 4:
			deleteCustomerPrompt(customers);
			break;
		case 0:
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);
}

#endif