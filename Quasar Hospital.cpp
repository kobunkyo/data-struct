#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Emer = 1, Super Vip = 2, VIP =3, basic = 4

char PRIORITY[5][15]={
	"", "Emergency", "Super VIP", "VIP", "Basic"
};

struct Quasar{
	char patient_name[25];
	int priorityLevel;
	int age;
	struct Quasar *next, *prev;
}*head, *tail;

struct Quasar* Create(char* name, int level, int age){
	struct Quasar* new_data = (struct Quasar*) malloc(sizeof(struct Quasar));
	strcpy(new_data->patient_name, name);
	new_data->age = age;
	new_data->priorityLevel = level;
	new_data->next = NULL;
	new_data->prev = NULL;
	return new_data;
}

void Push_Head(struct Quasar* data){
	if(!head){
		head = tail = data;
	}else{
		head ->prev = data;
		data->next = head;
		head = data;
	}
}

void Push_Tail(struct Quasar* data){
	if(!head){
		head = tail = data;
	}else{
		tail->next = data;
		data->prev = tail;
		tail = data;
	}
}

void Push(struct Quasar* data){
	if(!head){
		head = tail = data;
	}
//	else if(data->priorityLevel<){}
	else if(data->priorityLevel>= tail->priorityLevel){
		Push_Tail(data);
	}else{
		struct Quasar* curr = head;
		while(curr->next!=tail){
			if(curr->next->priorityLevel > data->priorityLevel){
				break;
			}else{
				curr = curr->next;
			}
		}
		struct Quasar* left = curr->next;
		left->prev = data;
		data->next = left;
		data->prev = curr;
		curr->next = data;
	}
}

void Call_Queue(){
	if(!head){
		printf("No Patient to be called..\n\n");
		getchar();
	}else if(head == tail){
		printf("Patient from %s Room,\n", PRIORITY[head->priorityLevel]);
		printf("With name %s, %d years\n", head->patient_name, head->age);
		printf("Please moving ahead to Administration Room..");
		free(head);
		head = tail = NULL;
		getchar();
	}else{
		printf("Patient from %s Room,\n", PRIORITY[head->priorityLevel]);
		printf("With name %s, %d years\n", head->patient_name, head->age);
		printf("Please moving ahead to Administration Room..");
//		struct Quasar* tobeDeleted = head;
		head = head->next;
		free(head->prev);
		head->prev = NULL;
//		free(tobeDeleted);
		getchar();
	}
}

void Remove(){
	while(head!=tail){
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
	free(head);
	head = tail = NULL;
	printf("All patient list has been purged");
	getchar();
}

void view(){
	int Patient_Count = 0;
	if(!head){
		printf("Patient: %d people(s)\n\n", Patient_Count);
	}else{
		printf("Quasar Hospitals Queue\n");
		printf("-------------------------------------------------------\n");
		struct Quasar* data = head;
		
		while(data){
			Patient_Count++;
			printf("%2d. %-15s: %25s(%d)\n", Patient_Count, PRIORITY[data->priorityLevel], data->patient_name, data->age);
			data = data->next;
		}
		printf("\nPatient: %d people(s)\n\n", Patient_Count);
	}
}

int main(){
	int menu=0;
	do{
		system("cls");
		view();
		printf("Quasar Queue 1.3\n");
		printf("================\n");
		printf("1. Add Patient\n");
		printf("2. Call Patient\n");
		printf("3. Remove All Patient List\n");
		printf("4. Exit\n");
		printf("Select [1..4]: ");
		scanf("%d", &menu); fflush(stdin);
		printf("\n");
		switch(menu){
			case 1:
				system("cls");
				char name[25];
				int age;
				int level;
				do{
					printf("Input Patient Name [1..25]: ");
					scanf("%[^\n]", name); fflush(stdin);
				}while(strlen(name)<1||strlen(name)>25);
				printf("1. Emergency\n");
				printf("2. Super VIP\n");
				printf("3. VIP\n");
				printf("4. Basic\n");
				do{
					printf("Select Class [1..4]: ");
					scanf("%d", &level); fflush(stdin);
					printf("\n");	
				}while(level<1 || level>4);
				do{
					printf("Input Age[1..110]: ");
					scanf("%d", &age); fflush(stdin);
				}while(age<1 || age>110);
				Push(Create(name, level, age));
				break;
			case 2:
				Call_Queue();
				break;
			case 3:
				Remove();
				break;
			case 4:
				printf("Thank you for using Quasar 1.3\n");
				getchar();
				break;
		}
	}while(menu != 4);
	
	return 0;
}

