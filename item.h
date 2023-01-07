#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _ITEMS_H_
#define _ITEMS_H_

#pragma warning(disable:4996)

typedef struct item {
	int id;
	char phoneName[32];
	char brand[32];
	float price;
	bool isNew;
	time_t date;
} item;

typedef struct nodeItem {
	item data;
	struct nodeItem* left;
	struct nodeItem* right;
} nodeItem;

typedef struct listItem {
	item data;
	struct listItem* next;
} listItem;

// Function prototypes
nodeItem* initializeItems();
void addItem(nodeItem** root, item* data);
void removeItem(nodeItem** root, int id);
void saveTreeItems(struct nodeItem* root, FILE* fp);
void saveItems(nodeItem* root);
void freeTreeItems(nodeItem* root);
void printTreeItems(nodeItem* root);
listItem* searchByBrandItem(nodeItem* root, char* searchKey);
nodeItem* searchByIdItem(nodeItem* root, int id);
nodeItem* searchByPhoneNameItem(nodeItem* root, const char* phoneName);

// create printItem function
void printItem(item* data) {
	printf("Item Id: %d\n", data->id);
	printf("Phone name: %s\n", data->phoneName);
	printf("Brand: %s\n", data->brand);
	printf("Price: %.2f\n", data->price);
	printf("Is new: %d\n", data->isNew);
	printf("In store since: %s", ctime(&data->date));
}


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
		while (1) {
			item data;
			int result = fread(&data, sizeof(item), 1, fp);
			if (result == 0) {
				break;
			}
			addItem(&root, &data);
		}
	}

	fclose(fp);
	return root;
}


void addItem(nodeItem** root, item* data) {
	if (*root == NULL) {
		*root = (nodeItem*)malloc(sizeof(nodeItem));
		(*root)->data = *data;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else {
		if (data->id < (*root)->data.id) {
			addItem(&(*root)->left, data);
		}
		else if (data->id > (*root)->data.id) {
			addItem(&(*root)->right, data);
		}
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
	fwrite(&root->data, sizeof(item), 1, fp);

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
		printf("%d,%s,%s,%f,%d,%s\n", root->data.id, root->data.phoneName, root->data.brand, root->data.price, root->data.isNew, ctime(&root->data.date));
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

nodeItem* searchByPhoneNameItem(nodeItem* root, const char* phoneName) {
	if (root == NULL) {
		return NULL;
	}

	if (strcmp(root->data.phoneName, phoneName) == 0) {
		return root;
	}
	else if (strcmp(phoneName, root->data.phoneName) < 0) {
		return searchByPhoneNameItem(root->left, phoneName);
	}
	else {
		return searchByPhoneNameItem(root->right, phoneName);
	}
}

listItem* searchByBrandItem(nodeItem* root, char* searchKey) {
	if (root == NULL) {
		return NULL;
	}

	listItem* result = searchByBrandItem(root->left, searchKey);

	if (strcmp(root->data.brand, searchKey) == 0) {
		listItem* newResult = (listItem*)malloc(sizeof(listItem));
		newResult->data = root->data;
		newResult->next = result;
		result = newResult;
	}

	listItem* rightResult = searchByBrandItem(root->right, searchKey);
	if (rightResult != NULL) {
		listItem* current = result;
		while (current != NULL && current->next != NULL) {
			current = current->next;
		}
		if (current == NULL) {
			result = rightResult;
		}
		else {
			current->next = rightResult;
		}
	}

	return result;
}

listItem* searchByIsNewItem(nodeItem* root, bool isNew) {
	if (root == NULL) {
		return NULL;
	}

	listItem* result = searchByIsNewItem(root->left, isNew);

	if (root->data.isNew == isNew) {
		listItem* newResult = (listItem*)malloc(sizeof(listItem));
		newResult->data = root->data;
		newResult->next = result;
		result = newResult;
	}

	listItem* rightResult = searchByIsNewItem(root->right, isNew);
	if (rightResult != NULL) {
		listItem* current = result;
		while (current != NULL && current->next != NULL) {
			current = current->next;
		}
		if (current == NULL) {
			result = rightResult;
		}
		else {
			current->next = rightResult;
		}
	}

	return result;
}

int updateItem(nodeItem* root, int id, item* data) {
	nodeItem* node = searchByIdItem(root, id);
	if (node != NULL) {
		node->data = *data;
		return 1;
	}
	return 0;
}
#endif