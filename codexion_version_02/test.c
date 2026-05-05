#include <stdio.h>

int main()
{
	int i= 0 ;
	int *s = &i;
	*s = 1;
	printf("%d %d", i, *s);
}