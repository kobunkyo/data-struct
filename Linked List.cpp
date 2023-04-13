#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Linked list
// Node 1 terhubungan ke node 2 melalui linked list
// LIFO = Last In First Out (Konsep stack dan linked list (pop tail dan push tail) dgn head di bawah dan tail di atas
// FIFO = First In First Out (Konsep Queue)
struct Mahasiswa{
	int age;
	char name[50];
	struct Mahasiswa* next;
};

struct Mahasiswa* HEAD = NULL;
struct Mahasiswa* TAIL = NULL;

struct Mahasiswa* Create(char* name, int age){
	struct Mahasiswa* new_mahasiswa = (struct Mahasiswa*)malloc(sizeof(Mahasiswa));
	new_mahasiswa->age=age;
	strcpy(new_mahasiswa->name, name);
	new_mahasiswa->next = NULL;
	return new_mahasiswa;
}

struct Mahasiswa* PushHead(char* name, int age){
	struct Mahasiswa* new_mahasiswa = Create(name, age);
	if(!HEAD){
		HEAD = TAIL = new_mahasiswa;
	}else{
		new_mahasiswa->next = HEAD;
		HEAD = new_mahasiswa;
	}
}

struct Mahasiswa* PushTail(char* name, int age){
	struct Mahasiswa* new_mahasiswa = Create(name, age);
	if(!HEAD){
		HEAD = TAIL = new_mahasiswa;
	}else{
		TAIL->next = new_mahasiswa;
		TAIL = new_mahasiswa;
	}
}

struct Mahasiswa* PushMid(char* name, int age){
	struct Mahasiswa* new_mahasiswa = Create(name, age);
	if(!HEAD){
		HEAD = TAIL = new_mahasiswa;
	}else{
		if(HEAD->age > age){ // bandingin umur di age sama data baru
			PushHead(name, age);
		}else if(TAIL->age < age){
			PushTail(name, age);
		}else{
			struct Mahasiswa* current = HEAD;
			while(current->next != TAIL && current->next->age < age){
				current = current->next;
			}
			new_mahasiswa->next = current->next;
			current->next = new_mahasiswa;
		}
	}
}

void PopHead(){
	if(!HEAD){
		printf("Linked List is empty!");
	}else if(HEAD == TAIL){
		free(HEAD);
		HEAD = TAIL = NULL;
	}else{
		struct Mahasiswa* temp = HEAD;
		HEAD = temp->next;
		free(temp);
	}
	
}

void PopTail(){
	if(!TAIL){
		printf("Linked List is empty!");
	}else if(HEAD == TAIL){
		free(HEAD);
		HEAD = TAIL = NULL;
	}else{
		struct Mahasiswa* current = HEAD;
		while(current->next != TAIL){
			current = current->next;
		}
		free(TAIL);
		TAIL = current;
		TAIL->next = NULL;
	}
}

void PopMid(int age){
	if(!HEAD){
		printf("Linked List is empty!");
	}else if(HEAD == TAIL){
		free(HEAD);
		HEAD = TAIL = NULL;
	}else{
		if(HEAD->age == age){
			PopHead();
		}else if(TAIL->age == age){
			PopTail();
		}else{
			struct Mahasiswa* current = HEAD;
			while(current->next != TAIL && current->next->age != age){
				current = current->next; // berhenti sebelum node yang akan dihapus
			}
			struct Mahasiswa* to_delete = current->next;
			current->next = to_delete->next;
			free(to_delete);
		}
		
	}
}

void View(){
	struct Mahasiswa* current = HEAD;
	while(current!=NULL){
		printf("[%-3s | %-3d] -> ", current->name, current->age);
		current = current->next;
	}
}

int main(){
	PushMid("Jacky", 17);
	View(); getchar();
	PushMid("Robert", 12);
	View(); getchar();
	PushMid("Tintin", 19);
	View(); getchar();
	PushMid("Bibi", 15);
	View(); getchar();
	PushMid("Lili", 13);
	View(); getchar();
	PushMid("Jojo", 14);
	View(); getchar();
	PopHead();
	View(); getchar();
	PopTail();
	View(); getchar();
	PopMid(15);
	View(); getchar();
	
}
