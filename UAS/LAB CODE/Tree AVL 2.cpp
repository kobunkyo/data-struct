#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	char name[50];
	int value;
	struct Node* left;
	struct Node* right;
	int height;
};

int getMax(int a, int b)
{
	return (a>b) ? a : b;
}

int getHeight(struct Node* node)
{
	if(node == NULL)
		return 0;
	else
		return node->height;
}

int getBalance(struct Node* node)
{
	if(!node)
		return 0;
	else
		return getHeight(node->left) - getHeight(node->right);
}

struct Node* create(char* name, int value)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	strcpy(newNode->name, name);
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	return newNode;
}

struct Node* rightRotate(struct Node* node)
{
	// Tentuin node yang mau di ubah
	struct Node* x = node->left;
	struct Node* subX = x->right;
	// Pindah posisi
	x->right = node;
	node->left = subX;
	// Update height
	node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
	x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));
	
	return x;
}

struct Node* leftRotate(struct Node* node)
{
	// Tentuin node yang mau di ubah
	struct Node* x = node->right;
	struct Node* subX = x->left;
	// Pindah posisi
	x->left = node;
	node->right = subX;
	// Update height
	node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
	x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));
	
	return x;
}

struct Node* insert(struct Node* node, char* name, int value)
{
	if(!node)
	{
		return create(name, value);
	}	
	else if(value < node->value)
	{
		node->left = insert(node->left, name, value);
	}	
	else if(value > node->value)
	{
		node->right = insert(node->right, name, value);
	}
	else
	{
		return node;
	}
	
	node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
	int balanceFactor = getBalance(node);
	
	// L-L
	if(balanceFactor > 1 && value < node->left->value)
	{
		// RIGHT ROTATE atas
		return rightRotate(node);
	}
	// L-R
	else if(balanceFactor > 1 && value > node->left->value)
	{
		// LEFT ROTATE bawah
		node->left = leftRotate(node->left);
		// RIGHT ROTATE atas
		return rightRotate(node);
	}
	// R-R
	else if(balanceFactor < -1 && value > node->right->value)
	{
		// LEFT ROTATE atas
		return leftRotate(node);
	}
	// R-L
	else if(balanceFactor < -1 && value < node->right->value)
	{
		// RIGHT ROTATE bawah
		node->right = rightRotate(node->right);
		// LEFT ROTATE atas
		return leftRotate(node);
	}
	
	return node;
		
}

// Search
struct Node* search(struct Node* node, int target)
{
	if(!node)
	{
		printf("Node %d is not exist!\n", target);
		return NULL;
	}
	else if(target < node->value)
	{
		node->left = search(node->left, target);
	}
	else if(target > node->value)
	{
		node->right = search(node->right, target);
	}
	else
	{
		printf("Node %d is exist with value %s\n", node->value, node->name);
		return node;
	}
}

struct Node* getPredecessor(struct Node* node)
{
	struct Node* curr = node->left;
	while(curr->right)
	{
		curr = curr->right;
	}
	return curr;
}

// Delete
struct Node* toDelete(struct Node* node, int target)
{
	if(!node)
	{
		printf("Node %d is not exist!\n", target);
	}
	else if(target < node->value)
	{
		node->left = toDelete(node->left, target);
	}
	else if(target > node->value)
	{
		node->right = toDelete(node->right, target);
	}
	else
	{
		// Node gak punya anak / punya 1 anak
		if(node->left == NULL || node->right == NULL)
		{
			struct Node* temp = NULL;
			if(node->left){
				temp = node->left;
			}
			else if (node->right){
				temp = node->right;
			}
			
			// Hapus
			free(node);
			// Ganti node
			node = temp;
			
			if(!node)
			{
				return NULL;
			}
			
		}
		// Node punya dua anak
		else
		{
			struct Node* predecessor = getPredecessor(node);
			node->value = predecessor->value;
			strcpy(node->name, predecessor->name);
			
			// Hapus predecessor
			node->left = toDelete(node->left, predecessor->value);
		}
		node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
		int balanceFactor = getBalance(node);
		
		// L-L
		if(balanceFactor > 1 && getBalance(node->left) >= 0)
		{
			// RIGHT ROTATE atas
			return rightRotate(node);
		}
		// L-R
		else if(balanceFactor > 1 && getBalance(node->right) < 0 )
		{
			// LEFT ROTATE bawah
			node->left = leftRotate(node->left);
			// RIGHT ROTATE atas
			return rightRotate(node);
		}
		// R-R
		else if(balanceFactor < -1 && getBalance(node->right) < 0)
		{
			// LEFT ROTATE atas
			return leftRotate(node);
		}
		// R-L
		else if(balanceFactor < -1 && getBalance(node->left) >= 0)
		{
			// RIGHT ROTATE bawah
			node->right = rightRotate(node->right);
			// LEFT ROTATE atas
			return leftRotate(node);
		}
		
		return node;
	}
}

void preOrder(struct Node* node)
{
	if(node)
	{
		printf("%-3s [%d]\n", node->name, node->value);
		preOrder(node->left);
		preOrder(node->right);
	}
}

int main()
{
	struct Node* ROOT = NULL;
	ROOT = insert(ROOT, "A", 1);
	ROOT = insert(ROOT, "B", 2);
	ROOT = insert(ROOT, "C", 3);
	ROOT = insert(ROOT, "D", 4);
	ROOT = insert(ROOT, "E", 5);
	
	preOrder(ROOT);
	
	search(ROOT, 4);
	search(ROOT, 12);
	
	ROOT = toDelete(ROOT, 4);
	search(ROOT, 4);
	
	preOrder(ROOT);
	
	return 0;
}
