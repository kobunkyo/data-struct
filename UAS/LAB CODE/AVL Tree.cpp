#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	char name[10];
	int value;
	int height;
	struct Node* left;
	struct Node* right;
}*ROOT = NULL;

// Buat sebuah data baru ke dalam sebuah node
struct Node* createNode(char* name, int value)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	
	strcpy(node->name, name);
	node->value = value;
	node->height = 1;
	
	node->left = NULL;
	node->right = NULL;
	return node;
}

// Untuk menentukan height tertinggi dari node anak kiri dan kanan
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// Dapetin height dari node
int height(struct Node* node)
{
	if(!node)
		return 0;
	else
		return node->height;
}

// Untuk hitung Balance Factor dari node
int getBalance(struct Node* node)
{
	if(!node)
		return 0;
	else
		return height(node->left) - height(node->right);
}

struct Node* rightRotate(struct Node* node)
{
	// Define X dan Sub X
	struct Node* x = node->left;
	struct Node* subX = x->right;
	
	// Rearrange posisi node
	x->right = node;
	node->left = subX;
	
	// Update Height
	node->height = 1 + max(height(node->left),height(node->right));
	x->height = 1 + max(height(node->left), height(node->right));
	
	return x;
}

struct Node* leftRotate(struct Node* node)
{
	// Define X dan Sub X
	struct Node* x = node->right;
	struct Node* subX = x->left;
	
	// Rearrange posisi node
	x->left = node;
	node->right = subX;
	
	// Update Height
	node->height = 1 + max(height(node->left),height(node->right));
	x->height = 1 + max(height(node->left), height(node->right));
	
	return x;
}

struct Node* insert(struct Node* node, char* name, int value)
{
	// Belum ada node
	if(!node)
	{
		return createNode(name, value);
	}
	// Value lebih kecil dari node sebelumnya
	else if (value < node->value)
	{
		node->left = insert(node->left, name, value);
	}
	// Value lebih besar dari node sebelumnya
	else if (value > node->value)
	{
		node->right = insert(node->right, name, value);
	}
	else
	{
		return node;
	}
	// Setiap INSERT dan ROTATE harus update HEIGHT dari NODE
	// Height -> Balance Factor -> Case ? -> Rotasi
	node->height = 1 + max(height(node->left), height(node->right));
	int balanceFactor = getBalance(node);
	
	// LL
	if(balanceFactor > 1 && value < node->left->value)
	{
		// Right Rotate
		return rightRotate(node);
	}
	// LR
	else if(balanceFactor > 1 && value > node->left->value)
	{
		// Left Rotate (solve anak)
		node->left = leftRotate(node->left);
		
		// Right Rotate (solve parent)
		return rightRotate(node);
	}
	// RR
	else if(balanceFactor < -1 && value > node->right->value)
	{
		// Left Rotate
		return leftRotate(node);
	}
	// RL
	else if(balanceFactor < -1 && value < node->right->value)
	{
		// Right Rotate
		node->right = rightRotate(node->right);
		
		// Left Rotate
		return leftRotate(node);
	}
	return node;
}

// Function Update
struct Node* update(struct Node* node, int targetValue, char* newName)
{
	// Node Kosong
	if(!node)
	{
		return node;
	}
	
	if(targetValue < node->value)
	{
		node->left = update(node->left, targetValue, newName);
	}
	else if(targetValue > node->value)
	{
		node->right = update(node->right, targetValue, newName);
	}
	else
	{
		strcpy(node->name, newName);
	}
	return node;
}

void preOrder(struct Node* node)
{
	if(node)
	{
		printf("%-7s [%d]\n", node->name, node->value);
		preOrder(node->left);
		preOrder(node->right);		
	}
}

int main()
{
	ROOT = insert(ROOT, "A", 1);
	ROOT = insert(ROOT, "B", 2);
	ROOT = insert(ROOT, "C", 3);
	ROOT = insert(ROOT, "D", 4);
	ROOT = insert(ROOT, "E", 5);
	
	preOrder(ROOT);
	
	update(ROOT, 3, "Hello");
	puts("");
	preOrder(ROOT);
	return 0;
}

// AVL buat searching lebih cepat
// Balance factor yang menentukan AVl harus berotasi atau kagak
// Kasus
/* 	Left left =  right rotate atas (sekali)
	Left right = left right tapi di bagian bawah terus atas
	Right right = left rotate atas (sekali)
	Right left = right left tapi di bagian bawah terus atas
	cnth
		1					Node	   right rotate 	  x
		 \				   /    \	   		=>			/	\
		  2				  x		null        		  null	Node
		   \			/  \		   left rotate		   /   \
		    3		 null  sub x			<=			sub x   null
		
	1 - 2 atas
	2 - 3 bawah
*/
