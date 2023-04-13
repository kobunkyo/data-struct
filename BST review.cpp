#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	int value;
	struct Node *left, *right;
}*root = NULL;

struct Node* create(int value){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->value = value;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// Insert
// 1. Kalo root kosong
// 2. Kalo value yang dimasukin lebih kecil drpd root
// 3. Kalo value yang dimasukin lebih besar drpd root

struct Node* insert(struct Node* root, int value){
	struct Node* newNode = create(value);
	// Kalo root kosong
	if(root == NULL){
		return newNode;
	}
	// Kalo value yang dimasukin lebih kecil
	else if(value < root->value){
		root->left = insert(root->left, value);
	}
	// Kalo value yang dimasukin lebih besar
	else if(value > root->value){
		root->right = insert(root->right, value);
	}
	return root;
}

// Search
// 1. Kalo root kosong
// 2. Kalo datanya ketemu di root
// 3. Kalo data dicari lbh kecil dari root
// 4. Kalo data dicari lbh besar dari root

void search(struct Node* root, int value){
	// Kalo root kosong
	if(root == NULL){
		printf("%d is not exist!\n", value);
		return;
	}
	// Kalo data ketemu
	if(root->value == value){
		printf("%d is available!\n", value);
		return;
	}
	// Kalo data dicari lbh kecil dari root
	else if(value < root->value){
		search(root->left, value);
	}
	// Kalo data dicari lbh besar dari root
	else if(value > root->value){
		search(root->right, value);
	}
}

// Traversal
// -> Cara kita untuk melintasi tree
// -> Prefix, Infix, Postfix

// Prefix (atas ke bawah tapi cari kiri bawah dulu kalau habis bisa ke kanan)
// 1. Print
// 2. Left
// 3. Right

// Infix (bawah ke atas dari kiri sampe ketemu cabang baru cari kanan)
// 1. Left
// 2. Print
// 3. Right

// Postfix (kiri ke kanan tapi kalo ketemu cabang cek kanannya dulu baru ke atas)
// 1. Left
// 2. Right
// 3. Print

void prefix(struct Node* curr){
	if(curr != NULL){
		printf("%d -> ", curr->value);
		prefix(curr->left);
		prefix(curr->right);
	}
}

void infix(struct Node* curr){
	if(curr != NULL){
		infix(curr->left);
		printf("%d -> ", curr->value);
		infix(curr->right);
	}
}

void postfix(struct Node* curr){
	if(curr != NULL){
		postfix(curr->left);
		postfix(curr->right);
		printf("%d -> ", curr->value);
	}
}

// Pop / Remove
// 1. Kalo root kosong
// 2. Kalo data yang mau dihapus lebih kecil daripada root
// 3. Kalo data yang mau dihapus lebih besar daripada root
// 4. Kalo data ketemu
//		-> Data paling bawah
//		-> Data punya satu anak dikiri
//		-> Data punya satu anak dikanan
//		-> Data punya dua anak

struct Node* pop(struct Node* root, int value){
	// Kalo data kosong
	if(!root){
		printf("%d is not exist!\n", value);
		return NULL;
	}
	// Kalo data lebih kecil drpd root
	else if(value < root->value){
		root->left = pop(root->left, value);
	}
	// Kalo data lebih besar drpd root
	else if(value > root->value){
		root->right = pop(root->right, value);
	}
	// Kalo data ketemu
	else if(value == root->value){
		// Kalo data paling bawah
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		// Kalo data punya satu anak di kiri
		else if(root->left != NULL && root->right == NULL){
			struct Node* temp = root->left;
			// Duplikat data
			*root = *temp;
			free(temp);
			temp = NULL;
		}
		// Kalo data punya satu anak di kanan
		else if(root->left == NULL && root->right != NULL){
			struct Node* temp = root->right;
			// Duplikat data
			*root = *temp;
			free(temp);
			temp = NULL;
		}
		// Kalo data punya dua anak
		else if(root->left != NULL && root->right != NULL){
			struct Node* temp = root->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			root->value = temp->value;
			root ->left = pop(root->left, temp->value);
		}
	}
	return root;
}

int main(){
	root = insert(root, 5);
	root = insert(root, 2);
	root = insert(root, 4);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 9);
	root = insert(root, 6);
	root = insert(root, 7);
	root = insert(root, 8);
	root = pop(root, 5);
//	search(root, 7);
	printf("PREFIX: ");
	prefix(root);
	getchar();
	
	printf("POSTFIX: ");
	postfix(root);
	getchar();
	
	printf("INFIX: ");
	infix(root);
	getchar();
	
	pop(root, 2);
	infix(root);
	return 0;
}
