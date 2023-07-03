#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
	Heap (BST tapi complete) 
	Heap ada max heap, min heap, dan min-max, heap
	Min heap -> parent lebih kecil dari child
	Max heap -> parent lebih besar dari child
	left child = parent*2
	right child = parent*2 + 1
	
	Extract = ambil dari root
*/

int heap[100];
int size = 0;

int parent(int pos){
	return pos/2;
}

void swap(int posA, int posB){
	int temp = heap[posA];
	heap[posA] = heap[posB];
	heap[posB] = temp;
	
}

void insert(int value){
	// Check size limit
	if(size==100){
		printf("Full");
		return;
	}
	// Insert to the last place
	size++;
	heap[size] = value;
//	printf("Size: %d - Value:%d\n", size, value);
	// Check heap rule -> parent
	int pos = size;
	while(heap[pos] > heap[parent(pos)] && pos > 1){ // Max heap, kalo min heap ganti tanda
		swap(pos, parent(pos));
		pos = parent(pos);
	}
	
}

void printHeap(){
	for(int i = 1; i <= size/2; i++){
		printf("Parent: %d, Left Child: %d, Right Child: %d\n", heap[i], heap[i*2], heap[i*2 + 1]);
	}
}

bool isLeaf(int pos){
	if(pos >= size/2 && pos <= size)
		return true;
	else
		return false;
}

int leftChild(int pos){
	return pos * 2;
}

int rightChild(int pos){
	return pos * 2 + 1;
}

void heapify(int pos){
	if(isLeaf(pos)) return;
	
	int leftChildValue = heap[leftChild(pos)];
	int rightChildValue = heap[rightChild(pos)];
	if(heap[pos] < leftChildValue || heap[pos] < rightChildValue){
		if(leftChildValue > rightChildValue){
			swap(pos, leftChild(pos));
			heapify(leftChild(pos));
		}else{
			swap(pos, rightChild(pos));
			heapify(rightChild(pos));
		}
	}
}

int extract(){
	int maxValue = heap[1];
	heap[1] = heap[size];
//	heap[size] = 0; // opsional karena data baru akan tertumpuk
	size --;
	heapify(1);
	return maxValue;
}

int main(){
	insert(7);
	insert(6);
	insert(11);
	insert(41);
	insert(3);
	insert(22);
	insert(1);
	
	printHeap();
	puts("");
	printf("Extracted Value: %d\n",extract());
	printHeap();
	return 0;
}
