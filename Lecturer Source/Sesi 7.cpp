#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Stack = numpuk di head, pop harus di head
	Queue = numpuk di tail, pop harus di tail
	Fungsi untuk mengerjakan evaluasi Prefix, Infix, dan Postfix
		Postfix dievaluasi manual dengan stack (head)
			push pada operand hingga bertemu operator
				operand kiri - operator - operand kanan
		Prefix dievaluasi manual dengan queue (tail) / stack dari belakang
			push pada operand hingga bertemu operator
				operand kiri - operator - operand kanan
			
*/

// Double linked list
// push_sort() / search = priority queue
struct Node{
	int age;
	char name[100];
	struct Node* next;
	struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail =NULL;

struct Node* Create_Node(char* name, int age){
	struct Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->age=age;
	strcpy(new_node->name, name);
	new_node->next=NULL;
	new_node->prev=NULL;
	return new_node;
}

void Push_Head(char* name, int age){
	struct Node* new_node = Create_Node(name, age);
	if (!head){
		head = tail = new_node;
	}else{
		head->prev = new_node;
		new_node->next = head;
		head = new_node;
	}
}

void Push_Tail(char* name, int age){
	struct Node* new_node = Create_Node(name, age);
	if (!head){
		head = tail = new_node;
	}else{
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
}

void Push_Sort(char* name, int age){
	struct Node* new_node = Create_Node(name, age);
	if (!head){
		head = tail = new_node;
	}else{
		if(new_node->age < head->age){
			Push_Head(name, age);
		}else if(new_node->age >= tail->age){ // Queue priority
			Push_Tail(name, age);
		}else{
			struct Node* current = head;
//			while(current->next != tail){
//				if(current->next->age > new_node->age){
//					break;
//				}
//				current=current->next;
//			}
			while(current->next->age <= age){
				current = current->next;
			}
			struct Node* temp = current->next;
			// temp = right dari new_node
			// current = left dari new_node
			// current - new_node - temp
			new_node->next = temp;
			new_node->prev = current;
			current->next = new_node;
			temp->prev = new_node;
		}
		
	}
}

void view(){
	struct Node* temp = head;
	while(temp){
		printf("%s(%d) -> ", temp->name, temp->age);
		temp= temp->next;
	}
}

void Pop_Head(){
	if(!head){
		return;
	}else if(head==tail){
		free(head);
		head = tail = NULL;
	}else{
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
}

void Pop_Tail(){
	if(!head){
		return;
	}else if(head==tail){
		free(head);
		head = tail = NULL;
	}else{
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL;
	}
}

void Pop_Search(char* name){\
	if(!head){
		return;
	}else if(strcmp(name, head->name) == 0){
		Pop_Head();
	}else if(strcmp(name, tail->name) == 0){
		Pop_Tail();
	}else{
		struct Node* target = head;
		while(target){
			if(strcmp(target->name, name)==0){
				struct Node* left = target->prev;
				struct Node* right = target->next;
				left->next=right;
				right->prev=left;
				free(target);
				return;
			}
			target=target->next;
		}
		printf("Data not found!\n");
	}
}

void Pop_All(){
	while(head){
		Pop_Head();
	}
}

int main(){
	Push_Sort("Andi", 23);
	Push_Sort("Budi", 27);
	Push_Sort("Caca", 21);
	Push_Sort("Andi 2", 23);
	Push_Sort("Erna", 39);
	Push_Sort("Budi 2", 27);
	Push_Sort("Andi 3", 23);
	view(); getchar();
	
	Pop_Search("Budi");
	view(); getchar();
	
	Pop_Search("Ihya");
	view(); getchar();
	
	Pop_All();
	view();
	return 0;
}
