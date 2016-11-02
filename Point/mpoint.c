#include <stdio.h>
#include "point.h"

int main(){
	int X, Y;
	POINT P;
	scanf("%d %d", &X, &Y);
	P=MakePOINT(X, Y);
	P=NextX(P);
	P=NextY(P);
	P=PlusDelta(P, 3, 5);
	Geser(&P, 2, 1);
	printf("%d %d\n", Absis(P), Ordinat(P));
	GeserKeSbX(&P);
	GeserKeSbY(&P);
	printf("%d %d\n", Absis(P), Ordinat(P));
	return 0;
}