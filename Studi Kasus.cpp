#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data{
	char name[31];
	char condition[15];
	int priority;
	struct Data* next;
	struct Data* prev;
};
struct Data* head = NULL;
struct Data* tail = NULL;

struct Data* create(char* name, char* condition){
	struct Data* data = (struct Data*)malloc(sizeof(struct Data));
	strcpy(data->name, name);
	strcpy(data->condition, condition);
	if(strcmp(condition, "Critical")==0){
		data->priority = 1;
	}else if(strcmp(condition, "Serious")==0){
		data->priority = 2;
	}else if(strcmp(condition, "Fair")==0){
		data->priority = 3;
	}else{
		data->priority = 4;
	}
	data->next = NULL;
	data->prev = NULL;
	return data;
}

void view(){
	struct Data* temp = head;
	while(temp){
		if(temp->next == NULL){
			printf("%s\n", temp->name);
		}else printf("%s, ", temp->name);
		temp=temp->next;
	}
	return;
}

void insert(char* name, char* condition){
	struct Data* data = create(name, condition);
	if(!head){
		head = tail = data;
	}else if(data->priority >= tail->priority){
		tail->next = data;
		data->prev = tail;
		tail = data;
	}else{
//		printf("pop search\n");
		struct Data* curr = head;
		while(curr->next != NULL && data->priority >= curr->priority){
			curr = curr->next;
		}
		struct Data* left = curr->prev;
		struct Data* right = curr;
		
		if(curr == head){
			data->next = right;
			right->prev = data;
			head = data;
		}else{
			left->next = data;
			data->prev = left;
			data->next = right;
			right->prev = data;
		}
//		printf("pop search end\n");
	}
	printf("Waiting room: "); view();
	printf("\n");
}

void pop(){
	if(!head){
		printf("No data\n");
		return;
	}else if(head == tail){
		free(head);
		head = tail = NULL;
	}else{
		if(strcmp(head->condition, "Critical")==0){
			printf("%s is in the Emergecy Room\n", head->name);
		}else if(strcmp(head->condition, "Serious") == 0){
			printf("%s is in the Examination Room\n", head->name);
		}else{
			printf("%s is in the Consultation Room\n", head->name);
		}
		struct Data* toDelete = head;
		head = head->next;
		free(toDelete);
		toDelete = NULL;
	}
	return;
}

int main(){
	int n;
	char c1[100];
	char c2[3][31];
	scanf("%d", &n); fflush(stdin);
	for(int i=0; i<n; i++){
//		scanf(" %s %s %s", c1, c2, c3);
		scanf("%[^\n]", c1); fflush(stdin);
		if(strcmp(c1, "CALL")==0){
			printf("pop\n");
			pop();
			
		}else{
			int j=0;
			int line=0;
			for(int l=0; l<=strlen(c1); l++){
				if(c1[l]==' '|| c1[l]=='\0'){
					c2[line][j]='\0';
					j=0;
					line++;
				}else{
					c2[line][j] = c1[l];
					j++;
				}
			}
			// Debugger
//			for(int l=0; l<strlen(c2[1]); l+=2){
//				printf("%c-%c-", c2[1][l], c2[1][l+1]);
//				if(c2[1][l] == ' '){
//					printf("%d\n", l);
//				}else if(c2[1][l+1] == ' '){
//					printf("%d\n", l+1);
//				}
//			}
//			printf("\n");
//			for(int l=0; l<strlen(c2[2]); l+=2){
//				printf("%c-%c-", c2[2][l], c2[2][l+1]);
//				if(c2[2][l] == ' '){
//					printf("%d\n", l);
//				}else if(c2[2][l+1] == ' '){
//					printf("%d\n", l+1);
//				}
//			}
			printf("\n");
			insert(c2[1],c2[2]);
		}
	}
	printf("Waiting Room: "); view();
	return 0;
}
