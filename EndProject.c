#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include "items.h"
#include "logs.h"

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

void searchItemPrompt(nodeItem** items) {
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

void removeItemPrompt(nodeItem** items) {
	printf("Enter the id: ");
	int id;
	scanf("%d", &id);
	nodeItem* item = searchByIdItem(*items, id);
	if (item == NULL) {
		printf("Item with id %d does not exist\n", id);
		return;
	}
	removeItem(items, item);
	saveItems(*items);
	logMessage("Item removed" + id);
}

void level1Menu(nodeItem** items, employee** employees, size_t* numEmployees) {
	printf("1. Add item\n");
	printf("2. Search items\n");
	printf("3. Exit\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		printf("Creating new item:\n\n");
		createItemPrompt(items);
		break;
	case 2:
		printf("Searching new item:\n\n");
		searchItemPrompt(items);
		break;
	case 3:
		exit(0);
		break;
	default:
		printf("Invalid choice\n");
		break;
	}
}

int main(int argc, char* argv[]) {
	// Open the input file
	initializeLogs();
	employee* employees;
	size_t employees_size = initializeEmployees(&employees);
	nodeItem* items = initializeItems();


	// Save changes to file
	//save(root);

	// Free tree memory


	employee* loggedInEmployee = login(employees_size, employees);
	switch (loggedInEmployee->accessLevel) {
	case 1:
		// Call function for level 1
		level1Menu(&items, &employees, &employees_size);
		break;
	case 2:
		// Call function for level 2
		break;
	case 3:
		// Call function for level 3
		level1Menu(&items, &employees, &employees_size);
		break;
	default:
		// Call function for level 4
		break;
	}


	// Try to login with the provided username and password

	freeTreeItems(items);
	free(employees);
	return 0;
}