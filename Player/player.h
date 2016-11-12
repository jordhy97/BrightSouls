#ifndef player_H
#define player_H

#include "boolean.h"
#include "../Point/point.h"
#include "../MesinKarKata/mesinkata.h"

typedef struct {
    char word[100];
    int length;
} Word;

typedef struct {
	Word name;
	int hp;
	int str;
	int def;
	int exp;
	int level;
	POINT position;
} Player;

#define Name(P) (P).name
#define HP(P) (P).hp
#define Strength(P) (P).str
#define Defense(P) (P).def
#define Exp(P) (P).exp
#define Level(P) (P).level
#define Position(P) (P).position

void GetPlayerData ();
/*Mengambil data player dari file eksternal*/

void CreatePlayer (Player * P);
/*Membentuk player baru dengan nama yang ditentukan user*/

void LevelUp (Player * P);
/* Menaikan level player bila sudah mencapai Exp tertentu */

#endif
