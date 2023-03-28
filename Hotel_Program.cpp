#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100

struct Hotel{
	int age;
	int duration;
	char name[31];
	char phoneNumber[35];
	char roomType[15];
	char id[6];
	struct Hotel* next;
}*table[SIZE], *tail[SIZE];

int count=0; // Hitung input data untuk view

struct Hotel* create(int age, int duration, char* name, char* phoneNumber, char* roomType){
	struct Hotel* newData = (struct Hotel*)malloc(sizeof(struct Hotel));
	newData->age = age;
	newData->duration = duration;
	strcpy(newData->name, name);
	strcpy(newData->phoneNumber, phoneNumber);
	strcpy(newData->roomType, roomType);
	sprintf(newData->id,"%c%c%d%d%d", toupper(roomType[0]), toupper(roomType[1]), rand()%10, rand()%10, rand()%10);
	newData->next = NULL;
	return newData;
}

int hashKey(char* id){
	int key = -1;
	for(int i=0; i<3; i++){
		key = key + id[i+2] - '0';
	}
	return key%SIZE;
}

void insert(struct Hotel* data){
	int key = hashKey(data->id);
	if( !table[key] ){
		table[key] = data;
		tail[key] = data;
	}
	else if( table[key] ){
		data->next = tail[key];
		tail[key] = data;
	}
	count++;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t+-------------------------------------------------+\n");
	printf("\t| Booking ID 	 : %-30s |\n", data->id);
	printf("\t+-------------------------------------------------+\n");
	printf("\t| Full Name	 : %-30s |\n", data->name);
	printf("\t| Phone Number 	 : %-30s |\n", data->phoneNumber);
	printf("\t| Room Type	 : %-30s |\n", data->roomType);
	printf("\t| Night Stay	 : %-30d |\n", data->duration);
	printf("\t+-------------------------------------------------+\n\n");
	printf("\tPress ENTER to continue..\n");
	getchar();
	fflush(stdin);
}

// Gak muncul semua
void view(){
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	for(int i=0; i<SIZE; i++){
		struct Hotel* temp = table[i];
		while(temp){
			printf("\t+-------------------------------------------------+\n");
			printf("\t| Booking ID 	 : %-30s |\n", temp->id);
			printf("\t+-------------------------------------------------+\n");
			printf("\t| Full Name	 : %-30s |\n", temp->name);
			printf("\t| Phone Number 	 : %-30s |\n", temp->phoneNumber);
			printf("\t| Room Type	 : %-30s |\n", temp->roomType);
			printf("\t| Night Stay	 : %-30d |\n", temp->duration);
			printf("\t+-------------------------------------------------+\n\n");
			temp= temp->next;
		}
			
	}
	if(count == 0){
		printf("\t+----------------------+\n");
		printf("\t| There is no booking! |\n");
		printf("\t+----------------------+\n\n");
	}
	
}
void noData(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t+--------------------------------------+\n");
	printf("\t| Failed to Delete, There is no Data ! |\n");
	printf("\t+--------------------------------------+\n\n");
}

void successToDelete(char* id){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t+-------------------------------------------+\n");
	printf("\t| BookingID %s is Successfully Deleted ! |\n", id);
	printf("\t+-------------------------------------------+\n\n");
}

void popSearch(){
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	if(count == 0){
		printf("\t+----------------------+\n");
		printf("\t| There is no booking! |\n");
		printf("\t+----------------------+\n\n");
	}else if(count>0){
		view();
		char id[6];
		printf("\tInput Booking ID (Case Sensitive): ");
		scanf("%s", id); fflush(stdin);
		int key = hashKey(id);
		if(!table[key]){
			noData();
		}else if(strcmp(table[key]->id, id)==0){
			struct Hotel* temp = table[key];
			table[key] = temp->next;
			free(temp);
			temp = NULL;
			successToDelete(id);
		}else{
			struct Hotel* current = table[key];
			while(current->next){
				if(strcmp(current->next->id, id)!=0){
					current = current->next;
				}
			}
			struct Hotel* forDelete = current->next;
			current->next = forDelete->next;
			free(forDelete);
			forDelete = NULL;
			successToDelete(id);
		}
	}
	printf("\tPress ENTER to continue..\n");
	getchar();
}

int main(){
	for(int i=0; i<SIZE; i++){
		table[i]=NULL;
	}
	int input = 0;
	do{
		input = 0;
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("\t+--------------------+\n");
		printf("\t| Hotel GrAnsylvania |\n");
		printf("\t+--------------------+\n\n");
		printf("\t1. Booking Hotel\n");
		printf("\t2. View Bookings\n");
		printf("\t3. Delete Booking\n");
		printf("\t4. Exit\n");
		printf("\t>> ");
		scanf("%d", &input); fflush(stdin);
		switch(input){
			case 1:
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				// Input nama
				char name[31];
				do{
					printf("\tInput Full Name [3..30] : ");
					scanf("%[^\n]", name); fflush(stdin);
					if(strlen(name)<3 || strlen(name)>30){
						printf("\tFull name length must between 3 and 30\n");
					}
				}while(strlen(name)<3 || strlen(name)>30);
				
				// Input nomor
				char indent[4]; // Full nomor
				char number[30]; // Input nomor
				char symbol[4]; //Validasi +62
				int len;
				do{
					len = 0;
					printf("\tInput Phone Number : ");
					scanf("%s%[^\n]", indent, number); fflush(stdin);
					for(int i=0; i<strlen(number); i++){
						if(number[i]!=' '){
							len++;
						}
					}
					strcpy(symbol, indent);
					strcat(indent, number);
					if(len!=11 || strcmp(symbol, "+62")!=0 || indent[3]!= ' '){
						printf("\tPhone number must begin with '+62', contains with at least 1 space and the lenght must be 11 (Exclude +62 and space)\n");
					}
				}while(len!=11 || strcmp(symbol, "+62")!=0 || indent[3]!= ' ');
				
				// Input umur
				int age;
				do{
					printf("\tInput Age [Minimum 18]: ");
					scanf("%d", &age); fflush(stdin);
					if(age<18){
						printf("\tAge must be minimum 18\n");
					}
				}while(age<18);
				
				//Input tipe ruangan
				char type[15];
				int typeVal;
				do{
					typeVal=1;
					printf("\tInput Room Type [Regular | Deluxe | Suite] (Case Sensitive): ");
					scanf("%s", type); fflush(stdin);
					if(strcmp(type, "Regular")==0){
						typeVal=0;
					}else if(strcmp(type, "Deluxe")==0){
						typeVal=0;
					}else if(strcmp(type, "Suite")==0){
						typeVal=0;
					}
					if(typeVal!=0){
						printf("\tRoom type must be either Regular or Deluxe or Suite (Case Sensitive)\n");
					}
					
				}while(typeVal!=0);
				
				//Input waktu
				int duration;
				do{
					printf("\tInput How Many Night You Will Stay [1..30] : ");
					scanf("%d", &duration); fflush(stdin);
					if(duration<1 || duration>30){
						printf("\tYou can't stay less than 1 night or more than 30 nights\n");
					}
				}while(duration<1 || duration>30);
				insert(create(age, duration, name, indent, type));
				
				break;
				
			case 2:
				view();
				printf("\tPress ENTER to continue..\n");
				getchar();
				break;
			case 3:
				popSearch();
				break;
			case 4:
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				printf("\t+---------------------------+\n");
				printf("\t| Thank You For Your Stay ! |\n");
				printf("\t+---------------------------+\n\n");
				printf("\tPress ENTER to continue..\n");
				getchar();
				break;
		}
			
		
	}while(input!=4);
	return 0;
}
