#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product{
	int price; int stock; char name[100];
};

struct Node{
	int key;
	struct Product data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}*ROOT = NULL;

struct Node* create(int key){
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return node;
}

struct Node* insert(struct Node* root, int key){
	if(!root){
		return create(key);
	}else if(key == root->key){
		printf("Duplicate data!\n");
	}else if(key<root->key){
		struct Node* leftchild = insert(root->left, key);
		root->left = leftchild;
		leftchild->parent = root;
	}else if(key>root->key){
		struct Node* rightchild = insert(root->right, key);
		root->right = rightchild;
		rightchild->parent = root;
	}
	return root;
}

void pre_order(struct Node* root){
	if(root){
		printf("%d -> ", root->key);
		pre_order(root->left);
		pre_order(root->right);
	}
}

void in_order(struct Node* root){
	if(root){
		in_order(root->left);
		printf("%d -> ", root->key);
		in_order(root->right);
	}
}

void post_order(struct Node* root){
	if(root){
		post_order(root->left);
		post_order(root->right);
		printf("%d -> ", root->key);
	}
}

struct Node* getPredecessor(struct Node* root){
	root = root->left;
	while( root->right ){
		root = root->right;
	}
	return root;
}

struct Node* getSucessor(struct Node* root){
	root = root->right;
	while( root->left ){
		root = root->left;
	}
	return root;
}

struct Node* deleted(struct Node* root, int key){
	if( !ROOT ){
		printf("There is no data!\n");
	}else if( !root ){
		printf("Data not found!\n");
	}else if( key < root->key ){
		root->left = deleted(root->left, key);
	}else if( key > root->key ){
		root->right = deleted(root->right, key);
	}else if( key == root->key){
		if(!root->right && !root->left){
			free(root);
			root = NULL;
		}else if(root->right && !root->left){
			struct Node* replace = root->right;
			replace->parent = root->parent;
			free(root);
			root = replace;
		}else if(!root->right && root->left){
			struct Node* replace = root->left;
			replace->parent = root->parent;
			free(root);
			root = replace;
		}else if(root->right && root->left){
			struct Node* replace = getPredecessor(root);
			root->key = replace->key;
			root->left = deleted(root->left, replace->key);
		}
	}
	return root;
}

struct Node* deleteAll(struct Node* root){
	if(root){
		deleteAll(root->left);
		deleteAll(root->right);
		free(root);
		return NULL;
	}
}

int main(){
	ROOT = insert(ROOT, 54);
	ROOT = insert(ROOT, 30);
	ROOT = insert(ROOT, 78);
	ROOT = insert(ROOT, 21);
	ROOT = insert(ROOT, 15);
	ROOT = insert(ROOT, 36);
	ROOT = insert(ROOT, 80);
	
	ROOT = deleted(ROOT, 15);
	ROOT = deleted(ROOT, 54);
	ROOT = deleted(ROOT, 78);
	ROOT = deleteAll(ROOT);
	
	printf("In Order: ");
	in_order(ROOT);
	printf("\n");
	printf("Post Order: ");
	post_order(ROOT);
	printf("\n");
	printf("Pre Order: ");
	pre_order(ROOT);
	
	return 0;
}
