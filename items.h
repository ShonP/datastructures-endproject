#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

typedef struct item {
	int id;
	char field1[32];
	char field2[32];
	float value;
	bool boolean;
	time_t date;
} item;

typedef struct nodeItem {
	item data;
	struct nodeItem* left;
	struct nodeItem* right;
} nodeItem;

// Function prototypes
nodeItem* initializeItems();
void addItem(nodeItem** root, item data);
void removeItem(nodeItem** root, int id);
void saveTreeItems(struct nodeItem* root, FILE* fp);
void saveItems(nodeItem* root);
void freeTreeItems(nodeItem* root);
void printTreeItems(nodeItem* root);
nodeItem* searchByIdItem(nodeItem* root, int id);
nodeItem* searchByField1Item(nodeItem* root, const char* field1);
nodeItem* searchByField1Item(nodeItem* root, const char* field1);
nodeItem* searchByField2Item(nodeItem* root, const char* field2);
nodeItem* searchByValueItem(nodeItem* root, float value);
nodeItem* searchByBooleanItem(nodeItem* root, bool boolean);
nodeItem* searchByDateItem(nodeItem* root, time_t date);

nodeItem* initializeItems() {
	nodeItem* root = NULL;

	// Open file for reading
	FILE* fp = fopen("items.bin", "r");
	if (fp == NULL) {
		printf("Initialize new file items\n");

		// File doesn't exist, create it
		fp = fopen("items.bin", "w");
		if (fp == NULL) {
			printf("Error creating file\n");
			return NULL;
		}
	}
	else {
		printf("Loading existing items file\n");
		// Read data from file and addItem it to the tree
		item data;
		while (fscanf(fp, "%d,%31[^,],%31[^,],%f,%d,%ld\n", &data.id, data.field1, data.field2, &data.value, &data.boolean, &data.date) == 6) {
			addItem(&root, data);
		}
	}

	fclose(fp);
	return root;
}


void addItem(nodeItem** root, item data) {
	// If the tree is empty, create a new root nodeItem
	if (*root == NULL) {
		*root = malloc(sizeof(nodeItem));
		(*root)->data = data;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}

	// Recursively addItem the data to the appropriate position in the tree
	if (data.id < (*root)->data.id) {
		addItem(&(*root)->left, data);
	}
	else {
		addItem(&(*root)->right, data);
	}
}

void removeItem(nodeItem** root, int id) {
	if (*root == NULL) {
		return;
	}

	// Recursively search the tree for the nodeItem with the given id
	if (id < (*root)->data.id) {
		removeItem(&(*root)->left, id);
	}
	else if (id > (*root)->data.id) {
		removeItem(&(*root)->right, id);
	}
	else {
		// Node found, remove it
		nodeItem* temp = *root;
		if ((*root)->left == NULL) {
			*root = (*root)->right;
			free(temp);
		}
		else if ((*root)->right == NULL) {
			*root = (*root)->left;
			free(temp);
		}
		else {
			// Node has two children, find the inorder successor
			nodeItem* successor = (*root)->right;
			while (successor->left
				!= NULL) {
				successor = successor->left;
			}  (*root)->data = successor->data;
			removeItem(&(*root)->right, successor->data.id);
		}

	}
}

void saveTreeItems(struct nodeItem* root, FILE* fp) {
	if (root == NULL) {
		return;
	}

	fprintf(fp, "%d,%s,%s,%f,%d,%ld\n", root->data.id, root->data.field1, root->data.field2, root->data.value, root->data.boolean, root->data.date);
	saveTreeItems(root->left, fp);
	saveTreeItems(root->right, fp);
}

void saveItems(struct Node* root) {
	FILE* fp = fopen("items.bin", "w");
	if (fp == NULL) {
		// Error opening file
		return;
	}

	saveTreeItems(root, fp);

	fclose(fp);
}

void freeTreeItems(nodeItem* root) {
	if (root != NULL) {
		freeTreeItems(root->left);
		freeTreeItems(root->right);
		free(root);
	}
}

void printTreeItems(nodeItem* root) {
	if (root != NULL) {
		printTreeItems(root->left);
		printf("%d,%s,%s,%f,%d,%ld\n", root->data.id, root->data.field1, root->data.field2, root->data.value, root->data.boolean, root->data.date);
		printTreeItems(root->right);
	}
}

nodeItem* searchByIdItem(nodeItem* root, int id) {
	if (root == NULL) {
		return NULL;
	}

	if (id < root->data.id) {
		return searchByIdItem(root->left, id);
	}
	else if (id > root->data.id) {
		return searchByIdItem(root->right, id);
	}
	else {
		return root;
	}
}

nodeItem* searchByField1Item(nodeItem* root, const char* field1) {
	if (root == NULL) {
		return NULL;
	}

	if (strcmp(root->data.field1, field1) == 0) {
		return root;
	}
	else if (strcmp(field1, root->data.field1) < 0) {
		return searchByField1Item(root->left, field1);
	}
	else {
		return searchByField1Item(root->right, field1);
	}
}

nodeItem* searchByField2Item(nodeItem* root, const char* field2) {
	if (root == NULL) {
		return NULL;
	}

	if (strcmp(root->data.field2, field2) == 0) {
		return root;
	}
	else if (strcmp(field2, root->data.field2) < 0) {
		return searchByField2Item(root->left, field2);
	}
	else {
		return searchByField2Item(root->right, field2);
	}
}

nodeItem* searchByValueItem(nodeItem* root, float value) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.value == value) {
		return root;
	}
	else if (value < root->data.value) {
		return searchByValueItem(root->left, value);
	}
	else {
		return searchByValueItem(root->right, value);
	}
}

nodeItem* searchByBooleanItem(nodeItem* root, bool boolean) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.boolean == boolean) {
		return root;
	}
	else if (boolean < root->data.boolean) {
		return searchByBooleanItem(root->left, boolean);
	}
	else {
		return searchByBooleanItem(root->right, boolean);
	}
}

nodeItem* searchByDateItem(nodeItem* root, time_t date) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.date == date) {
		return root;
	}
	else if (date < root->data.date) {
		return searchByDateItem(root->left, date);
	}
	else {
		return searchByDateItem(root->right, date);
	}
}
