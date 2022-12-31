#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct employee {
	char username[32];
	char password[32];
	int accessLevel;
	char fullName[32];
}employee;

void saveEmployees(const employee* employees, size_t numEmployees) {
	FILE* fp = fopen("employees.bin", "wb");
	if (fp == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	fwrite(&numEmployees, sizeof(size_t), 1, fp);
	for (size_t i = 0; i < numEmployees; i++) {
		fwrite(&employees[i], sizeof(employee), 1, fp);
	}

	fclose(fp);
}

// Function to add an employee to the array
void addEmployee(employee** employees, size_t* numEmployees, const employee* newEmployee) {
	// Allocate memory for the new employee
	*employees = realloc(*employees, (*numEmployees + 1) * sizeof(employee));
	if (*employees == NULL) {
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	// Add the new employee to the array
	(*employees)[*numEmployees] = *newEmployee;
	(*numEmployees)++;
}

// Function to remove an employee from the array
void removeEmployee(employee** employees, size_t* numEmployees, const char* username) {
	// Find the index of the employee to be removed
	int index = -1;
	for (size_t i = 0; i < *numEmployees; i++) {
		if (strcmp((*employees)[i].username, username) == 0) {
			index = i;
			break;
		}
	}

	// If the employee was not found, return
	if (index == -1) {
		return;
	}

	// Shift the elements after the removed employee down one position
	for (size_t i = index; i < *numEmployees - 1; i++) {
		(*employees)[i] = (*employees)[i + 1];
	}

	// Decrease the number of employees by 1
	(*numEmployees)--;

	// Reallocate memory for the array
	*employees = realloc(*employees, *numEmployees * sizeof(employee));
	if (*employees == NULL) {
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
}

size_t initializeEmployees(employee** employees) {
	FILE* infile = fopen("employees.bin", "rb");
	size_t i;
	size_t array_size;
	employee* d_array;
	// Check if the input file exists
	if (!infile) {
		printf("Initialize new file employees\n");
		// If the input file does not exist, create an empty array of structs
		array_size = 1;
		d_array = malloc(array_size * sizeof(employee));
		d_array[0] = (employee){ .username = "Admin", .password = "Admin", .fullName = "Manager_System", .accessLevel = 3 };
		saveEmployees(d_array, array_size);
	}
	else {
		// If the input file exists, read the data from the file and store it in an array of structs
		printf("Loading existing file\n");
		fread(&array_size, sizeof(size_t), 1, infile);
		d_array = malloc(array_size * sizeof(employee));
		for (i = 0; i < array_size; i++) {
			fread(&d_array[i], sizeof(employee), 1, infile);
		}
		fclose(infile);
	}
	*employees = d_array;
	return array_size;
}

employee* tryLogin(const char* username, const char* password, size_t employees_size, const employee* employees) {
	for (size_t i = 0; i < employees_size; i++) {
		if (strcmp(username, employees[i].username) == 0 && strcmp(password, employees[i].password) == 0) {
			return &employees[i];
		}
	}
	return NULL;
}

employee* login(size_t employees_size, const employee* employees) {
	int tries = 0;
	employee* loggedInEmployee = NULL;
	while (tries < 3 && loggedInEmployee == NULL) {
		// Prompt the user for a username and password
		char username[32];
		char password[32];
		printf("Enter username: ");
		scanf("%s", username);
		printf("Enter password: ");
		scanf("%s", password);

		// Try to login with the provided username and password
		loggedInEmployee = tryLogin(username, password, employees_size, employees);
		if (loggedInEmployee == NULL) {
			printf("Login failed.\n");
		}
		tries++;
	}
	if (loggedInEmployee == NULL) {
		printf("You have exceeded the maximum number of tries.\n");
		exit(0);
	}

	printf("Login successful!\n");
	printf("Access level: %d\n", loggedInEmployee->accessLevel);
	printf("Full name: %s\n", loggedInEmployee->fullName);

	return loggedInEmployee;
}
