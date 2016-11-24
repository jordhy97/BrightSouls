#include <unistd.h>

void saveplayer(Player P){
	char x;
	boolean ulang=true;

	while (ulang){
		printf("SAVE FILE\n\n");
		printf("Pilih Slot:\n\n");

		if( access( "player1.txt", F_OK ) != -1 ) {
	    // file exists
			printf("1. ");
			STARTKATA("player1.txt");
			int i=1;
			while(i<=CKata.Length){
				printf("%c", CKata.TabKata[i]);
				i++;
			}
			printf("\n\n");
		}
		else 
	    // file doesn't exist
	    	printf("1. Slot Kosong\n\n");

		if( access( "player2.txt", F_OK ) != -1 ) {
	    // file exists
			printf("2. ");
			STARTKATA("player2.txt");
			int i=1;
			while(i<=CKata.Length){
				printf("%c", CKata.TabKata[i]);
				i++;
			}
			printf("\n\n");
		}
	    else
	    // file doesn't exist
	    	printf("2. Slot Kosong\n\n");

		if( access( "player3.txt", F_OK ) != -1 ) {
	    // file exists
			printf("3. ");
			STARTKATA("player3.txt");
			int i=1;
			while(i<=CKata.Length){
				printf("%c", CKata.TabKata[i]);
				i++;
			}
			printf("\n\n");
		}
	    else 
	    // file doesn't exist
	    	printf("3. Slot Kosong\n\n");

	    scanf(" %c", &x);

	    if ((x!='1') && (x!='2') && (x!='3'))
	    	printf("Slot %c tidak tersedia\n\n", x);
	    else
	    	ulang=false;
    }
    
    FILE *fileplayer;
	
	if (x=='1')
   		fileplayer=fopen("player1.txt", "w");
    else if (x=='2')
   		fileplayer=fopen("player2.txt", "w");
   	else if (x=='3')
   		fileplayer=fopen("player3.txt", "w");
    
    int i;
    for(i = 1; i <= Name(P).Length; i++)
	    fprintf(fileplayer, "%c", Name(P).TabKata[i]);

    fprintf(fileplayer, " \n%d\n%d\n%d\n%d\n%d\n%d", HP(P), Max_HP(P), Strength(P), Defense(P), Exp(P), Level(P));

    fclose(fileplayer);
}

void loadplayer(Player *P){
	char x;
	boolean kosong1=false;
	boolean kosong2=false;
	boolean kosong3=false;
	boolean ulang=true;

	while (ulang){
		printf("LOAD FILE\n\n");
		printf("Pilih Slot:\n\n");

		if( access( "player1.txt", F_OK ) != -1 ) {
	    // file exists
			printf("1. ");
			STARTKATA("player1.txt");
			int i=1;
			while(i<=CKata.Length){
				printf("%c", CKata.TabKata[i]);
				i++;
			}
			printf("\n\n");
		}
	    else 
	    // file doesn't exist
	    {
	    	printf("1. Slot Kosong\n\n");
	    	kosong1=true;
	    }

	    if( access( "player2.txt", F_OK ) != -1 ){
	    // file exists
			printf("2. ");
			STARTKATA("player2.txt");
			int i=1;
			while(i<=CKata.Length){
				printf("%c", CKata.TabKata[i]);
				i++;
			}
			printf("\n\n");
		}
	    else
	    // file doesn't exist
	    {
	    	printf("2. Slot Kosong\n\n");
	    	kosong2=true;
	    }

	    if( access( "player3.txt", F_OK ) != -1 ) {
	    // file exists
			printf("3. ");
			STARTKATA("player3.txt");
			int i=1;
			while(i<=CKata.Length){
				printf("%c", CKata.TabKata[i]);
				i++;
			}
			printf("\n\n");
		}
	    else 
	    // file doesn't exist
	    {
	    	printf("3. Slot Kosong\n\n");
	    	kosong3=true;
	    }

	    char x;
	    scanf(" %c", &x);

	    if (x=='1' && kosong1)
	    	printf("Slot 1 kosong\n");

	    else if (x=='2' && kosong2)
	    	printf("Slot 2 kosong\n");

	    else if (x=='3' && kosong3)
	    	printf("Slot 3 kosong\n");

	    else if ((x!='1') && (x!='2') && (x!='3'))
	    	printf("Slot %c tidak tersedia\n\n", x);
	    else
	    	ulang=false;
    }
    
    FILE *fileplayer;
	
	if (x=='1'){
   		fileplayer=fopen("player1.txt", "r");
   		STARTKATA("player1.txt");
	}
    else if (x=='2'){
   		fileplayer=fopen("player2.txt", "r");
   		STARTKATA("player2.txt");
    }
   	else if (x=='3'){
   		fileplayer=fopen("player3.txt", "r");
   		STARTKATA("player3.txt");
   	}

   	Name(*P)=CKata;

   	char z[100];
   	fgets(z, 100, fileplayer);
   	fscanf(fileplayer, "%d\n%d\n%d\n%d\n%d\n%d", &HP(*P), &Max_HP(*P), &Strength(*P), &Defense(*P), &Exp(*P), &Level(*P));

    fclose(fileplayer);
}