#include <iostream>
#include "Stack.h"

using namespace std;

void push(char x, Stack*& myStk)
{
	Stack* e = new Stack;  
	e->data = x;            
	e->next = myStk;         
	myStk = e;				 
}

int isEmpty(Stack*& myStk) {
	if (myStk == NULL)
	{
		return 1;              
	}
	else {
		return 0;
	}
}

char pop(Stack*& myStk)   
{
	if (myStk == NULL)
	{
		return -1;              
	}
	else
	{
		Stack* e = myStk;        
		int x = myStk->data;    
		if (myStk)
			myStk = myStk->next;   
		delete e;
		return x;

	}
}

char top(Stack*& myStk)
{
	if (myStk == NULL)
	{
		cout << "Привет мир!" << endl;
		return 1;              
	}
	else {
		return myStk->data;
	}
}
