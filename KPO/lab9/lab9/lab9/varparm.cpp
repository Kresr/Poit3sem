#include "varparm.h"
#include <float.h>

namespace Varparm {
	//Вычислить произведение значений всех параметров
	int ivarparm(int n, ...)
	{
		if (n == 0)// Если не передано целых чисел
		{
			return 0;
		}
		int mul = 1;
		int* p = &n + 1;
		int i = 0;
		while (i < n) {
			mul *= *(p + i);
			i++;
		}
		return mul;


	}
	//Найти максимальное значение параметров
	int svarparm(short n, ...) {
		int max = 0;

		int* p = (int*)(&n);
		for (int i = 1; i < n + 1; i++)
		{
			if (*(p + i) > max)
			{
				max = *(p + i);
			}
		}
		return max;
	}
	//Вычислить сумму значений всех параметров
	double fvarparm(float n, ...) {
		double sum = (double)n;
		double* ptr = (double*)(&n + 1);
		if (n == FLT_MAX) return 0;// Если 'n' равно максимальному значению для float, вернуть 0
		for (int i = 0; ptr[i] != (double)FLT_MAX; i++) {
			sum += ptr[i];
		}
		return sum;
	}
	//Вычислить сумму значений всех параметров
	double dvarparm(double n, ...) {
		double sum = n;
		double* ptr = &n + 1;
		if (n == DBL_MAX) return 0;
		for (int i = 0; ptr[i] != DBL_MAX; i++) {
			sum += ptr[i];
		}
		return sum;
	}
}