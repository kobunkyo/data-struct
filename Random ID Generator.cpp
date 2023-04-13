#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 26

int hash(char*name){
	return toupper(name[0]) - 'A';
}

struct Animal{
	char ID[6];
	char name[50];
	struct Animal* next;
}*cage[SIZE];

struct Animal* create(char* name){
	struct Animal* newAnimal = (struct Animal*)malloc(sizeof(struct Animal));
	char ID[6];
	// Untuk buat ID (masukin nilai ke ID pake sprinf)
	sprintf(ID, "%c%d%d%d", toupper(name[0]), rand()%10, rand()%10, rand()%10);
	strcpy(newAnimal->ID, ID);
	strcpy(newAnimal->name, name);
	newAnimal->next = NULL;
	return newAnimal;
}

void insert(char* name){
	struct Animal* newAnimal = create(name);
	int position = hash(name);
	
	// Kalo gak ada binatang di dalam kandang
	if(!cage[position]){
		cage[position]=newAnimal;
		return;
	}
	
	// Kalo ada binatang
	struct Animal* curr = cage[position];
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next = newAnimal;
	
}

void print(){
	for(int i=0; i<SIZE; i++){
		printf("%d. ", i);
		struct Animal* curr = cage[i];
		while(curr != NULL){
			printf("%s [%s] -> ", curr->name, curr->ID);
			curr = curr->next;
		}
		printf("\n");
	}
}

void pop(char* name){
	int position = hash(name);
	// Kalo kandang kosong
	if(!cage[position]){
		printf("%s is not available[1]\n", name);
		return;
	}
	// Kalo binatang yang dicari ada di depan (head)
	if(strcmp(cage[position]->name, name)==0){
		printf("%s is successfully deleted[2]\n", name);
		struct Animal* toDelete = cage[position];
		cage[position] = toDelete->next;
		printf("toDelete: %x - ", toDelete);
		free(toDelete);
		printf("toDelete->next: %x - ", toDelete->next);
		printf("toDelete->name: %s - ", toDelete->name);
		toDelete = NULL;
		return;
	}
	// Kalo binatang di tengah
	struct Animal* curr = cage[position];
	struct Animal* prev = curr;
	while(curr != NULL && strcmp(curr->name, name)!=0){
		prev = curr;
		curr = curr->next;
//		printf("prev: %s ",prev->name);
//		printf("curr: %s\n",curr->name);
	}
	
	// Kalo binatang gak ketemu
	if(curr == NULL){
		printf("%s is not available[3]\n", name);
		return;
	}
	
	// Kalo binatang ketemu
	prev->next = curr->next;
	free(curr);
	curr = NULL;
	printf("%s is successfully deleted[4]\n", name);
	return;
}

void popAll(){
	for(int i=0; i<SIZE; i++){
		struct Animal* curr = cage[i];
		while(curr){
			pop(curr->name);
			printf("curr: %x ", curr);
			curr=curr->next;
			printf("- curr->next: %x\n\n", curr);
		}
	}
	printf("Pop All success\n");
}

int main(){
	insert("Chicken");
	insert("Dolphin");
	insert("Capybara");
	insert("Ant");
	insert("Tiger");
	insert("Lizard");
	insert("Calf");
	insert("Lion");
	insert("Komodo");
	insert("Girrafe");
	print();
//	pop("Bird");
//	pop("Ant");
//	pop("Chick");
//	pop("Capybara");
	popAll();
	return 0;
}
