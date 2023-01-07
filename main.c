#include <stdio.h>
#include <stdlib.h>
#include "logs.h"
#include "employee.h"
#include "employeePrompts.h"
#include "items.h"
#include "itemsPrompts.h"
#include "customers.h"
#include "customersPrompts.h"
#include "customerItemPrompots.h"
#include "customerItem.h"
#include "shopPrompts.h"

// create void function that include all employee prompts
void employeePrompts(employee** employees, int* employeeSize) {
	system("cls");
	int choice = 0;
	while (choice != 5) {
		printf("-----------------\n\n\n\n");
		printf("1. Create employee\n");
		printf("2. Remove employee\n");
		printf("3. Search employee by full name\n");
		printf("4. View all employees\n");
		printf("5. Back\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			createEmployeePrompt(employees, employeeSize);
			break;
		case 2:
			removeEmployeePrompt(employees, employeeSize);
			break;
		case 3:
			searchEmployeeByFullNamePrompt(*employees, *employeeSize);
			break;
		case 4:
			viewAllEmployeesPrompt(*employees, *employeeSize);
			break;
		case 5:
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}

// create void function that include all item prompts
void itemPrompts(nodeItem** items) {
	int choice = 0;
	while (choice != 5) {
		printf("-----------------\n\n\n\n");
		printf("1. Create item\n");
		printf("2. Remove item\n");
		printf("3. Search item by id\n");
		printf("4. View all items\n");
		printf("5. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			createItemPrompt(items);
			break;
		case 2:
			deleteItemPrompt(items);
			break;
		case 3:
			searchItemByIdPrompt(*items);
			break;
		case 4:
			viewAllItemsPrompt(*items);
			break;
		case 5:
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}

// create void function that include all customer prompts
void customerPrompts(nodeCustomer** customers) {
	int choice = 0;
	while (choice != 5) {
		printf("-----------------\n\n\n\n");
		printf("1. Create customer\n");
		printf("2. Remove customer\n");
		printf("3. Search customer by full name\n");
		printf("4. View all customers\n");
		printf("5. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			createCustomerPrompt(customers);
			break;
		case 2:
			deleteCustomerPrompt(customers);
			break;
		case 3:
			searchCustomerByNamePrompt(*customers);
			break;
		case 4:
			viewAllCustomersPrompt(*customers);
			break;
		case 5:
			exit(0);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}

// create all view prompts prompt
void level1Prompts(employee** employees, int* employeeSize, nodeItem** items) {
	system("cls");
	int choice = 0;
	while (choice != 5) {
		printf("-----------------\n\n\n\n");
		printf("1. View employee menu\n");
		printf("2. View item menu\n");
		printf("3. View customer menu\n");
		printf("4. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			level1EmployeePrompts(employees, employeeSize);
			break;
		case 2:
			level1ItemPrompts(items);
		case 4:
			exit(0);
			break;
		}


	}
}


int main(int argc, char* argv[]) {
	initializeLogs();
	employee* employees;
	int employeeSize = initializeEmployees(&employees);
	employee* loggedEmployee = loginPrompt(employeeSize, employees, 1);
	nodeItem* items = initializeItems();
	nodeCustomer* customers;
	initializeCustomers(&customers);
	customerItem* customerItems;

	int customerItemsSize = initializeCustomerItems(&customerItems);
	level1Prompts(&employees, &employeeSize, &items);
	//createItemPrompt(&items);
	//itemPrompts(&items);
	//customerPrompts(&customers);
	// buy item using buyPrompt
	//viewAllCustomersPrompt(customers);
	//viewAllItemsPrompt(items);
	//viewAllCustomerItemsPrompt(customerItems, customerItemsSize);
	//viewAllItemsPrompt(items);
	//buyPrompt(&customers, &items, &customerItems, &customerItemsSize);
	return 0;
}