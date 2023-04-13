#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Linked List
// Objective pada linked list adalah menyimpan alamat pada struct
struct Product{
	char name[100];
	int prive;
	int stock;
};

// Singgle link list
struct Node{
	int value;
	char name[100];
//	Product product; // Untuk advance struct
	struct Node* next; // Pointer untuk data selanjutnya
};
// malloc = memory allocation, untuk menaruh suatu data pada memory pada saat running time si kode
// void* menghasilkan return void dan void pointer ada pada malloc
// free = menghapus lokasi memori

Node* HEAD = NULL;
Node* TAIL = NULL;

Node* create_node(int value, char* name){ // Fungsi membuat node untuk linked List
	struct Node* newNode= (Node*)malloc(sizeof(Node));
	newNode->value = value;
	strcpy(newNode->name, name);
//	(*newNode).value = value; // Alternatif
	newNode->next = NULL;
	return newNode; // Return address
}

void push_head(int value, char* name){ // Tambah alamat sebelum head
	struct Node* newNode = create_node(value, name);
	if (!HEAD){ // indikasi head = null
		HEAD = TAIL = newNode;
	}else{ // head yang sudah ada
		newNode->next = HEAD;
		HEAD = newNode;
	}
}

void push_tail(int value, char* name){ // Tambah alamat setelah tail
	struct Node* newNode = create_node(value, name);
	if(!TAIL){ // indikasi tail = null
		TAIL = HEAD = newNode;
	}else{ // tail yang sudah ada
		TAIL->next = newNode;
		TAIL = newNode;
	}
}

void pop_head(){ // Hapus alamat head
	if (!HEAD){
		printf("Linked list is empty!\n");
	}else if(HEAD ==  TAIL){
		free(HEAD);
		HEAD = TAIL = NULL;
	}else{
		struct Node* temp = HEAD;
		HEAD = HEAD->next; 
		free(temp);
		temp = NULL;
	}
}

void pop_tail(){
	if(!TAIL){
		printf("Linked list is empty!\n");
	}else if(HEAD ==  TAIL){
		free(HEAD);
		HEAD = TAIL = NULL;
	}else{
		struct Node* temp = HEAD;
		while(temp->next != TAIL){
			temp = temp->next;
		}
		TAIL = temp;
		free(TAIL->next);
		temp = NULL;
		TAIL->next = NULL;
	}
}

void pop_search(int value){
	if(!HEAD){
		printf("Data not Found!\n");
	}else if(value == HEAD->value){
		pop_head();
	}else if(value == TAIL->value){
		pop_tail();
	}else{
		struct Node* temp = HEAD;
		while(temp->next){
			if(temp->next->value == value){
				struct Node* left = temp;
				struct Node* right = temp->next->next;
				struct Node* toDelete = temp->next;
				left->next = right;
				free(toDelete);
				return;
			}
			temp = temp->next;
		}
	}
}

void view(){
	if(!HEAD){
		printf("Linked list is empty\n");
	}else{
		Node* temp = HEAD;
		while(temp){
			printf("(%s)%d -> ",temp->name, temp->value);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

int main(){
	push_head(15, "Reni");
	push_head(23, "Hani");
	push_tail(17, "Beni");
	push_head(22, "Koni");
	push_tail(56, "Joni");
	push_tail(53, "Budi");
//	
//	pop_head();
//	pop_tail();
//	pop_tail();
//	pop_tail();
//	pop_head();
//	pop_head();
	view();
	pop_search(17);
	view();
	return 0;
}
