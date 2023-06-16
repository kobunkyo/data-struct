#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2602240045  - Christopher Angriawan

struct Data{
	int value;
	int height;
	struct Data* left;
	struct Data* right;
}*ROOT = NULL;

int maxHeight(int a, int b){
	return (a>b) ? a : b;
}

int heightTree(struct Data* node){
	return (!node) ? 0 : node->height;
}

int treeBalance(struct Data* node){
	return (!node) ? 0 : (heightTree(node->left) - heightTree(node->right));
}

struct Data* createData(int value){
	struct Data* newData = (struct Data*)malloc(sizeof(struct Data));
	newData->value = value;
	newData->height = 1;
	newData->left = NULL;
	newData->right = NULL;
	return newData;
}

struct Data* rightRotate(struct Data* node){
	struct Data* anchor = node->left;
	struct Data* reconnect = anchor->right;
	
	anchor->right = node;
	node->left = reconnect;
	
	node->height = 1 + maxHeight(heightTree(node->left), heightTree(node->right));
	anchor->height = 1 + maxHeight(heightTree(anchor->left), heightTree(anchor->right));
	
	return anchor;
}

struct Data* leftRotate(struct Data* node){
	struct Data* anchor = node->right;
	struct Data* reconnect = anchor->left;
	
	anchor->left = node;
	node->right = reconnect;
	
	node->height = 1 + maxHeight(heightTree(node->left), heightTree(node->right));
	anchor->height = 1 + maxHeight(heightTree(anchor->left), heightTree(anchor->right));
	
	return anchor;
}

struct Data* rebalancing(struct Data* root){
	int balanceFactor = treeBalance(root);
	
	// Left case
	if(balanceFactor > 1){
		if (treeBalance(root->left) < 0){
			root->left = leftRotate(root->left);
		}
		root = rightRotate(root);
	}
	//Right case
	else if(balanceFactor < -1){
		if (treeBalance(root->right) > 0){
			root->right = rightRotate(root->right);
		}
		root = leftRotate(root);
	}
	return root;
}

struct Data* insert(struct Data* root, int addedValue){
	if(!root){
		return createData(addedValue);
	}
	else if(addedValue < root->value){
		root->left = insert(root->left, addedValue);
	}
	else if(addedValue > root->value){
		root->right = insert(root->right, addedValue);
	}
	else{
		return root; // Jika angka sama
	}
	
	root->height = 1 + maxHeight(heightTree(root->left), heightTree(root->right));
	root = rebalancing(root);
	
	return root;
}
struct Data* predecessor(struct Data* root){
	struct Data* temp = root->left;
	while(temp->right){
		temp = temp->right;
	}
	return temp;	
}

struct Data* Delete(struct Data* root, int deleteValue){
	if(!root){
		return root;
	}
	else if(deleteValue < root->value){
		root->left = Delete(root->left, deleteValue);
	}
	else if(deleteValue > root->value){
		root->right = Delete(root->right, deleteValue);
	}
	else if(deleteValue == root->value){
		// Node 1 anak / Leaf node
		if(root->left == NULL || root->right == NULL){
			struct Data* temp = NULL;
			if(root->left){
				temp = root->left;
			}
			else if(root->right){
				temp = root->right;
			}
			free(root);
			root = temp;
			return root;
		}
		else{
			struct Data* temp = predecessor(root);
			root->value = temp->value;
			root->left = Delete(root->left, temp->value);
		}
	}
	
	root->height = 1 + maxHeight(heightTree(root->left), heightTree(root->right));
	root = rebalancing(root);
	
	return root;
}

int searchData(struct Data* root, int searchValue){
	if(!root){
		printf("Data not found\n");
		return 0;
	}
	else if(searchValue < root->value){
		return searchData(root->left, searchValue);
	}
	else if(searchValue > root->value){
		return searchData(root->right, searchValue);
	}
	else if(searchValue == root->value){
		printf("Data Found\n");
		return 1;
	}
}

//Transversal
void preOrder(struct Data* root){
	if(root){
		printf("%d ", root->value);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(struct Data* root){
	if(root){
		inOrder(root->left);
		printf("%d ", root->value);
		inOrder(root->right);
	}
}

void postOrder(struct Data* root){
	if(root){
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->value);
	}
}

void menu(){
	printf("1. Insertion\n");
	printf("2. Deletion\n");
	printf("3. Traversal\n");
	printf("4. Exit\n");
	printf("Choose: ");
}

void traversal(){
	printf("Preorder: ");
	preOrder(ROOT); puts("");
	printf("Inorder: ");
	inOrder(ROOT); puts("");
	printf("Postorder: ");
	postOrder(ROOT); puts("");
}

int main(){
	int input;
	int flag;
	do{
		system("cls");
		menu();
		scanf("%d", &input); fflush(stdin);
		switch (input){
			case 1:
				int inputValue;
				
				printf("Insert: ");
				scanf("%d", &inputValue); fflush(stdin);
				
				ROOT = insert(ROOT, inputValue);
				getchar();
				break;
			case 2:
				int deleteValue;
				flag = 0;
				printf("Delete: ");
				scanf("%d", &deleteValue); fflush(stdin);
				
				flag = searchData(ROOT, deleteValue);
				if(flag == 1){
					ROOT = Delete(ROOT, deleteValue);
					printf("Value %d was deleted", deleteValue);
				}
				getchar();
				break;
			case 3:
				traversal();
				getchar();
				break;
			case 4:
				printf("Thank you\n");
				getchar();
				break;
			default:
				break;
		}
			
		
	}while (input != 4);
	return 0;
}
