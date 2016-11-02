#include <stdio.h>
#include "player.h"

void CreateNewPlayer (Player * P) {
    char c;
    int input, i = 0;
    printf("Enter Player Name: ");
    do {
        scanf("%c",&c);
        if (c != '\n') {
            Name(*P).word[i] = c;
            ++i;
        }
    } while (c != '\n' && i < 20);
    Name(*P).length = i;
    printf("Choose Player Speciality\n1. Balance\n2. HP\n3. Strength\n4. Defense\nChoice: ");
    scanf("%d",&input);
    if (input == 1) {
        HP(*P) = 50;
        Strength(*P) = 5;
        Defense(*P) = 5;
    }
    else if (input == 2) {
        HP(*P) = 70;
        Strength(*P) = 3;
        Defense(*P) = 3;
    }
    else if (input == 3) {
        HP(*P) = 40;
        Strength(*P) = 7;
        Defense(*P) = 3;
    }
    else if (input == 4) {
        HP(*P) = 40;
        Strength(*P) = 3;
        Defense(*P) = 7;
    }
    Exp(*P) = 0;
    Level(*P) = 1;
}

void LevelUp (Player * P) {
    int input;
    printf("Level Up, Congratulations!\n1. HP\n2. Strength\n3. Defense\nChoice: ");
    scanf("%d",&input);
    if (input == 1) HP(*P) += 10;
    else if (input == 2) ++Strength(*P);
    else if (input == 3) ++Defense(*P);
    ++Level(*P);
    //Exp(*P) -= 100;
}

int main() {
    int i;
    Player P;
    CreateNewPlayer(&P);
    printf("\n");
    printf("Player Name: ");
    for (i = 0; i < Name(P).length; ++i) printf("%c",Name(P).word[i]);
    printf("\n");
    printf("HP: %d\nStr: %d\nDef: %d\nExp: %d\nLevel: %d\n",HP(P),Strength(P),Defense(P),Exp(P),Level(P));
    printf("\n");
    LevelUp(&P);
    printf("\n");
    printf("Player Name: ");
    for (i = 0; i < Name(P).length; ++i) printf("%c",Name(P).word[i]);
    printf("\n");
    printf("HP: %d\nStr: %d\nDef: %d\nExp: %d\nLevel: %d\n",HP(P),Strength(P),Defense(P),Exp(P),Level(P));
    printf("\n");
    return 0;
}
