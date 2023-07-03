#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// AVL Tree

struct Node
{
	int key;
	int height;
	Node *left;
	Node *right;
};

struct Node* ROOT = NULL;

struct Node* CreateNode(int key)
{
	Node *node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int GetHeight(struct Node* node)
{
	if(!node)
		return 0;
	else
		return node->height;
	
}

int GetBalanceFactor(struct Node* node)
{
	if(!node)
		return 0;
	else
		return GetHeight(node->left) - GetHeight(node->right);
}

int GetMaximum(int a, int b)
{
	return (a > b) ? a : b;
}

int CalculateHeight(struct Node* node)
{
	return GetMaximum(GetHeight(node->left), GetHeight(node->right) + 1);
}

struct Node* RightRotate(struct Node* node)
{
	struct Node* pivot = node->left;
	struct Node* cut = pivot->right;
	
	pivot->right = node;
	node->left = cut;
	
	node->height = CalculateHeight(node);
	pivot->height = CalculateHeight(pivot);
	
	return pivot;
}

struct Node* LeftRotate(struct Node* node)
{
	struct Node* pivot = node->right;
	struct Node* cut = pivot->left;
	
	pivot->left = node;
	node->right = cut;
	
	node->height = CalculateHeight(node);
	pivot->height = CalculateHeight(pivot);
	
	return pivot;
}

struct Node* Rebalance(struct Node *node)
{
	int bf = GetBalanceFactor(node);
	
	// Left
	if(bf>1)
	{
		// Left - Right
		if(GetBalanceFactor(node->left)<0)
		{
			// left rotate
			node->left = LeftRotate(node->left);
		}
		// Left - Left
		node = RightRotate(node);
	}
	// Right
	else if(bf<-1)
	{
		// Right - Left
		if(GetBalanceFactor(node->right) > 0)
		{
			// Right rotate
			node->right = RightRotate(node->right);
		}
		// Right - Right
		node = LeftRotate(node);
	}
	
	return node;
}

struct Node* InsertNode(struct Node* curr, int key)
{
	if(!curr)
	{
		struct Node* node = CreateNode(key);
		return node;
	}
	else if(key == curr->key)
	{
		printf("Duplicate key!\n");
	}
	else if(key < curr->key)
	{
		curr->left = InsertNode(curr->left, key);
	}
	else if(key > curr->key)
	{
		curr->right = InsertNode(curr->right, key);
	}
	
	curr->height = CalculateHeight(curr);
	curr = Rebalance(curr);
	return curr;
}

struct Node* GetPredecessor(struct Node* node)
{
	node = node->left;
	while(node->right){
		node = node->right;
	}
	return node;
}

struct Node* DeleteNode(struct Node* curr, int key)
{
	if(!curr)
	{
		printf("Key not found!\n");
	}
	else if(key < curr->key)
	{
		curr->left = DeleteNode(curr->left, key);
	}
	else if(key > curr->key)
	{
		curr->right = DeleteNode(curr->right, key);
	}
	else if(key == curr->key)
	{
		if(!curr->left && !curr->right)
		{
			free(curr);
			return NULL;
		}
		else if(curr->left && !curr->right)
		{
			struct Node* replace = curr->left;
			free(curr);
			return replace;
		}
		else if(curr->right && !curr->left)
		{
			struct Node* replace = curr->right;
			free(curr);
			return replace;
		}
		else if(curr->left && curr->right)
		{
			struct Node* replace = GetPredecessor(curr);
			curr->key = replace->key;
			curr->left = DeleteNode(curr->left, replace->key) ;
		}
	}
	curr->height = CalculateHeight(curr);
	curr = Rebalance(curr);
	
	return curr;
}

void PreOrder(struct Node* node)
{
	if(node)
	{
		printf("%d ", node->key);
		PreOrder(node->left);
		PreOrder(node->right);
	}
}

void InOrder(struct Node* node)
{
	if(node)
	{
		PreOrder(node->left);
		printf("%d ", node->key);
		PreOrder(node->right);
	}
}

void PostOrder(struct Node* node)
{
	if(node)
	{
		PreOrder(node->left);
		PreOrder(node->right);
		printf("%d ", node->key);
	}
}

int main()
{
//	ROOT = InsertNode(ROOT, 1);
//	ROOT = InsertNode(ROOT, 2);
//	ROOT = InsertNode(ROOT, 3);
//	ROOT = InsertNode(ROOT, 4);
//	ROOT = InsertNode(ROOT, 5);
//	ROOT = InsertNode(ROOT, 6);
//	ROOT = InsertNode(ROOT, 7);
//	ROOT = InsertNode(ROOT, 8);
//	ROOT = InsertNode(ROOT, 9);
//	ROOT = InsertNode(ROOT, 10);
	
	ROOT = InsertNode(ROOT, 6);
	ROOT = InsertNode(ROOT, 27);
	ROOT = InsertNode(ROOT, 19);
	ROOT = InsertNode(ROOT, 11);
	ROOT = InsertNode(ROOT, 36);
	ROOT = InsertNode(ROOT, 14);
	ROOT = InsertNode(ROOT, 81);
	ROOT = InsertNode(ROOT, 63);
	ROOT = InsertNode(ROOT, 75);
	
	PreOrder(ROOT); puts("");
	InOrder(ROOT); puts("");
	PostOrder(ROOT); puts("");
	
	return 0;
}
