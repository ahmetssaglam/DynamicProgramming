/* 
@file
BLM3021 2020-2021 GUZ ODEV-3 / Soru-1
Bu programda dinamik programlama y�ntemi kullan�larak iki tak�m aras�nda ge�en ma� serisini, tak�mlardan biri olan A tak�m�n�n kazanma olas�l��� hesaplanm��t�r.
Ma�larda bereberlik s�z konusu de�ildir.

@author
�sim: Ahmet Said SA�LAM
��renci No: 17011501
Tarih: 19.12.2020
E-Mail: l1117501@std.yildiz.edu.tr
Compiler: TDM-GCC 4.9.2 64 bit-Release
IDE: DEV-C++ (version 5.11)
��letim Sistemi: Windows 10 Pro 64 bit
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//icerisine ald�g� double tipindeki matrisi yazd�r�r
void printDoubleMatrix(double **matrix, int row_count, int column_count) {
	int i,j;
	for (i=0; i < row_count; i++) {
		for(j=0; j < column_count; j++) {
			printf("%.3f\t", matrix[i][j]);
		}
		printf("\n");
	}		
}

//dinamik programlama y�ntemiyle A tak�m�n�n seriyi kazanma y�ntemini hesaplayan fonksiyon
double kazanmaOrani(double prob_a, int total_matches) {
	double prob_b = 1 - prob_a;	//B tak�m�n�n 1 mac� kaz�nma olas�l�g�
	int i; //A tak�m�n�n kazand�g� mac say�s� // dongu degiskeni
	int j; //B tak�m�n�n kazand�g� mac say�s�
	int enough_win = (total_matches / 2) + 1;	//seriyi kazanmak icin kazan�lmas� gereken mac say�s�
	double ret_value;
	
	double **Matches =  (double**) malloc((enough_win + 1) * sizeof(double*));	//matris tanimlanir ve matrisin satirlari icin yer acilir
	//matris,n sutunlar� icin yer acilir
	for(i = 0; i <= enough_win; i++) {
		Matches[i] = (double*) malloc((enough_win + 1) * sizeof(double));
	}
	
	//matris 1. sat�r ve s�tundan itibaren gezilerek de�erler hesaplan�r
	for (i = 1; i <= enough_win; i++) {
		Matches[i][0] = 0;	//matrisin ilk sutunu ilklendirilir
		for(j = 1; j <= enough_win; j++) {
			Matches[0][j] = 1;	//matrisin ilk sat�r� ilklendirilir
			Matches[i][j] = (prob_a * Matches[i-1][j]) + (prob_b * Matches[i][j-1]);	//matrisin ilgili g�z� hesaplan�r
		}
	}
	
	printf("\nCozum Matrisi : \n\n");
	printDoubleMatrix(Matches, (enough_win + 1), (enough_win + 1));		//matris ekrana yazdirilir
	
	ret_value = Matches[enough_win][enough_win];	//donus degeri degiskende saklanir
	
	//dinamik olarak acilan yer free edilir
	for(i = 0; i <= enough_win; i++) {
		free(Matches[i]);
	}
	free(Matches);
	
	return ret_value;	//matrisin son g�z� yani sonu� d�nd�r�l�r
}



int main() {
	double prob_a;	//A tak�m�n�n bir maci kazanma olasiligi
	int total_matches;	//serideki toplam mac sayisi
	int cont = 1;
	//kullanici istedikce donen while dongusu
	while(cont) {
		printf("Serideki toplam mac sayisini giriniz : ");
		scanf("%d",&total_matches);
		printf("\nA takiminin kazanma ihtimalini giriniz : ");
		scanf("%lf",&prob_a);
		printf("\n\nA takiminin seriyi kazanma olasiligi : %.3lf\n\n",kazanmaOrani(prob_a,total_matches));
		printf("Yeni hesaplama yapmak icin 1'e, cikmak icin 0'a basiniz...\n");
		scanf("%d",&cont);
		printf("\n");
	}
	return 0;
}



