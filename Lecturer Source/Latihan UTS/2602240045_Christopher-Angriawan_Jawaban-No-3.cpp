#include <stdio.h>
#include <conio.h>
#include <malloc.h>
struct node {
	int key;
	struct node *left;
	struct node *right;
} *root;

void search(struct node* curr, int find) {
//INSERT YOUR CODE HERE
	if(curr==NULL){
		printf("%d is not found\n", find); // Kalo gak ketemu
	}else if(curr->key == find){
		printf("%d is found\n", find); // Kalo ketemu
		return;
	}else if(find<curr->key){
		search(curr->left, find); // Cari ke cabang kiri
	}else if(find>curr->key){
		search(curr->right, find); // Cari ke cabang kanan
	}
}

void insert(struct node* curr, int val) {
	struct node *new_node = (struct node*) malloc(sizeof(struct node));
// Pemborosan memori
	new_node->key = val;
	new_node->left = NULL;
	new_node->right = NULL;
	if (root == NULL) {
		root = new_node;
	}
	else if (val != curr->key) {
		if (val < curr->key && curr->left == NULL) {
			curr->left = new_node;
		}
		else if (val > curr->key && curr->right == NULL) {
			curr->right = new_node;
		}
		else if (val < curr->key && curr->left != NULL) {
			insert(curr->left, val);
		}
		else if (val > curr->key && curr->right != NULL) {
			insert(curr->right, val);
		}
	}
}

void inorder_traversal(struct node* curr) {
	if (curr == NULL) return;
	inorder_traversal(curr->left);
	printf("%d ", curr->key);
	inorder_traversal(curr->right);
}

void preorder_traversal(struct node* curr) {
//INSERT YOUR CODE HERE
	if (curr == NULL) return;
	printf("%d ", curr->key);
	preorder_traversal(curr->left);
	preorder_traversal(curr->right);
}

void postorder_traversal(struct node* curr) {
//INSERT YOUR CODE HERE
	if (curr == NULL) return;
	postorder_traversal(curr->left);
	postorder_traversal(curr->right);
	printf("%d ", curr->key);
}

void executeDeleteNode(struct node* parent, struct node* curr) {
//INSERT YOUR CODE HERE
	if(curr->right==NULL && curr->left == NULL){
		if(parent->left == curr){
			parent->left=NULL;
			free(curr);
			curr = NULL;
		}else if(parent->right == curr){
			parent->right = NULL;
			free(curr);
			curr = NULL;
		}
	}else if(curr->right!=NULL && curr->left == NULL){
		if(parent->left == curr){
			parent->left = curr->right;
			free(curr);
			curr = NULL;
		}else if(parent->right == curr){
			parent->right = curr->right;
			free(curr);
			curr = NULL;
		}
	}else if(curr->right == NULL && curr->left != NULL){
		if(parent->left == curr){
			parent->left = curr->left;
			free(curr);
			curr = NULL;
		}else if(parent->right == curr){
			parent->right = curr->left;
			free(curr);
			curr = NULL;
		}
	}else if(curr->right != NULL && curr->left != NULL){
		struct node* tempParent; 
		struct node* temp = curr->left;
		while(temp->right!=NULL){
			tempParent = temp; // Cari parent sebelum node paling ujung
			temp = temp->right; // Node paling ujung pengganti yang mau dihapus
		}
		curr->key = temp->key; // Pindahin value ke address node yang mau dihapus
		executeDeleteNode(tempParent, temp); // Hapus node yang angkanya di duplikat
	}
}

void deleteNode(struct node* curr, int find) {
	struct node *parent;
	parent = curr;
	while (curr != NULL && curr->key != find) {
		if (find < curr->key) {
			parent = curr;
			curr = curr->left;
		}
		else if (find > curr->key) {
			parent = curr;
			curr = curr->right;
		}
	}
	if (curr == NULL) {
		printf("%d is not found");
	}
	else if (curr->key == find) {
		executeDeleteNode(parent, curr);
		}
}

int minValue(struct node* node) {
//INSERT YOUR CODE HERE
	while(node->left){
		node=node->left; // Cari node paling kiri
	}
	return node->key;
}

int maxValue(struct node* node){
//INSERT YOUR CODE HERE
	while(node->right){
		node = node->right; // Cari node paling kanan
	}
	return node->key;
}

int count(struct node* node){
//INSERT YOUR CODE HERE
	int x = 1;
	if(node == NULL){
		return 0;
	}else{
		// Algoritma post order
		x = x + count(node->left); // Cari ke kiri
		x = x + count(node->right); // Cari ke kanan
		return x; // Print jadi return angka
	}
}

int height_of_binary_tree(struct node *node){
//INSERT YOUR CODE HERE
	if(node==NULL){
		return 0; // Kalo gak ada node
	}else{
		int left,right;
		left = height_of_binary_tree(node->left);
		right = height_of_binary_tree(node->right);
		if(left > right){ // Bandingin tinggi cabang kiri dan kanan
			return left+1; // Tinggi cabang sebelum + diri sendiri
		}else{
			return right+1;
		}
		
	}
}

int main() {
	root = NULL;
	insert(root, 54);
	insert(root, 81);
	insert(root, 16);
	insert(root, 27);
	insert(root, 9);
	insert(root, 36);
	insert(root, 63);
	insert(root, 72);
	printf("Total node in BST: %d \n",count(root));
	printf("Height of binary tree : %d\n ", height_of_binary_tree(root));
	printf("\nInorder: "); inorder_traversal(root);
	printf("\nPreorder: "); preorder_traversal(root);
	printf("\nPostorder: "); postorder_traversal(root);
	puts("");
	deleteNode(root, 54); // 36 ke duplikat
	printf("\nPreorder (after del 54): "); preorder_traversal(root);
	deleteNode(root, 9);
	printf("\nPostorder (after del 9): "); postorder_traversal(root);
	deleteNode(root, 81);
	printf("\nInorder (after del 81): "); inorder_traversal(root);
	puts("");
	printf("Min value: %d \n", minValue(root));
	printf("Max value: %d \n", maxValue(root));
	puts("");
	search(root, 10);
	search(root, 8);
	_getch();
	return 0;
}
