#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int minHeap[1000];

//Assume ROOT will be at index 0
int count = 0;

int get_parent_index(int index){
	return (index-1)/2;
}

int get_left_child_index(int index){
	return (index*2) + 1;
}

int get_right_child_index(int index){
	return (index*2) + 2;
}

int get_min(){
	return minHeap[0];
}

void swap(int a, int b){
	int temp = minHeap[a];
	minHeap[a] = minHeap[b];
	minHeap[b] = temp;
}

void up_heap(int index){
	if( index == 0 ) return;
	
	int parentIndex = get_parent_index(index);
	if( minHeap[parentIndex] <= minHeap[index] ) return;
	
	swap(parentIndex, index);
	up_heap(parentIndex);		
}

void down_heap(int index){
	if( index >= count ) return;
	
	int indexOfSmallest = index;
	int leftIndex = get_left_child_index(index);
	int rightIndex = get_right_child_index(index);
	
	if( leftIndex < count && 
			minHeap[leftIndex] < minHeap[indexOfSmallest] ){
		indexOfSmallest = leftIndex;			
	}
	
	if( rightIndex < count &&
			minHeap[rightIndex] < minHeap[indexOfSmallest] ){
		indexOfSmallest = rightIndex;			
	}
	
	if( indexOfSmallest == index ) return;
	
	swap(index, indexOfSmallest);
	down_heap(indexOfSmallest);
}

void push(int value){
	minHeap[count] = value;
	count++;
	up_heap(count-1);
}

int pop(){
	int removed = minHeap[0];
	swap(0, count-1);
	count--;
	down_heap(0);
	return removed;	
}

int main(){
	
	srand(time(NULL));
	
	for(int i=0 ; i<10; i++){
		int n = rand()%100+1;
		push(n);
		printf("%d is added!\n", n);
	}
	
	printf("\n");

	for(int i=0 ; i<10 ; i++){
		printf("%d is removed!\n", pop());
	}
	
	return 0;
}
