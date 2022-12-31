#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include "items.h"

#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	// Open the input file
	employee* employees;
	size_t employees_size = initializeEmployees(&employees);
	employee dummyEmployee = { .accessLevel = 2,.fullName = "Shon",.password = "123",.username = "Shon" };
	printf("%s", employees[0].fullName);
	nodeItem* root = initialize();


	// Initialize tree from file
	//print_tree(root);


	// Save changes to file
	//save(root);

	// Free tree memory
	free_tree(root);


	//user* loggedInUser = login(users_size, users);


	// Try to login with the provided username and password

	free(employees);
	return 0;
}