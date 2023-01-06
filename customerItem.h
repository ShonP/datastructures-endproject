#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

#ifndef _CUSTOMER_ITEM_H_
#define _CUSTOMER_ITEM_H_

#pragma warning(disable:4996)
// create customer struct with dynamic items with joined date
typedef struct customerItem {
	int generatedId;
	int customerId;
	int itemId;
} customerItem;


// create addCustomerItem with array of customerItems and size
void addCustomerItem(customerItem** customerItems, int* size, int customerId, int itemId) {
	customerItem* newCustomerItem = (customerItem*)malloc(sizeof(customerItem));
	newCustomerItem->generatedId = *size + 1;
	newCustomerItem->customerId = customerId;
	newCustomerItem->itemId = itemId;

	(*size)++;
	*customerItems = (customerItem*)realloc(*customerItems, *size * sizeof(customerItem));
	(*customerItems)[*size - 1] = *newCustomerItem;
}
// remove addCustomerItem with array of customerItems and size by customerId and itemId
void removeCustomerItem(customerItem** customerItems, int* size, int customerId, int itemId) {
	for (int i = 0; i < *size; i++) {
		if ((*customerItems)[i].customerId == customerId && (*customerItems)[i].itemId == itemId) {
			for (int j = i; j < *size - 1; j++) {
				(*customerItems)[j] = (*customerItems)[j + 1];
			}
			(*size)--;
			*customerItems = (customerItem*)realloc(*customerItems, *size * sizeof(customerItem));
			return;
		}
	}
}

int initializeCustomerItems(customerItem** customerItems) {
	FILE* infile = fopen("customerItem.bin", "rb");
	int i;
	int array_size;
	customerItem* d_array;
	// Check if the input file exists
	if (!infile) {
		printf("Initialize new file customerItem\n");
		// If the input file does not exist, create an empty array of structs
		array_size = 1;
		d_array = malloc(array_size * sizeof(customerItem));
	}
	else {
		// If the input file exists, read the data from the file and store it in an array of structs
		printf("Loading existing customerItem file\n");
		fread(&array_size, sizeof(int), 1, infile);
		d_array = malloc(array_size * sizeof(customerItem));
		for (i = 0; i < array_size; i++) {
			fread(&d_array[i], sizeof(customerItem), 1, infile);
		}
		fclose(infile);
	}
	*customerItems = d_array;
	return array_size;
}



#endif