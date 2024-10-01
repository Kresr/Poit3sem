#include <iostream>
#include <Windows.h>

using namespace std;

int sum(int x, int y)
{
	return x + y;
}

int(*f) (int, int);

int main()
{
	setlocale(LC_ALL, "Russian");     

	int n = 6;                        // 6
	int X = 9 + n;                    // 15
	int Y = 10 + n;                   // 16
	int Z = 11 + n;                   // 17
	float S = 1.0 + n;                // 7.0000000

	bool t4_1 = false;                // 00
	bool t4_2 = true;                 // 01

	char t5 = 'p';                    // ASCII  70

	char t6 = 'р';                    // ASCII f0

	wchar_t t7 = L'e';                // UTF-16 65 00

	wchar_t t8 = L'е';                // UTF-16 35 04

	short t9_1 = X;                   // 0000 1111 = 0x0F
	short t9_2 = -X;                  // 1000 1111 (п/к) = 1111 0000 (о/к) = 1111 0001 (д/к) = 0xFFFFFFF0

	short t10_1 = 0xFFFF8000;         // −32768 = 0111 1111 1111 1111 (п/к) = 1000 0000 0000 0000 (о/к) = 1000 0000 0000 0001 (д/к)
	short t10_2 = 0x00007FFF;         // 0111 1111 1111 1111 = 32767

	unsigned short t11_1 = 0x0000;    // 0
	unsigned short t11_2 = 0xFFFF;    // 1111 1111 1111 1111 = 65535

	int t12_1 = Y;                    // 0001 0000 = 0x10
	int t12_2 = -Y;                   // 1001 0000 (п/к) = 1110 1111 (о/к) = 1111 0000 (д/к) = 0x10

	int t13_1 = 0xFFFFFFFF80000000;   // -2147483648 = 0111 1111 1111 1111 1111 1111 1111 1111 (п/к) = 1000 0000 0000 0000 0000 0000 0000 0000 (о/к) = 1000 0000 0000 0000 0000 0000 0000 0001 (д/к)
	int t13_2 = 0x000000007FFFFFFF;   // 2147483647 = 0111 1111 1111 1111 1111 1111 1111 1111

	unsigned int t14_1 = 0x00000000;  // 0
	unsigned int t14_2 = 0xFFFFFFFF;  // 4294967295 = 1111 1111 1111 1111 1111 1111 1111 1111

	long t15_1 = Z;                   // 0001 0001 = 0x11
	long t15_2 = -Z;                  // 1001 0001 (п/к) = 1110 1110 (о/к) = 1110 1111 (д/к) = 0x0F

	long t16_1 = 0xFFFFFFFF80000000;  // -2147483648 = 0111 1111 1111 1111 1111 1111 1111 1111 (п/к) = 1000 0000 0000 0000 0000 0000 0000 0000 (о/к) = 1000 0000 0000 0000 0000 0000 0000 0001 (д/к)
	long t16_2 = 0x000000007FFFFFFF;  // 2147483647 = 0111 1111 1111 1111 1111 1111 1111 1111

	unsigned long t17_1 = 0x00000000; // 0
	unsigned long t17_2 = 0xFFFFFFFF; // 4294967295 = 1111 1111 1111 1111 1111 1111 1111 1111

	float t18_1 = S;                  // 0x7 = 0.1000111.000
	float t18_2 = -S;                 // -0x7 = 1.1000111.000

	float t19_1 = t18_1 / 0;          // 0x7F800000
	float t19_2 = t18_2 / 0;          // 0xFF800000
	float t19_3 = sqrt(-2.0f);        // 0xFFC00000

	//Переменные
	char t20_1 = 'А';                 //0x00C0
	wchar_t t20_2 = L'А';             //0x0410
	short t20_3 = 26;                 //0x001A
	int t20_4 = 260;                  //0x0104
	float t20_5 = 26.5;               //0x414D0000
	double t20_6 = 26.0005;           //0x41D40000

	//Указатели
	char* p20_1 = &t20_1;             //0x0037FCAF
	wchar_t* p20_2 = &t20_2;          //0x0037FCA0
	short* p20_3 = &t20_3;            //0x0037FC94
	int* p20_4 = &t20_4;              //0x0037FC88
	float* p20_5 = &t20_5;            //0x0037FC7C
	double* p20_6 = &t20_6;           //0x0037FC6C

	//Увеличение на 3
	char* p20_1_1 = p20_1 + 3;        //0x0037FCB2 = 0x0037FCAF + sizeof(char)*3 // +3
	wchar_t* p20_2_2 = p20_2 + 3;     //0x0037FCA6 = 0x0037FCA0 + sizeof(wchar_t)*3 // +6
	short* p20_3_3 = p20_3 + 3;       //0x0037FC9A = 0x0037FC94 + sizeof(short)*3 // +6
	int* p20_4_4 = p20_4 + 3;         //0x0037FC94 = 0x0037FC88 + sizeof(int)*3 // +12
	float* p20_5_5 = p20_5 + 3;       //0x0037FC88 = 0x0037FC7C + sizeof(float)*3 // +12
	double* p20_6_6 = p20_6 + 3;      //0x0037FC84 = 0x0037FC6C + sizeof(long)*3 // +24

	f = sum;
	int t21 = f(1, 5);                //0x0006
	cout << t21;
	return 0;
}
