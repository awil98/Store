#include <stdio.h>
#include <stdlib.h>

void push(int num);
int pop();
int peek();

int main(){
	int numStack[100];

	int *stackPointer = numStack[100];

	return 0;
}

void push(int num){
	
	stackPointer--;
	numStack[stackPointer] = num;
}

int pop(){

	int returnValue = *
}
