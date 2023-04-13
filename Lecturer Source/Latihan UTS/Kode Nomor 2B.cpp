 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 1000

struct Tabel{
	int num;
}*table[SIZE];

struct Tabel* create(int num){
	struct Tabel* data = (struct Tabel*)malloc(sizeof(struct Tabel));
	data->num = num;
	return data;
}
// Masih berantakan 1-3-3 harusnya 3-3-1
int hash(int num){
	char str[100];
	sprintf(str, "%d", num);
	int key = 0;
	int temp = num;
	if(strlen(str)%3 == 0){
		while(temp != 0){
			key = key + (temp%SIZE);
			temp = temp/SIZE;
		}	
	}else if(strlen(str)%3 == 1){
		key = key+ (temp%10);
		temp = temp/10;
		while(temp != 0){
			key = key + (temp%SIZE);
			temp = temp/SIZE;
		}
	}else{
		key = key+ (temp%100);
		temp = temp/100;
		while(temp != 0){
			key = key + (temp%SIZE);
			temp = temp/SIZE;
		}
	}
	return key%SIZE;
}

void insert(int num){
	struct Tabel* data = create(num);
	int key = hash(num);
	int position = key;
	if(!table[key]){
		table[key] = data;
		printf("%d -> key(%d)\n", num, key);
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
//			printf("Success to insert\n");
			printf("%d -> key(%d)\n", num, key);
			return;
		}
	}
}

void view(){
	for(int i=0; i<SIZE; i++){
		printf("(%d) -> %d\n", i, table[i]->num);
	}
}

int main(){
//	printf("%d", NULL);
	insert(1921678);
	insert(777281);
	insert(1892);
	insert(1921);
	insert(21017);
	return 0;
}
