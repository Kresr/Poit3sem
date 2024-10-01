#include <iostream>
using namespace std;

float defaultparm(int a, int b, int c, int d, int e, int x = 10, int y = 20) {
	return (a + b + c + d + e + x + y) / 7;
}

int main() {
	int parms5 = defaultparm(2, 5, 7, 8, 11);
	int parms7 = defaultparm(2, 5, 7, 8, 11, 37, 55);
	cout << parms5 << endl;
	cout << parms7 << endl;
} 
