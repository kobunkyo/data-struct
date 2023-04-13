#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash tabble seperti lemari
// Hash key = penentu data yang akan di letakan
// Hashing akan menghasilkan hash key
// Collision handling = mengantisipasi data yang sama
// Linear probing dan chaining salah satu cara dari collision handling
// Linear probing masukin secara linear
// Chaining pakai linked list

#define SIZE 10

struct Animal{
	char name[50];
}*cage[SIZE];

int count = 0; // Hitung binatang yang masuk ke kandang

struct Animal* create(char* name){
	struct Animal* new_animal = (struct Animal*)malloc(sizeof(struct Animal));
	strcpy(new_animal->name, name);
	return new_animal;
}

int hash(char* name){
	int key = 0;
	int len = strlen(name);
	for (int i=0; i < len; i++){
		key += name[i];
	}
	return key % SIZE; //biar tidak oversize untuk 'kandangnya'
}

void insert(char* name){
	struct Animal* new_animal = create(name);
	int hashKey = hash(name);
	int position = hashKey;
	
	// Kondisi yang diperhatikan
	// Kalau kandang penuh
	if(count >= SIZE){
		printf("Cage is full\n");
		return;
	}
	// Kalau terjadi collision
	while(cage[position]!=NULL){
		position = (position + 1)%SIZE;
	}
	// Kalau kandang kosong
	cage[position] = new_animal;
	count++;
}

void view(){
	for(int i = 0; i< SIZE; i++){
		if(cage[i]!=NULL){
			printf("%d. %-8s [%d]\n", i, cage[i]->name, hash(cage[i]->name));
		}else{
			printf("%d. \n",i);
		}
	}
}

void search(char* name){
	int hashKey = hash(name);
	int position = hashKey;
	do{
		if(cage[position != NULL] && strcmp(cage[position]->name, name)==0){
			printf("%s is found!\n", name);
			return;
		}
		position = (position + 1) % SIZE;
//		printf("Pos = %d\n", position);
	}while(position!=hashKey);
	printf("Data is not availabe!\n");
}

void removes(char *name){
	int hashKey = hash(name);
	int position = hashKey;
	do{
		if(cage[position] != NULL && strcmp(cage[position]->name, name) == 0){
			printf("%s is successfully removed\n", name);
			free(cage[position]);
			cage[position] = NULL;
			return;
		}
		position = (position +1) % SIZE;
	}while(position != hashKey);
	printf("%s not available!\n", name);
}

int main(){
//	printf("%d\n", hash("Chicken"));
//	printf("%d\n", hash("Buffalo"));
//	printf("%d\n", hash("Penguin"));

	insert("Antelope");
	insert("Lion");
	insert("Elephant");
	insert("Giraffe");
	insert("Penguin");
	insert("Cappybara");
	insert("Hippo");
	insert("Cat");
	insert("Dog");
	insert("Fish");
	insert("Bear");	

	view();
	
	search("Hippo");
	removes("Fish");
	view();
	return 0;
}
