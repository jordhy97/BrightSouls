#include <stdio.h>
#include "enemy.h"
#include <time.h>
//#include "player.h"

typedef struct {
	Kata name;
	int hp;
	int str;
	int def;
	int exp;
	int level;
	//POINT position;
} Player;

#define Name(P) (P).name
#define HP(P) (P).hp
#define Strength(P) (P).str
#define Defense(P) (P).def
#define Exp(P) (P).exp
#define Level(P) (P).level
#define Position(P) (P).position

int main ()
{
	ElmtStack QMusuh,QPemain,QMusuhC,QPemainC;
	Enemy T1;
	char inplayer[1];
	char temp,player,enemy;
	Kata NPemain;
	int i,j,y,z,base,enemyhp;
	Player P;
	boolean aliveE,aliveP;

	Name(P).TabKata[1] = 'J';
	Name(P).TabKata[2] = 'e';
	Name(P).TabKata[3] = 's';
	Name(P).TabKata[4] = 's';
	Name(P).TabKata[5] = 'i';
	Name(P).TabKata[6] = 'c';
	Name(P).TabKata[7] = 'a';
	Name(P).Length = 7;
	HP(P) = 50;
	Strength(P) = 5;
	Defense(P) = 5;
	Exp(P) = 0;
	Level(P) = 1;
	
	/*BATTLE STARTS*/
	LoadFileEnemy(&T1,"bowtruckle.txt",'b'); /*parameter terakhir jika 'b' maka bos, jika 'e' maka enemy*/ 
	j = 0;
	if ((Level(P)>=1) && (Level(P)<=10))
	{
		base = 1;
	}
	else
	{
		base = 2;
	}
	enemyhp = e_hp(T1);
	aliveE = true;
	aliveP = true;
	while ((!IsEmptyS(e_attack(T1))) && (aliveE) && (aliveP))
	{
		j++;
		printf("Round %d\n",j);
		AttackEnemy(&T1,&QMusuh);
		
		srand(time(NULL));
		z = rand() % 4 + 1;
		y = rand() % 4 + 1;
		while (y == z) {
			z = rand() % 4 + 1;
			y = rand() % 4 + 1;
		} 
		PrintQueue(QMusuh,y,z);

		printf("\n");
		//kalo mau print aksi musuh tanpa di hide komen di bawah dihilangkan
		/*PrintQueueNR(QMusuh);
		printf("\n");*/
		CreateEmptyQ(&QPemain);
		while (NBElmtQ(QPemain)<4)
		{
			scanf("%s",inplayer);
			if ((inplayer[0] != 'E') && (inplayer[0] != 'A') && (inplayer[0] != 'B') && (inplayer[0] != 'F'))
			{
				do
				{
					PrintQueueNR(QPemain);
					printf("\n");
					scanf("%s",inplayer);
				}
				while ((inplayer[0] != 'E') && (inplayer[0] != 'A') && (inplayer[0] != 'B') && (inplayer[0] != 'F'));
			}
			if (inplayer[0] == 'E')
			{
				if (!IsEmptyQ(QPemain))
				{
					for (i = 1; i <= (NBElmtQ(QPemain)-1); i++)
					{
						Del(&QPemain,&temp);
						Add(&QPemain,temp);
					}
					Del(&QPemain,&temp);
					PrintQueueNR(QPemain);
					printf("\n");
				}
			}
			else if ((inplayer[0] == 'A') || (inplayer[0] == 'B') || (inplayer[0] == 'F'))
			{
				if (!IsFullQ(QPemain))
				{
					Add(&QPemain,inplayer[0]);
					PrintQueueNR(QPemain);
					printf("\n");
				}
			}
		}
		printf("\n");

		CreateEmptyQ(&QPemainC);
		CreateEmptyQ(&QMusuhC);
		QMusuhC = QMusuh;
		QPemainC = QPemain;
		/*dequeue*/
		i = 0;
		while ((!IsEmptyQ(QPemainC)) && (!IsEmptyQ(QMusuhC)) && (aliveE) && (aliveP))
		{
			i++;
			Del(&QPemainC,&player);
			Del(&QMusuhC,&enemy);
			PrintQueueBattleE(QMusuh,i,y,z);
			printf("\n");
			PrintQueueBattleP(QPemain,i);
			printf("\n");
			//printf("player %c enemy %c\n",player,enemy);
			if (((player == 'A') || (player == 'F')) && (player == enemy)) 
			{
				e_hp(T1) = e_hp(T1) - ((Damage(Strength(P),e_def(T1),base))/2);
				HP(P) = HP(P) - ((Damage(e_str(T1),Defense(P),base))/2);
				if (HP(P) < 0)
				{
					HP(P) = 0;
				}
				if (e_hp(T1) < 0)
				{
					e_hp(T1) = 0;
				}
				printf("Balanced!\n");
				PrintWord(e_name(T1)); printf("'s HP -%d! ",((Damage(Strength(P),e_def(T1),base))/2));
				PrintWord(Name(P)); printf("'s HP -%d!\n",((Damage(e_str(T1),Defense(P),base))/2));
				printf("\n");
			}
			else if ((player == 'B') && (player == enemy))
			{
				printf("Balanced!\n");
				printf("\n");
			}
			else if ((player == 'B') && (enemy == 'A'))
			{
					PrintWord(e_name(T1));
					printf(" Attacks!\n");
					PrintWord(e_name(T1));
					printf(" attacks ");
					PrintWord(Name(P)); //harusnya nama pemain
					printf(", but it's blocked!\n");
					printf("\n");
			}
			else if ((player == 'A') && (enemy == 'B'))
			{
					PrintWord(Name(P)); //harusnya nama pemain
					printf(" Attacks!\n");
					PrintWord(Name(P)); //harusnya nama pemain
					printf(" attacks ");
					PrintWord(e_name(T1)); 
					printf(", but it's blocked!\n");
					printf("\n");
			} 
			else if ((player == 'F') && (enemy == 'B'))
			{
					e_hp(T1) = e_hp(T1) - Damage(Strength(P),e_def(T1),base);
					if (e_hp(T1) < 0)
					{
						e_hp(T1) = 0;
					}
					PrintWord(Name(P)); //harusnya nama pemain
					printf(" flanks ");
					PrintWord(e_name(T1));
					printf("! ");
					PrintWord(e_name(T1));
					printf("'s HP -%d!\n",Damage(Strength(P),e_def(T1),base));
					printf("\n");
			}
			else if ((player == 'B') && (enemy == 'F'))
			{
					HP(P) = HP(P) - Damage(e_str(T1),Defense(P),base);
					if (HP(P) < 0)
					{
						HP(P) = 0;
					}
					PrintWord(e_name(T1));
					printf(" flanks ");
					PrintWord(Name(P)); //harusnya nama pemain
					printf("! ");
					PrintWord(Name(P)); //harusnya nama pemain
					printf("'s HP -%d!\n",Damage(e_str(T1),Defense(P),base));
					printf("\n");
			}
			else if ((player == 'A') && (enemy == 'F'))
			{
					e_hp(T1) = e_hp(T1) - Damage(Strength(P),e_def(T1),base);
					if (e_hp(T1) < 0)
					{
						e_hp(T1) = 0;
					}
					PrintWord(Name(P)); //harusnya nama pemain
					printf(" attacks ");
					PrintWord(e_name(T1));
					printf("! ");
					PrintWord(e_name(T1));
					printf("'s HP -%d!\n",Damage(Strength(P),e_def(T1),base));
					printf("\n");
			}
			else if ((player == 'F') && (enemy == 'A'))
			{
					HP(P) = HP(P) - Damage(e_str(T1),Defense(P),base);
					if (HP(P) < 0)
					{
						HP(P) = 0;
					}
					PrintWord(e_name(T1));
					printf(" attacks ");
					PrintWord(Name(P)); //harusnya nama pemain
					printf("! ");
					PrintWord(Name(P)); //harusnya nama pemain
					printf("'s HP -%d!\n",Damage(e_str(T1),Defense(P),base));
					printf("\n");
			}
			if (e_hp(T1) == 0)
			{
				aliveE = false;
			}
			if (HP(P) == 0)
			{
				aliveP = false;
			}
		}
	}
	if ((aliveP) && (aliveE))
	{
		if (e_hp(T1) >= (enemyhp/2))
		{
			printf("You got away!\n");
		}
		else
		{
			PrintWord(e_name(T1)); printf(" escaped!\n");
		}
		Exp(P) = Exp(P) + (((enemyhp - e_hp(T1))*e_exp(T1)) / enemyhp);
		printf("You earned %d experience points!\n",(((enemyhp - e_hp(T1))*e_exp(T1)) / enemyhp)); 
	}
	else if ((aliveP) && (!aliveE))
	{
		printf("You win!\n");
		Exp(P) = Exp(P) + e_exp(T1);
		printf("You earned %d experience points!\n",(((enemyhp - e_hp(T1))*e_exp(T1)) / enemyhp));
	}
	else
	{
		printf("You lose!\n");
	}
	return 0;
}
