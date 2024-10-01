#include <iostream>
#define TED 10
int main(void)
{
#ifdef TED
	printf("Привет, Тэд\n");
#else
	printf("Привет, кто-нибудь\n");
#endif
#ifndef RALPH
	printf("А RALPH не определен, т.к. Ральфу не повезло.\n");
#endif
	return 0;
}
