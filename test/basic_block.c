#include<stdio.h>

int foo(int a) {
  return a * 2;
}

int bar(int a, int b) {
  return (a + foo(b) * 2);
}

int fez(int a, int b, int c) {
  return (a + bar(a, b) * 2 + c * 3);
}

int main()
{
	int a,b;
	a=10;
	b=5;
	return 0;
}


