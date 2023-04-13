#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Push
		Push head
		Push mid / search
		Push tail
	
	Pop
		Pop head
		Pop mid / search
		Pop tail
*/
struct Student{
	char nim[11];
	int ipk;
	struct Student* prev;
	struct Student* next;
}*HEAD = NULL, *TAIL = NULL;
//struct Student* HEAD = NULL;

struct Student* Create_Node(char* nim, int ipk){
	struct Student* newNode = (Student*)malloc(sizeof(struct Student));
	strcpy(newNode->nim, nim);
	newNode->ipk = ipk;
	newNode->prev=NULL;
	newNode->next=NULL;
	return newNode;
}

void Push_Head(struct Student* newNode){
//	struct Student* newNode = Create_Node(temp->nim, temp->ipk);
	if(!HEAD){
		// Tidak ada data
		HEAD = TAIL = newNode;
	}else{
		// Ada data
		newNode->next = HEAD;
		HEAD->prev = newNode;
		HEAD = HEAD->prev;
	}
}

void Push_Tail(struct Student* newNode){
//	struct Student* newNode = Create_Node(temp->nim, temp->ipk);
	if(!HEAD){
		// Tidak ada data
		HEAD = TAIL = newNode;
	}else{
		// Ada data
		TAIL->next = newNode;
		newNode->prev = TAIL;
		TAIL = TAIL->next;
	}
}

//Data diurutkan lalu di input
void Push_Mid(struct Student* newNode){
	//Urutkan dengan NIM, ascending (kecil ke besar)
	
	if(!HEAD){
		// Tidak ada data
		HEAD = TAIL = newNode;
	}else{
		// Ada ada
		if(strcmp(newNode->nim, HEAD->nim)<0){
			Push_Head(newNode);
		}else if(strcmp(newNode->nim, TAIL->nim)>0){
			Push_Tail(newNode);
		}else{
			struct Student* current = HEAD;
			while(current->next!=TAIL){
				if(strcmp(current->next->nim, newNode->nim)<0){
					current = current->next;
				}else{
					break;
				}
			}
			// Connect newNode dengan current dan current->next
			newNode->next = current->next;
			newNode->prev = current;
			current->next->prev = newNode;
			current->next = newNode;
		}
	}
		
}

void Pop_Head(){
	if(!HEAD){
//		printf("No data\n");
		return;
	}else if(HEAD == TAIL){
		free(HEAD);
		HEAD = TAIL = NULL;
	}else{
//		struct Student* target = HEAD;
//		HEAD = HEAD->next;
//		HEAD->prev = NULL;
//		target->next = NULL;
//		free(target);
		HEAD = HEAD->next;
		free(HEAD->prev);
		HEAD->prev = NULL;
	}
}


void Pop_Tail(){
	if(!HEAD){
//		printf("No data\n");
		return;
	}else if(HEAD == TAIL){
		free(HEAD);
		HEAD = TAIL = NULL;
	}else{
//		struct Student* target = TAIL;
//		TAIL = TAIL->prev;
//		TAIL->next = NULL;
//		target->prev = NULL;
//		free(target);
		TAIL = TAIL->prev;
		free(TAIL->next);
		TAIL->next = NULL;
	}
}

void Pop_Mid(char* nim){
	if(!HEAD){
		return;
	}else{
		if(strcmp(nim, HEAD->nim)==0){
			Pop_Head();
		}else if(strcmp(nim, TAIL->nim)==0){
			Pop_Tail();
		}else{
			struct Student* current=HEAD;
			while(current != TAIL){
				if(strcmp(current->nim, nim)==0){
					break;
				}else{
					current = current->next;
				}
			}
//			printf("%d %d\n", TAIL, current);
			// Cek apakah tidak ketemu;
			// Tidak ketemu
			if(current == TAIL){
				printf("Data not found!\n");
				return;
			}
			// Ketemu
			struct Student* after = current->next;
			struct Student* before = current->prev;
			current->next=current->prev=NULL;
			after->prev = before;
			before->next = after;
			free(current);
		}
	}
}

void Display(){
	struct Student* temp = HEAD;
	while(temp){
		printf("%s(%d) -> ", temp->nim, temp->ipk);
		temp = temp->next;
	}
	printf("\n");
}

int main(){
	Push_Mid(Create_Node("2600111", 3));
	Push_Mid(Create_Node("2600131", 3));
	Push_Mid(Create_Node("2600177", 3));
	Push_Mid(Create_Node("2600222", 3));
	Push_Mid(Create_Node("2600001", 3));
	Display(); getchar();
	
	Pop_Mid("2600177");
	Display(); getchar();
	Pop_Mid("2600131");
	Display(); getchar();
	Pop_Mid("2600111");
	Display(); getchar();
	Pop_Mid("2600001");
	Display(); getchar();
	Pop_Mid("2600002");
	Display();
	
	return 0;
}
