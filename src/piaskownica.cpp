#include <stdio.h>

void pp( int * p ) {
	
	printf("%p\n", p );
}
void pp( int & p ) {
	
	printf("%p\n", &p );
}


int main () {
	
	int b = 6;
	int v = 90;
	
	int *pb = &b;
	int *pv = &v;
	
	printf("pb:	%p\n", pb );
	pp( pb );
	pp( &b );
	pp( b );
	
	printf("pv:	%p\n", pv );
	pp( pv );
	pp( &v );
	pp( v );
	
	return 0;
}
