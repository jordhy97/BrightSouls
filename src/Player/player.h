#ifndef player_H
#define player_H

#include "boolean.h"
#include "../Point/point.h"
#include "../MesinKarKata/mesinkata.h"
#include <ncurses.h>

typedef struct {
	Kata name;
	int hp;
	int str;
	int def;
	int exp;
	int level;
	POINT position;
	BinTree skill;
} Player;

#define Name(P) (P).name
#define HP(P) (P).hp
#define Strength(P) (P).str
#define Defense(P) (P).def
#define Exp(P) (P).exp
#define Level(P) (P).level
#define Position(P) (P).position
#define Skill(P) (P).skill

void GetPlayerData ();
/*Mengambil data player dari file eksternal*/

void CreatePlayer (Player *P, Kata nama);
/* I.S. P sembarang, nama terdefinisi */
/* F.S. Membentuk player baru dengan (P).name = nama dengan status yang sudah ditentukan berdasarkan pilihan user*/ 

void wCreatePlayer(WINDOW *menu, Player *P, Kata nama);
/* I.S. P sembarang, menu dan nama terdefinisi */
/* F.S. Membentuk player baru dengan (P).name = nama dengan status yang sudah ditentukan berdasarkan pilihan user*/ 

void print_choice(WINDOW *menu_win, int pilihan);
/* I.S. menu_win dan pilihan[1..5] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */

void LevelUp (Player * P);
/* Menaikan level player bila sudah mencapai Exp tertentu */

void AddSkill (Player * P);

#endif
