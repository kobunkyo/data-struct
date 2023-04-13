#include <stdio.h>
#include <string.h>

/*
	Product (100)
	-name
	-price
	-stock
*/	

struct Date{
	int day;
	int month;
	int year;
};

struct Product{ // Abstract Data Type
	char name[100];
	int price;
	int stock;
	struct Date expired; // Nested Struct
};

/*
struct X{
	char h;
	char g;
	int a;
	int b;
	char c;
	char d;
	char e;
	char f;
};
	Prinsip kerja struct X
		int > 4
		char > 1
		Karena int adalah size terbesar sehingga saat 
		deklarasi char akan menghasilkan blok yang 
		berjumlah 4. Pada saat yang sama jika char 
		dideklarasikan di awal akan menghasilkan 4 Byte
		Urutan pada struct akan berpengaruh.
		_ _ _ _	   _ _ _ _   _ _ _ _   _ _ _ _
		h g 	      a         b      c d e f
printf("Size of X = %d\n", sizeof(X));
*/

struct Node{
	int value; // Data yang disimpan
	Node *next;// Address node yang lain
};

int main(){

	struct Product prodDat[100]; // Array of Struct
	strcpy(prodDat[0].name, "Ayam Bakar");
	prodDat[0].price = 20000;
	prodDat[0].stock = 100;
	
	return 0;
}
