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

void createItemPrompt(nodeItem** items) {
	printf("Enter the id: ");
	int id;
	scanf("%d", &id);
	if (searchByIdItem(*items, id) != NULL) {
		printf("Item with id %d already exists\n", id);
		return;
	}
	printf("Enter the field1: ");
	char field1[32];
	scanf("%s", field1);
	printf("Enter the field2: ");
	char field2[32];
	scanf("%s", field2);
	printf("Enter the value: ");
	float value;
	scanf("%f", &value);
	printf("Enter the boolean: ");
	bool boolean = 0;

	item data;
	data.id = id;
	strcpy(data.field1, field1);
	strcpy(data.field2, field2);
	data.value = value;
	data.boolean = boolean;
	data.date = time(NULL);

	addItem(items, data);
	saveItems(*items);
	logMessage("Item created" + id);
}

void removeItemPrompt(nodeItem** items) {
	printf("Enter the id: ");
	int id;
	scanf("%d", &id);
	nodeItem* item = searchByIdItem(*items, id);
	if (item == NULL) {
		printf("Item with id %d does not exist\n", id);
		return;
	}
	removeItem(items, item->data.id);
	saveItems(*items);
	logMessage("Item removed" + id);
}


void searchItemByIdPrompt(nodeItem** items) {
	printf("Enter the id: ");
	int id;
	scanf("%d", &id);
	nodeItem* item = searchByIdItem(*items, id);
	if (item == NULL) {
		printf("Item with id %d does not exist\n", id);
		return;
	}
	printf("id: %d, field1: %s, field2: %s, value: %f, boolean: %d, date: %ld\n", item->data.id, item->data.field1, item->data.field2, item->data.value, item->data.boolean, item->data.date);
}

#endif