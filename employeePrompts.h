#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "logs.h"

#ifndef _EMPLOYEES_PROMPTS_H_
#define _EMPLOYEES_PROMPTS_H_

#pragma warning(disable:4996)

void createEmployeePrompt(employee** employees, int* numEmployees) {
	system("cls");
	employee* newEmployee = malloc(sizeof(employee));
	printf("Enter username: ");
	scanf("%s", newEmployee->username);
	printf("Enter password: ");
	scanf("%s", newEmployee->password);
	printf("Enter full name: ");
	scanf("%s", newEmployee->fullName);
	printf("Enter access level: ");
	scanf("%d", &newEmployee->accessLevel);
	addEmployee(employees, numEmployees, newEmployee);
	char log[100];
	snprintf(log, sizeof(log), "%s created employee successfully", newEmployee->username);
	logMessage(&log);
	saveEmployees(*employees, *numEmployees);
}

// remove employee prompt
void removeEmployeePrompt(employee** employees, int* numEmployees) {
	system("cls");
	char username[32];
	printf("Enter username: ");
	char log[100];
	scanf("%s", username);
	int isSuccessRemove = removeEmployee(employees, numEmployees, username);
	if (isSuccessRemove == 1) {
		snprintf(log, sizeof(log), "%s removed employee successfully", username);
		logMessage(&log);
		saveEmployees(*employees, *numEmployees);
	}
	else {
		printf("Employee not found\n");
	}

}

// search employee by full name prompt
void searchEmployeeByFullNamePrompt(employee* employees, int numEmployees) {
	system("cls");
	char fullName[32];
	printf("Enter full name: ");
	scanf("%s", fullName);
	employee* foundEmployee = searchEmployeeByFullName(fullName, numEmployees, employees);
	if (foundEmployee == NULL) {
		printf("Employee not found\n");
	}
	else {
		printf("Employee found\n");
		printf("Username: %s\n", foundEmployee->username);
		printf("Password: %s\n", foundEmployee->password);
		printf("Full name: %s\n", foundEmployee->fullName);
		printf("Access level: %d\n", foundEmployee->accessLevel);
	}
}

//searchEmployeeByUsernamePrompt
void searchEmployeeByUsernamePrompt(employee* employees, int numEmployees) {
	system("cls");
	char username[32];
	printf("Enter username: ");
	scanf("%s", username);
	employee* foundEmployee = searchEmployeeByUsername(username, numEmployees, employees);
	if (foundEmployee == NULL) {
		printf("Employee not found\n");
	}
	else {
		printf("Employee found\n");
		printf("Username: %s\n", foundEmployee->username);
		printf("Password: %s\n", foundEmployee->password);
		printf("Full name: %s\n", foundEmployee->fullName);
		printf("Access level: %d\n", foundEmployee->accessLevel);
	}
}

// function to view all employees
void viewAllEmployeesPrompt(const employee* employees, int employeesSize) {
	system("cls");
	printf("All employees:\n");
	for (int i = 0; i < employeesSize; i++) {
		printf("Username: %s\n", employees[i].username);
		printf("Fullname: %s\n", employees[i].fullName);
		printf("Access level: %d\n", employees[i].accessLevel);
	}
}


// create all view prompts prompt
void level1EmployeePrompts(const employee** employees, int* employeesSize) {
	system("cls");
	int choice;
	do {
		printf("-----------------\n\n\n\n");
		printf("1. View all employees\n");
		printf("2. Search employee by full name\n");
		printf("3. Search employee by username\n");
		printf("0. Back\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			break;
		case 1:
			viewAllEmployeesPrompt(*employees, *employeesSize);
			break;
		case 2:
			searchEmployeeByFullNamePrompt(*employees, *employeesSize);
			break;
		case 3:
			searchEmployeeByUsernamePrompt(*employees, *employeesSize);
			break;
		case 4:
			return;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);

}
// create all view prompts prompt

void level2EmployeePrompts(const employee** employees, int* employeesSize) {
	system("cls");
	int choice;
	do {
		printf("-----------------\n\n\n\n");
		printf("1. View all employees\n");
		printf("2. Search employee by full name\n");
		printf("3. Search employee by username\n");
		printf("4. Create employee\n");
		printf("0. Back\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			break;
		case 1:
			viewAllEmployeesPrompt(*employees, *employeesSize);
			break;
		case 2:
			searchEmployeeByFullNamePrompt(*employees, *employeesSize);
			break;
		case 3:
			searchEmployeeByUsernamePrompt(*employees, *employeesSize);
			break;
		case 4:
			createEmployeePrompt(employees, employeesSize);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);
}

void level3EmployeePrompts(const employee** employees, int* employeesSize) {
	system("cls");
	int choice;
	do {
		printf("-----------------\n\n\n\n");
		printf("1. View all employees\n");
		printf("2. Search employee by full name\n");
		printf("3. Search employee by username\n");
		printf("4. Create employee\n");
		printf("5. Remove employee\n");
		printf("0. Back\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			break;
		case 1:
			viewAllEmployeesPrompt(*employees, *employeesSize);
			break;
		case 2:
			searchEmployeeByFullNamePrompt(*employees, *employeesSize);
			break;
		case 3:
			searchEmployeeByUsernamePrompt(*employees, *employeesSize);
			break;
		case 4:
			createEmployeePrompt(employees, employeesSize);
			break;
		case 5:
			removeEmployeePrompt(employees, employeesSize);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);
}


#endif