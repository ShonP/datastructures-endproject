#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#ifndef _CUSTOMERS_H_
#define _CUSTOMERS_H_

#pragma warning(disable:4996)
// create customer struct with dynamic items with joined date
typedef struct customer {
	int id;
	char name[32];
	char address[32];
	time_t date;
} customer;

// create linked list of customers that is sorted by joinedDate
typedef struct nodeCustomer {
	customer data;
	struct nodeCustomer* next;
} nodeCustomer;

// create addCustomer function and keep the list sorted by joinedDate
void addCustomer(nodeCustomer** customers, customer* data) {
	nodeCustomer* newNode = (nodeCustomer*)malloc(sizeof(nodeCustomer));
	newNode->data = *data;
	newNode->next = NULL;

	if (*customers == NULL) {
		*customers = newNode;
		return;
	}

	nodeCustomer* current = *customers;
	nodeCustomer* previous = NULL;
	while (current != NULL && current->data.date < newNode->data.date) {
		previous = current;
		current = current->next;
	}

	if (previous == NULL) {
		newNode->next = *customers;
		*customers = newNode;
	}
	else {
		newNode->next = current;
		previous->next = newNode;
	}
}

// remove Customer function by id and return success
int removeCustomer(nodeCustomer** customers, int id) {
	if (*customers == NULL) {
		return 0;
	}
	if ((*customers)->data.id == id) {
		nodeCustomer* temp = *customers;
		*customers = (*customers)->next;
		free(temp);
		return 1;
	}
	nodeCustomer* current = *customers;
	while (current->next != NULL && current->next->data.id != id) {
		current = current->next;
	}
	if (current->next == NULL) {
		return 0;
	}
	nodeCustomer* temp = current->next;
	current->next = current->next->next;
	free(temp);
	return 1;
}

// create initialize function of customers that reads from file and is sorted by joinedDate
void initializeCustomers(nodeCustomer** customers) {
	// allocate customers root
	*customers = NULL;
	FILE* fp = fopen("customers.bin", "r");
	if (fp == NULL) {
		printf("Initialize new file customers\n");
		// File doesn't exist, create it
		fp = fopen("customers.bin", "w");
		if (fp == NULL) {
			printf("Error creating file\n");
			return;
		}
	}
	else {
		printf("Loading existing customers file\n");
		// Read data from file and add it to the linked list
		while (1) {
			customer data;
			int result = fread(&data, sizeof(customer), 1, fp);
			if (result == 0) {
				break;
			}
			addCustomer(customers, &data);
		}
	}
}

// create search function by id
customer* searchCustomerById(nodeCustomer* customers, int id) {
	while (customers != NULL) {
		if (customers->data.id == id) {
			return &customers->data;
		}
		customers = customers->next;
	}
	return NULL;
}

//create search function by name
customer* searchCustomerByName(nodeCustomer* customers, char* name) {
	while (customers != NULL) {
		if (strcmp(customers->data.name, name) == 0) {
			return &customers->data;
		}
		customers = customers->next;
	}
	return NULL;
}

// create search function by address
customer* searchCustomerByAddress(nodeCustomer* customers, char* address) {
	while (customers != NULL) {
		if (strcmp(customers->data.address, address) == 0) {
			return &customers->data;
		}
		customers = customers->next;
	}
	return NULL;
}

// create search function by joinedDate
customer* searchCustomerByDate(nodeCustomer* customers, time_t date) {
	while (customers != NULL) {
		if (customers->data.date == date) {
			return &customers->data;
		}
		customers = customers->next;
	}
	return NULL;
}

// create print function
void printCustomer(customer* data) {
	printf("Customer ID: %d\n", data->id);
	printf("Customer Name: %s\n", data->name);
	printf("Customer Address: %s\n", data->address);
	printf("Customer Joined Date: %s", ctime(&data->date));
}

// create print all linkedlist
void printCustomers(nodeCustomer* customers) {
	while (customers != NULL) {
		printCustomer(&customers->data);
		customers = customers->next;
	}
}

// create save function that saves the list to file
void saveCustomers(nodeCustomer* customers) {
	FILE* fp = fopen("customers.bin", "w");
	if (fp == NULL) {
		printf("Error creating file\n");
		return;
	}
	while (customers != NULL) {
		fwrite(&customers->data, sizeof(customer), 1, fp);
		customers = customers->next;
	}
	fclose(fp);
}
#endif