//#include <stdio.h>
//#include <stdlib.h>
//#include "employees.h"
//#include "items.h"
//#include "itemsprompts.h"
//#include "customers.h"
//#include "customersprompts.h"
//#include "logs.h"
//
//void level1Menu(nodeItem** items, employee** employees, size_t* numEmployees) {
//	printf("1. Add item\n");
//	printf("2. Search items\n");
//	printf("3. Exit\n");
//	printf("Enter your choice: ");
//	int choice;
//	scanf("%d", &choice);
//	switch (choice) {
//	case 1:
//		printf("Creating new item:\n\n");
//		createItemPrompt(items);
//		break;
//	case 2:
//		printf("Searching new item:\n\n");
//		searchItemByIdPrompt(items);
//		break;
//	case 3:
//		exit(0);
//		break;
//	default:
//		printf("Invalid choice\n");
//		break;
//	}
//}
//
//int main(int argc, char* argv[]) {
//	// Open the input file
//	initializeLogs();
//	employee* employees;
//	size_t employees_size = initializeEmployees(&employees);
//	nodeItem* items = initializeItems();
//	customer* customers;
//	initializeCustomers(&customers);
//
//
//
//	// Save changes to file
//	//save(root);
//
//	// Free tree memory
//
//
//	employee* loggedInEmployee = login(employees_size, employees);
//	switch (loggedInEmployee->accessLevel) {
//	case 1:
//		// Call function for level 1
//		level1Menu(&items, &employees, &employees_size);
//		break;
//	case 2:
//		// Call function for level 2
//		break;
//	case 3:
//		// Call function for level 3
//		level1Menu(&items, &employees, &employees_size);
//		break;
//	default:
//		// Call function for level 4
//		break;
//	}
//
//
//	// Try to login with the provided username and password
//
//	freeTreeItems(items);
//	free(employees);
//	return 0;
//}