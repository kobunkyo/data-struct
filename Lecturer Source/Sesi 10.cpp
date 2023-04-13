#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Untuk konstanta
#define SIZE 4

struct Table{
	int key;
	char data[100];
	struct Table* next;
}*data[SIZE];

struct Bucket{
	Table* head = NULL;
	Table* tail = NULL;
}table[SIZE];

int StringToInt(char* input){
	int sum = 0;
	int length = strlen(input);
	for(int i = 0; i<length; i++){
		sum = sum+input[0];
	}
	return sum;
}

int Division(char* input){
	int key = StringToInt(input);
	return key % SIZE;
}

struct Table* Create(char* input){
	struct Table* newTable = (struct Table*)malloc(sizeof(struct Table));
	strcpy(newTable->data, input);
	newTable->key = Division(input);
	newTable->next = NULL;
	return newTable;
}

void Push(Table *data){
	if(!table[data->key].head){
		table[data->key].head = table[data->key].tail = data;
	}else{
		table[data->key].tail->next = data;
		table[data->key].tail = data;
	}
}

void View(){
	for(int i = 0; i<SIZE; i++){
		struct Table* temp = table[i].head;
		printf("HT[%d]: ", i);
		while(temp){
			printf("%s -> ", temp->data);
			temp=temp->next;
		}
		printf("null\n");
	}
}

int main(){
	Push(Create("Nasi Bakar"));
	Push(Create("Ayam Goreng"));
	Push(Create("Nasi Goreng"));
	Push(Create("Ayam Bakar"));
	Push(Create("Mie Bakar"));
	Push(Create("Mie Goreng"));
	View();
	return 0;
}
