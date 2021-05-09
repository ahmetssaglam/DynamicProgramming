/* 
@file
BLM3021 2020-2021 GUZ ODEV-3 / Soru-1
Bu programda dinamik programlama yöntemi kullanýlarak iki takým arasýnda geçen maç serisini, takýmlardan biri olan A takýmýnýn kazanma olasýlýðý hesaplanmýþtýr.
Maçlarda bereberlik söz konusu deðildir.

@author
Ýsim: Ahmet Said SAÐLAM
Öðrenci No: 17011501
Tarih: 19.12.2020
E-Mail: l1117501@std.yildiz.edu.tr
Compiler: TDM-GCC 4.9.2 64 bit-Release
IDE: DEV-C++ (version 5.11)
Ýþletim Sistemi: Windows 10 Pro 64 bit
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//icerisine aldýgý double tipindeki matrisi yazdýrýr
void printDoubleMatrix(double **matrix, int row_count, int column_count) {
	int i,j;
	for (i=0; i < row_count; i++) {
		for(j=0; j < column_count; j++) {
			printf("%.3f\t", matrix[i][j]);
		}
		printf("\n");
	}		
}

//dinamik programlama yöntemiyle A takýmýnýn seriyi kazanma yöntemini hesaplayan fonksiyon
double kazanmaOrani(double prob_a, int total_matches) {
	double prob_b = 1 - prob_a;	//B takýmýnýn 1 macý kazýnma olasýlýgý
	int i; //A takýmýnýn kazandýgý mac sayýsý // dongu degiskeni
	int j; //B takýmýnýn kazandýgý mac sayýsý
	int enough_win = (total_matches / 2) + 1;	//seriyi kazanmak icin kazanýlmasý gereken mac sayýsý
	double ret_value;
	
	double **Matches =  (double**) malloc((enough_win + 1) * sizeof(double*));	//matris tanimlanir ve matrisin satirlari icin yer acilir
	//matris,n sutunlarý icin yer acilir
	for(i = 0; i <= enough_win; i++) {
		Matches[i] = (double*) malloc((enough_win + 1) * sizeof(double));
	}
	
	//matris 1. satýr ve sütundan itibaren gezilerek deðerler hesaplanýr
	for (i = 1; i <= enough_win; i++) {
		Matches[i][0] = 0;	//matrisin ilk sutunu ilklendirilir
		for(j = 1; j <= enough_win; j++) {
			Matches[0][j] = 1;	//matrisin ilk satýrý ilklendirilir
			Matches[i][j] = (prob_a * Matches[i-1][j]) + (prob_b * Matches[i][j-1]);	//matrisin ilgili gözü hesaplanýr
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
	
	return ret_value;	//matrisin son gözü yani sonuç döndürülür
}



int main() {
	double prob_a;	//A takýmýnýn bir maci kazanma olasiligi
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



