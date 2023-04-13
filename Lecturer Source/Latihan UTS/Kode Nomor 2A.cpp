#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 11

struct Table{
	int number;
}*table[11];

struct Table* create(int number){
	struct Table* data = (struct Table*)malloc(sizeof(struct Table));
	data->number = number;
	return data;
}

int hash(int number){
	return number%11;
}

void insert(int number){
	struct Table* data = create(number);
	int key = hash(number);
	int position = key;
	
	if(!table[key]){
		table[key] = data;
		printf("Success to insert\n");
	}else{
		while(table[position]){
			position = (position+1) % 11;
		}
		if(position == key){
			printf("Data full\n");
			return;
		}
		if(position != key){
			table[position] = data;
			printf("Success to insert\n");
			return;
		}
	}
}

void view(){
	for(int i = 0; i<SIZE; i++){
		printf("%d. %d\n", i, table[i]->number);
	}
}

int main(){
	insert(51);
	insert(22);
	insert(33);
	insert(45);
	insert(81);
	insert(60);
	insert(63);
	insert(69);
	insert(60);
	insert(55);
	insert(21);
	view();
	return 0;
}
