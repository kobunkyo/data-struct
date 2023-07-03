#include <stdio.h>
#include <stdlib.h>

struct Node{
	int key;
	int height;
	Node *left;
	Node *right;
};

Node *ROOT = NULL;

Node* create_node(int key){
	Node *node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int get_height(Node *node){
	if( !node )
		return 0;
	else
		return node->height;
}

int get_balance_factor(Node *node){
	if( !node )
		return 0;
	else
		return get_height(node->left) - get_height(node->right);
}

int get_maximum(int a, int b){
	return (a > b) ? a : b; //Ternary
}

int calculate_height(Node *node){
	return get_maximum(get_height(node->left), get_height(node->right)) + 1;
}

Node* right_rotate(Node *node){
	Node *pivot = node->left;
	Node *cut = pivot->right;
	
	pivot->right = node;
	node->left = cut;
	
	node->height = calculate_height(node);
	pivot->height = calculate_height(pivot);
	
	return pivot;	
}

Node* left_rotate(Node *node){
	Node *pivot = node->right;
	Node *cut = pivot->left;
	
	pivot->left = node;
	node->right = cut;
	
	node->height = calculate_height(node);
	pivot->height = calculate_height(pivot);
	
	return pivot;
}

Node* rebalance(Node *node){
	int bf = get_balance_factor(node);
	//L
	if( bf > 1 ){
		//R
		if( get_balance_factor(node->left) < 0 ){
			node->left = left_rotate(node->left);
		}
		node = right_rotate(node);
	}
	//R
	else if( bf < -1 ){
		if( get_balance_factor(node->right) > 0 ){
			node->right = right_rotate(node->right);
		}
		node = left_rotate(node);
	}	
	return node;
}

Node* insert_node(Node* curr, int key){
	if( !curr ){
		Node *node = create_node(key);
		return node;
	}
	else if( key == curr->key ){
		printf("Duplicate key!!\n");
	}
	else if( key < curr->key ){
		curr->left = insert_node(curr->left, key);
	}
	else if( key > curr->key ){
		curr->right = insert_node(curr->right, key);
	}
	
	curr->height = calculate_height(curr);
	curr = rebalance(curr);
	return curr;	
}

Node* get_predecessor(Node *node){
	node = node->left;
	while( node->right ){
		node = node->right;
	}
	return node;
}

Node* delete_node(Node *curr, int key){
	if( !curr ){
		printf("Key not found!\n");
	}
	else if( key < curr->key ){
		curr->left = delete_node(curr->left, key);
	}
	else if( key > curr->key ){
		curr->right = delete_node(curr->right, key);
	}
	else if( key == curr->key ){
		if( !curr->left && !curr->right ){
			free(curr);
			return NULL;
		}
		else if( curr->left && !curr->right ){
			Node *replace = curr->left;
			free(curr);
			return replace;
		}
		else if( curr->right && !curr->left ){
			Node *replace = curr->right;
			free(curr);
			return replace;
		}
		else{
			Node *replace = get_predecessor(curr);
			curr->key = replace->key;
			curr->left = delete_node(curr->left, replace->key);
		}
	}
	
	curr->height = calculate_height(curr);
	curr = rebalance(curr);
	
	return curr;	
}

void preOrder(Node *node){
	if( node ){
		printf("%d ", node->key);
		preOrder(node->left);
		preOrder(node->right);
	}
}

int main(){
	
	ROOT = insert_node(ROOT, 1);
	ROOT = insert_node(ROOT, 2);
	ROOT = insert_node(ROOT, 3);
	
	preOrder(ROOT);		
	
	return 0;
}
