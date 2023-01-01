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

// Function prototypes
nodeItem* initializeItems();
void addItem(nodeItem** root, item data);
void removeItem(nodeItem** root, int id);
void saveTreeItems(struct nodeItem* root, FILE* fp);
void saveItems(nodeItem* root);
void freeTreeItems(nodeItem* root);
void printTreeItems(nodeItem* root);
nodeItem* searchByIdItem(nodeItem* root, int id);
nodeItem* searchByPhoneNameItem(nodeItem* root, const char* phoneName);
nodeItem* searchByBrandItem(nodeItem* root, const char* brand);
nodeItem* searchByValueItem(nodeItem* root, float price);
nodeItem* searchByIsNewItem(nodeItem* root, bool isNew);
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
		while (fscanf(fp, "%d,%31[^,],%31[^,],%f,%d,%ld\n", &data.id, data.phoneName, data.brand, &data.price, &data.isNew, &data.date) == 6) {
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

	fprintf(fp, "%d,%s,%s,%f,%d,%ld\n", root->data.id, root->data.phoneName, root->data.brand, root->data.price, root->data.isNew, root->data.date);
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
		printf("%d,%s,%s,%f,%d\n", root->data.id, root->data.phoneName, root->data.brand, root->data.price, root->data.isNew);
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

nodeItem* searchByBrandItem(nodeItem* root, const char* brand) {
	if (root == NULL) {
		return NULL;
	}

	if (strcmp(root->data.brand, brand) == 0) {
		return root;
	}
	else if (strcmp(brand, root->data.brand) < 0) {
		return searchByBrandItem(root->left, brand);
	}
	else {
		return searchByBrandItem(root->right, brand);
	}
}

nodeItem* searchByPriceItem(nodeItem* root, float price) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.price == price) {
		return root;
	}
	else if (price < root->data.price) {
		return searchByPriceItem(root->left, price);
	}
	else {
		return searchByPriceItem(root->right, price);
	}
}

nodeItem* searchByIsNewItem(nodeItem* root, bool isNew) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.isNew == isNew) {
		return root;
	}
	else if (isNew < root->data.isNew) {
		return searchByIsNewItem(root->left, isNew);
	}
	else {
		return searchByIsNewItem(root->right, isNew);
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

#endif