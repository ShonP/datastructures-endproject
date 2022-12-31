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
nodeItem* initialize();
void add(nodeItem** root, item data);
void remove_item(nodeItem** root, int id);
void saveTree(struct nodeItem* root, FILE* fp);
void save(nodeItem* root);
void free_tree(nodeItem* root);
void print_tree(nodeItem* root);
nodeItem* search_id(nodeItem* root, int id);
nodeItem* search_field1(nodeItem* root, const char* field1);
nodeItem* search_field1(nodeItem* root, const char* field1);
nodeItem* search_field2(nodeItem* root, const char* field2);
nodeItem* search_value(nodeItem* root, float value);
nodeItem* search_boolean(nodeItem* root, bool boolean);
nodeItem* search_date(nodeItem* root, time_t date);

nodeItem* initialize() {
	nodeItem* root = NULL;

	// Open file for reading
	FILE* fp = fopen("items.bin", "r");
	if (fp == NULL) {
		printf("File does not exist, creating new file\n");

		// File doesn't exist, create it
		fp = fopen("items.bin", "w");
		if (fp == NULL) {
			printf("Error creating file\n");
			return NULL;
		}
	}
	else {
		printf("File existing using same file\n");
		// Read data from file and add it to the tree
		item data;
		while (fscanf(fp, "%d,%31[^,],%31[^,],%f,%d,%ld\n", &data.id, data.field1, data.field2, &data.value, &data.boolean, &data.date) == 6) {
			add(&root, data);
		}
	}

	fclose(fp);
	return root;
}


void add(nodeItem** root, item data) {
	// If the tree is empty, create a new root nodeItem
	if (*root == NULL) {
		*root = malloc(sizeof(nodeItem));
		(*root)->data = data;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}

	// Recursively add the data to the appropriate position in the tree
	if (data.id < (*root)->data.id) {
		add(&(*root)->left, data);
	}
	else {
		add(&(*root)->right, data);
	}
}

void remove_item(nodeItem** root, int id) {
	if (*root == NULL) {
		return;
	}

	// Recursively search the tree for the nodeItem with the given id
	if (id < (*root)->data.id) {
		remove_item(&(*root)->left, id);
	}
	else if (id > (*root)->data.id) {
		remove_item(&(*root)->right, id);
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
			remove_item(&(*root)->right, successor->data.id);
		}

	}
}

void saveTree(struct nodeItem* root, FILE* fp) {
	if (root == NULL) {
		return;
	}

	fprintf(fp, "%d,%s,%s,%f,%d,%ld\n", root->data.id, root->data.field1, root->data.field2, root->data.value, root->data.boolean, root->data.date);
	saveTree(root->left, fp);
	saveTree(root->right, fp);
}

void save(struct Node* root) {
	FILE* fp = fopen("items.bin", "w");
	if (fp == NULL) {
		// Error opening file
		return;
	}

	saveTree(root, fp);

	fclose(fp);
}

void free_tree(nodeItem* root) {
	if (root != NULL) {
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

void print_tree(nodeItem* root) {
	if (root == NULL) {
		return;
	}

	print_tree(root->left);
	printf("id: %d, field1: %s, field2: %s, value: %f, boolean: %d, date: %ld\n", root->data.id, root->data.field1, root->data.field2, root->data.value, root->data.boolean, root->data.date);
	print_tree(root->right);
}

nodeItem* search_id(nodeItem* root, int id) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.id == id) {
		return root;
	}
	else if (id < root->data.id) {
		return search_id(root->left, id);
	}
	else {
		return search_id(root->right, id);
	}
}

nodeItem* search_field1(nodeItem* root, const char* field1) {
	if (root == NULL) {
		return NULL;
	}

	if (strcmp(root->data.field1, field1) == 0) {
		return root;
	}
	else if (strcmp(field1, root->data.field1) < 0) {
		return search_field1(root->left, field1);
	}
	else {
		return search_field1(root->right, field1);
	}
}

nodeItem* search_field2(nodeItem* root, const char* field2) {
	if (root == NULL) {
		return NULL;
	}

	if (strcmp(root->data.field2, field2) == 0) {
		return root;
	}
	else if (strcmp(field2, root->data.field2) < 0) {
		return search_field2(root->left, field2);
	}
	else {
		return search_field2(root->right, field2);
	}
}

nodeItem* search_value(nodeItem* root, float value) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.value == value) {
		return root;
	}
	else if (value < root->data.value) {
		return search_value(root->left, value);
	}
	else {
		return search_value(root->right, value);
	}
}

nodeItem* search_boolean(nodeItem* root, bool boolean) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.boolean == boolean) {
		return root;
	}
	else if (boolean < root->data.boolean) {
		return search_boolean(root->left, boolean);
	}
	else {
		return search_boolean(root->right, boolean);
	}
}

nodeItem* search_date(nodeItem* root, time_t date) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data.date == date) {
		return root;
	}
	else if (date < root->data.date) {
		return search_date(root->left, date);
	}
	else {
		return search_date(root->right, date);
	}
}
