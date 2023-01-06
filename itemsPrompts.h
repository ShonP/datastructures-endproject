#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"
#include "items.h"

#ifndef _ITEMS_PROMPTS_H
#define _ITEMS_PROMPTS_H
#pragma warning(disable:4996)
//create item prompt by addItem function nodeItem
void createItemPrompt(nodeItem** items) {
	system("cls");
	item* data = malloc(sizeof(item));
	printf("Enter item id: ");
	scanf("%d", &data->id);
	printf("Enter item name: ");
	scanf("%s", data->phoneName);
	printf("Enter item brand: ");
	scanf("%s", data->brand);
	printf("Enter item price: ");
	scanf("%f", &data->price);
	printf("Enter item isNew: ");
	scanf("%d", &data->isNew);
	data->date = time(NULL);
	
	
	addItem(items, data);

	char log[100];
	snprintf(log, sizeof(log), "%s created item successfully", data->phoneName);
	logMessage(&log);
	saveItems(*items);
}

//delete item prompt by removeItem function nodeItem
void deleteItemPrompt(nodeItem** items) {
	system("cls");
	int id;
	printf("Enter id: ");
	scanf("%d", &id);
	removeItem(items, id);

	char log[100];
	snprintf(log, sizeof(log), "%d removed item successfully", id);
	logMessage(&log);
	saveItems(*items);
}

//view all items by printTree function nodeItem
void viewAllItemsPrompt(nodeItem* items) {
	system("cls");
	printTreeItems(items);
}

//search item by id prompt by searchByIdItem function nodeItem
void searchItemByIdPrompt(nodeItem* items) {
	system("cls");
	int id;
	printf("Enter id: ");
	scanf("%d", &id);
	nodeItem* result = searchByIdItem(items, id);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
	}
}

//search item by phone name prompt by searchByPhoneNameItem function nodeItem
void searchItemByPhoneNamePrompt(nodeItem* items) {
	system("cls");
	char phoneName[32];
	printf("Enter phone name: ");
	scanf("%s", phoneName);
	nodeItem* result = searchByPhoneNameItem(items, phoneName);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
	}
}

//search item by brand prompt by searchByBrandItem function nodeItem
void searchItemByBrandPrompt(nodeItem* items) {
	system("cls");
	char brand[32];
	printf("Enter brand: ");
	scanf("%s", brand);
	nodeItem* result = searchByBrandItem(items, brand);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
	}
}

// search item by price prompt by searchByPriceItem function nodeItem
void searchItemByPricePrompt(nodeItem* items) {
	system("cls");
	float price;
	printf("Enter price: ");
	scanf("%f", &price);
	nodeItem* result = searchByPriceItem(items, price);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
	}
}

// search item by isNew prompt by searchByIsNewItem function nodeItem
void searchItemByIsNewPrompt(nodeItem* items) {
	system("cls");
	int isNew;
	printf("Enter isNew: ");
	scanf("%d", &isNew);
	nodeItem* result = searchByIsNewItem(items, isNew);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
	}
}

// search item by date prompt by searchByDateItem function nodeItem
void searchItemByDatePrompt(nodeItem* items) {
	system("cls");
	long date;
	printf("Enter date: ");
	scanf("%ld", &date);
	nodeItem* result = searchByDateItem(items, date);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
	}
}


#endif