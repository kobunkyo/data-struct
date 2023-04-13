#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 26

struct Animal{
	char name[50];
	struct Animal* next;
}*cage[SIZE];

int hash(char* name){
	return toupper(name[0]) - 'A';
}

struct Animal* create(char* name){
	struct Animal* new_animal = (struct Animal*)malloc(sizeof(struct Animal));
	strcpy(new_animal->name, name);
	new_animal->next = NULL;
	return new_animal;
}

void insert(char* name){
	struct Animal* new_animal = create(name);
	int position = hash(name);
	
	//Kalo kandang masih kosong
	if(cage[position] == NULL){
		cage[position] = new_animal;
		return;
	}
	//Kalo kandang gak kosong
	// cage[position] = head
	new_animal->next = cage[position];
	cage[position] = new_animal;
}

void view(){
	for(int i = 0; i< SIZE; i++){
		printf("%d. ", i);
		struct Animal* curr = cage[i];
		while(curr!=NULL){
			printf("%s -> ", curr->name);
			curr = curr->next;
		}
		printf("\n");
	}
}

void removes(char* name){
	int position = hash(name);
	struct Animal* curr = cage[position];
	// Kalo binatang ada di paling depan
	if(strcmp(curr->name, name)==0){
		printf("\n%s is successsfully deleted\n\n", name);
		struct Animal* temp = curr;
		cage[position] = temp->next;
		free(temp);
		temp = NULL;
		return;
	}
	// Kalo binatang ada di tengah
	while(curr != NULL && strcmp(curr->next->name, name) != 0){
		curr = curr->next;
	}
	if(curr == NULL){
		printf("Animal not available!\n");
		return;
	}
	printf("\n%s is successsfully deleted\n\n", name);
	struct Animal* to_deleted = curr->next;
	curr->next = to_deleted->next;
	free(to_deleted);
	to_deleted = NULL;
	
	
}

int main(){
	insert("Chicken");
	insert("Capybara");
	insert("Hippo");
	insert("Antelope");
	insert("Polar Bear");
	insert("Bear");
	insert("Zebra");
	insert("Penguin");
	insert("Dolphin");
	insert("Duck");
	insert("Lion");
	insert("Tiger");
	view();
	removes("Chicken");
	view();
	return 0;
}
