#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"
#include "item.h"

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

//void search item by brand prompt by searchByBrandItem function listItem
void searchItemByBrandPrompt(nodeItem* items) {
	system("cls");
	char brand[32];
	printf("Enter brand: ");
	scanf("%s", brand);
	listItem* result = searchByBrandItem(items, brand);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		while (result != NULL) {
			printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
			result = result->next;
		}
	}
}
void searchItemByIsNewPrompt(nodeItem* items) {
	system("cls");
	int isNew;
	printf("Enter isNew: ");
	scanf("%d", &isNew);
	listItem* result = searchByIsNewItem(items, isNew);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		while (result != NULL) {
			printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
			result = result->next;
		}
	}
}

void itemPrompts(nodeItem** root, int accessLevel) {
	system("cls");
	int choice;
	do {
		printf("1. View all items\n");
		printf("2. Create item\n");
		printf("3. Search item by id\n");
		printf("4. Search item by phone name\n");
		printf("5. Search item by brand\n");
		printf("6. Search item by isNew\n");
		if (accessLevel == 2) {
			//update employee printf
		}
		if (accessLevel == 3) {
			printf("8. Delete item\n");
		}
		printf("0. Back\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			viewAllItemsPrompt(*root);
			break;
		case 2:
			createItemPrompt(root);
			break;
		case 3:
			searchItemByIdPrompt(*root);
			break;
		case 4:
			searchItemByPhoneNamePrompt(*root);
			break;
		case 5:
			searchItemByBrandPrompt(*root);
			break;
		case 6:
			searchItemByIsNewPrompt(*root);
			break;
		case 7:
			if (accessLevel == 2) {
				//update employee
			}
			else {
				printf("Invalid choice\n");
			}
			break;
		case 8:
			if (accessLevel == 3) {
				deleteItemPrompt(root);
			}
			else {
				printf("Invalid choice\n");
			}
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