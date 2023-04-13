#include<stdio.h>

int main(){
	int n = 10; // variabel biasa
	int *ptr_n = &n; // pointer dari n
	int **ptr_ptr_n = &ptr_n; //pointer dari pointernya n
//	Cara kerja pointer adalah mencari refrensi dari variabel sebelumnya
	
	printf("%p\n", &n);		// output address n
	printf("%p\n", ptr_n);	// output address n melalui pointer
	printf("%d\n", *(ptr_n)); // output dari n melalui pointer
	printf("%p\n", &ptr_n); // alamat pointer
	printf("%d\n", *(*ptr_ptr_n)); // output nilai n dari pointer, pointernya n
	// Refrencing 2 kali sebaiknya di kurung karena bisa error di struct
	printf("\n");
	
//	{
//		int z = 5;
//		int n= 7;
//		printf("%d\n", n); //Bisa di print karena scopenya beda
//	}
	
//	Informasi dari line 4
//	1) Data type (void, int, char, float, double)
//	2) Identifier
//	3) Value
//	4) Scope
//	5) Address
	
//	Array adalah pointer
	
	int data[10];
	data[0]=15;
	data[1]=17;
	
	printf("%d\n", *data);		//data[0] => data + 0
	printf("%d\n", *(data+1));	//data[1] => data + 1
	
	
	return 0;
}
