#pragma once
#include <iostream>
#include <string>

struct Stack
{
	char data;
	Stack* next;
};

void push(char x, Stack*& myStk);
int isEmpty(Stack*& myStk);
char pop(Stack*& myStk);
char top(Stack*& myStk);
