#include <iostream>
#pragma comment(lib,"..\\Debug\\SE_asm01a.lib")
extern "C"
{
    int __stdcall getmin(int*, int);
    int __stdcall getmax(int*, int);
}

int main()
{
    int arr[10] = { 56, 32, 82, -2, 10, 98, 17, -11, 7, 4 };
    int min = 0, max = 0, sum = 0;
    min = getmin(arr, 10);
    max = getmax(arr, 10);
    sum = min + max;
    std::cout << "getmax + getmin = " << sum << std::endl;
}