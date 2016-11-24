#ifndef player_H
#define player_H

#include "../Shared/boolean.h"
#include "../Point/point.h"
#include "../MesinKarKata/mesinkata.h"
//#include "../BinTree/bintree.h"
#include <ncurses.h>

typedef struct {
	Kata name;
	int max_hp;
	int hp;
	int str;
	int def;
	int exp;
	int level;
	POINT position;
	int CArea;
//	BinTree skill;
} Player;

#define Name(P) (P).name
#define Max_HP(P) (P).max_hp
#define HP(P) (P).hp
#define Strength(P) (P).str
#define Defense(P) (P).def
#define Exp(P) (P).exp
#define Level(P) (P).level
#define Position(P) (P).position
#define CArea(P) (P).CArea
// #define Skill(P) (P).skill

void SavePlayer(Player P, char *namafile);
/* I.S. P terdefinisi, namafile terdefinisi */
/* F.S. data P tersimpan file eksternal*/

void LoadPlayer (Player *P, char *namafile);
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. P berisi data player dari file eksternal*/

void CreatePlayer (Player *P, Kata nama);
/* I.S. P sembarang, nama terdefinisi */
/* F.S. Membentuk player baru dengan (P).name = nama dengan status yang sudah ditentukan berdasarkan pilihan user*/ 

void wCreatePlayer(WINDOW *menu, Player *P, Kata nama, boolean *created);
/* I.S. P sembarang, menu dan nama terdefinisi, created sembarang */
/* F.S. Membentuk player baru dengan (P).name = nama dengan status yang sudah ditentukan berdasarkan pilihan user, created true jika player dibuat dan false jika tidak */ 

void print_choice(WINDOW *menu_win, int pilihan);
/* I.S. menu_win dan pilihan[1..5] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */

boolean IsLevelUp(Player P);
/* Menghasilkan true jika EXP P cukup untuk naik level */

void LevelUp (Player * P);
/* Menaikan level player bila sudah mencapai Exp tertentu */

// void AddSkill (Player * P);
/* Daftar skill player pada tiap level */

#endif