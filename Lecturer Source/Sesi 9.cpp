#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Untuk konstanta
#define SIZE 4
// Untuk flush
#define f fflush(stdin)

struct Table{
	int key;
	char name[5];
	struct Table* next;
}*data[SIZE];

struct Bucket{
	Table* head;
	Table* tail;
}table[SIZE];

int count = 0;
int step[SIZE];



int stringToInt(char* name){
	int key = 0;
	int hashKey = 0;
	for(int i = 0; i<strlen(name); i++){
		key = key*100 + (name[i]-97);
	}
	return key;
}

int Hash(char *name){
	int key = stringToInt(name);
	int hashKey = 0;
	while(key!=0){
		hashKey = hashKey + key%10;
		key = key/10;
	}
//	for(int i=0; i<strlen(name)*2;i++){
//		temp = temp+key%10;
//		key = key/10;
//	}
//	printf("%d", temp);
	return hashKey%SIZE;
}

struct Table* Create(char* name){
	struct Table* newTable = (struct Table*)malloc(sizeof(struct Table));
	strcpy(newTable->name, name);
	newTable->key = Hash(name);
	newTable->next = NULL;
	return newTable;
}
void Push(struct Table* data){
	
}
void Insert(char* name){
	struct Table* new_data = Create(name);
	int key = Hash(name);
	int position = key;
	if(count>=SIZE){
		printf("Full!\n");
		return;
	}else{
		int i=0;
		while(data[position]!=NULL){
			position = (position+1)%SIZE;
			i++;
		}
		data[position] = new_data;
		step[position]=i+1;
		count++;
	}
}

void Pop_All(){
	for(int i=0; i<SIZE; i++){
		free(data[i]);
		data[i]=NULL;
	}
}

void View(){
	system("cls");
	printf("----------------------------\n");
	printf("| H[i] | Input | Hash | Step |\n");
	printf("----------------------------\n");
	for(int i=0; i<SIZE; i++){
		if(data[i]!=NULL){
			printf("| H[%d] | %5s | %04d | %04d |\n", i, data[i]->name, data[i]->key, step[i]);
		}else{
			printf("| H[%d] |      |      |       |\n", i);
		}
	}
}

int main(){
	char name[5]="abz";
	for(int i = 0; i<SIZE; i++){
		step[i]=0;
	}

	Insert("tzfo");
	Insert("nkkl");
	Insert("lqmk");
	Insert("xoji");
	View(); getchar();
	Pop_All();
	View();
	return 0;
}
