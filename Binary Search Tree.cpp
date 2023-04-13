#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Aturan di BST
// Root ini nilainya > dari child kiri dan < dari child kanan
// child kiri < root < child kanan
//		10
//     /  \
//	  9   11

/*
	Objective
	 - Insert
	 - Update
	 - Search
*/

struct Student{
	float ipk;
	char name[20];
	struct Student* left;
	struct Student* right;
}*root = NULL;

struct Student* createRoot(char* name, float ipk){
	struct Student* newData = (struct Student*)malloc(sizeof(struct Student));
	strcpy(newData->name, name);
	newData->ipk = ipk;
	newData->left = NULL;
	newData->right = NULL;
	return newData;
}

struct Student* insert(struct Student* root, struct Student* newData){
	if(root == NULL){
//		root = newData;
		return newData;
	}else if(newData->ipk > root->ipk){
		// Rekrusif ke kanan
		root->right = insert(root->right, newData);
	}else if(newData->ipk < root->ipk){
		// Rekrusif ke kiri
		root->left = insert(root->left, newData);
	}
	return root;
}

// InOrder, PreOrder, PostOrder -> Tree Traversal
void inOrder(struct Student* root){
	if(root!=NULL){
		inOrder(root->left);
		printf("%-20s (%.2f)\n", root->name, root->ipk);
		inOrder(root->right);
	}
}

void preOrder(struct Student* root){
	if(root!=NULL){
		printf("%-20s (%.2f)\n", root->name, root->ipk);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void postOrder(struct Student* root){
	if(root!=NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("%-20s (%.2f)\n", root->name, root->ipk);
	}
}

// Update (value yang key)
// Delete -> Insert lagi

// Update (value yang bukan key)
// Harus di search dulu
struct Student* search(struct Student* root, float ipk){
	if(root == NULL || root->ipk == ipk){
		return root;
	}else if(ipk < root->ipk){
		return search(root->left, ipk);
	}else if(ipk > root->ipk){
		return search(root->right, ipk);
	}
}

void update(float ipk, char* newName){
	Student* result = search(root, ipk);
	if(result == NULL){
		printf("Data with the wanted IPK is not found!\n");
		return;
	}
	strcpy(result->name, newName);
	printf("Updated Successful!\n");
	return;
}

int main(){
	root = insert(root, createRoot("Rico", 3.99));
	root = insert(root, createRoot("Christoper", 3.71));
	root = insert(root, createRoot("Sandyka", 3.29));
	root = insert(root, createRoot("Holyvia", 3.67));
	root = insert(root, createRoot("Hanson", 1.31));
	root = insert(root, createRoot("Eliora", 4));
	inOrder(root);
	printf("\n");
	update(3.71, "Jojo");
	inOrder(root);
	return 0;
}
