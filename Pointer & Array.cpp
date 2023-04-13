#include <stdio.h>
#include <string.h>

// Declare struct
struct Mahasiswa{
	int ipk;
	char nim[10];
	char name[20];
};

int main(){
	
	// Pointer
	// Pointer => data type => nyimpen alamat variabel lain
	// Declare variabel integer
	int b=7;
	printf("Nilai b\t: %d\n", b);
	printf("Alamat b: %d\n", &b);
	
	// Declare pointer
	int *a;
	printf("Alamat a: %d\n", &a);
	
	// Assign alamat b ke pointer a
	a = &b;
	printf("Nilai a\t: %d\n", a);
	
	// Akses value dari alamat di pointer
	*a = 9;
	printf("Nilai dari alamat di a\t: %d\n", *a);
	printf("Nilai b (Setelah diubah): %d\n\n", b);
	
	// Array
	// Array of integer tidak ada NULL operator
	int arr[5] = {1,2,3,4,5};
	for(int i=0; i < (sizeof(arr)/sizeof(int)); i++){
		printf("  %d(%d)\n", arr[i], &arr[i]);
	}
	
	// Array of char ada NULL operator = \0 (dalam char akan blank dan angka akan 0)
	char str[5]="abcd";
	printf("%s\n", str);
	for(int i=0; i< (sizeof(str)/sizeof(char)); i++){
		if (str[i]=='\0') printf("  %d(%d)\n", str[i], &str[i]);
		else printf("  %c(%d)\n", str[i], &str[i]);
	}
	printf("\n");
	
	// Struct
	// Struc buat tipe data baru
	struct Mahasiswa m1;
	
	//ext .cpp bisa langsung 'Mahasiswa m1' tanpa struct
	Mahasiswa m2;
	
	strcpy(m1.nim, "123"); // String input to struct m1
	strcpy(m1.name, "Anthony"); // String input to struct m1
	m1.ipk = 4; // Integer input to struct m1
	
	printf("Name of m1: %s\n", m1.name);
	printf("NIM of m1 : %s\n", m1.nim);
	printf("IPK of m1 : %d\n", m1.ipk);
	
	//Array of struct
	struct Mahasiswa kelas[30];
	kelas[0].ipk = 3;
	printf("IPK of kelas[0]: %d\n", kelas[0].ipk);
	
	
	return 0;
}
