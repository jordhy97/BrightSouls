#include "stackqueue.c"

int main() {
	Stack S;
	ElmtStack Q;
	infotype X;
	int i,j,k;
	char T1[4];
	T1[1] = 'A';
	T1[2] = 'B';
	T1[3] = 'F';
	CreateEmptyS(&S);
	srand(time(NULL));
	for (i=1; i<=10; i++) {
		CreateEmptyQ(&Q);
		for (k=1; k<=4; k++) {
			j = rand() % 3 +1;
			X = T1[j];
			Add(&Q, X);
		}
		Push(&S,Q);
	}
	PrintStack(S);
	RandomStack(&S);
	printf("\n");
	PrintStack(S);
	return 0;
}
