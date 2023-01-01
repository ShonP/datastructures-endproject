#include <stdio.h>
#include <stdlib.h>
#include "logs.h"
#include "employee.h"
#include "employeePrompts.h"

// create void function that include all employee prompts
void employeePrompts(employee** employees, int* employeeSize) {
	int choice = 0;
	while (choice != 5) {
		printf("-----------------\n\n\n\n");
		printf("1. Create employee\n");
		printf("2. Remove employee\n");
		printf("3. Search employee by full name\n");
		printf("4. View all employees\n");
		printf("5. Exit\n");
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
			exit(0);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}
int main(int argc, char* argv[]) {
	initializeLogs();
	employee* employees;
	int employeeSize = initializeEmployees(&employees);
	employee* loggedEmployee = loginPrompt(employeeSize, employees);
	employeePrompts(&employees, &employeeSize);
	return 0;
}