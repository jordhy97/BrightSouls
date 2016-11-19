/* Nama file    : BrightSouls.c            			*/
/* Last Edited  : 13 November 2016         			*/

#include <ncurses.h>
#include "../MesinKarKata/mesinkar.h"
#include "../MesinKarKata/mesinkata.h"
#include "../Peta/peta.h"
#include "../Enemy/enemy.h"
#include "../Player/player.h"
#include "../StackQueue/stackqueue.h"
#include "boolean.h"

#define Game_Height 29
#define Game_Width 121

/* DEKLARASI FUNGSI DAN PROSEDUR */
int Mid_y(int y);
// BUtuh offset??

int Mid_x(int x);

WINDOW *create_newwin(int height, int width, int starty, int startx);
/* Menghasilkan pointer to WINDOW dengan tinggi sebesar height, lebar sebesar width, posisi sumbu y dimulai dari starty, dan posisi sumbu x dimulai dari startx */
void print_menu(WINDOW *menu_win, int pilihan);
/* I.S. menu_win dan pilihan[1..4] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */
void main_menu(int *choice, float tunda);
/* I.S. choice sembarang */
/* F.S. choice berisi pilihan user */
/* Proses: Menampilkan main menu dan menunggu sampai user menentukan pilihannya */
void delay(float s);
/* I.S. s terdefinisi */
/* F.S. Proses ditunda selama s second */
void explore(Player *P);

void battle();

int main()
{
	/* KAMUS */
	WINDOW *New_Game, *Pop_Up;
	int pilihan;
	Player P;
	Kata nama;
	char temp[50];
	boolean mulai, quit, created, loaded;

	/* ALGORITMA */
	initscr()	;
	cbreak();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));
	curs_set(0);
	refresh();
	battle();
	delay(100);
	main_menu(&pilihan, 0.001);
	nama.Length = 0;
	mulai = false;
	quit = false;
	created = false;
	loaded = false;
	while((!mulai) && (!quit))
	{
		switch(pilihan)
		{
			case 1:
				New_Game = create_newwin(Game_Height, Game_Width, Mid_y(Game_Height), Mid_x(Game_Width));
				wborder(New_Game, 0, 0, 0, 0, 0, 0, 0, 0);
				mvwprintw(New_Game,1,1, "Enter Player Name: ");
				wrefresh(New_Game);
				curs_set(1);
				echo();
				wBacaKata(New_Game,&nama);
				curs_set(0);
				noecho();
				wCreatePlayer(New_Game, &P, nama);
				wclear(New_Game);
				wrefresh(New_Game);
				delwin(New_Game);
				main_menu(&pilihan, 0.001);
				break;
			case 2:
				if(!IsKataEmpty(Name(P)))
				{
					mulai = true;
				}
				else
				{
					Pop_Up = create_newwin(3, 100, Mid_y(3) + 1, Mid_x(100));	
					wborder(Pop_Up, 0, 0, 0, 0, 0, 0, 0, 0);
					mvwprintw(Pop_Up, 1, 36, "You haven't created a player");
					wrefresh(Pop_Up);			
					delay(2);
					wclear(Pop_Up);
					wrefresh(Pop_Up);
					delwin(Pop_Up);
					main_menu(&pilihan,0);
				}
				break;
			case 3:
				main_menu(&pilihan, 0.001);
				break;
			case 4:
				quit = true;
		}
	}
	if(mulai)
	{
		explore(&P);
	}
	endwin();
	return 0;
}

/* REALISASI FUNGSI DAN PROSEDUR */
int Mid_y(int y)
{
	/* ALGORITMA */
	return ((LINES - y) / 2);
}

int Mid_x(int x)
{
	/* ALGORITMA */
	return ((COLS - x) / 2);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
/* Menghasilkan pointer to WINDOW dengan tinggi sebesar height, lebar sebesar width, posisi sumbu y dimulai dari starty, dan posisi sumbu x dimulai dari startx */
{
	/* KAMUS LOKAL */
	WINDOW *local_win;

	/* ALGORITMA */
	local_win = newwin(height, width, starty, startx);
	wbkgd(local_win, COLOR_PAIR(1));
	return local_win;
}

void print_menu(WINDOW *menu_win, int pilihan)
/* I.S. menu_win dan pilihan[1..4] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */
{
	/* KAMUS LOKAL */
	int i;	
	char *choices[] = {"New Game","Start Game","Load Game","Exit"};

	/* ALGORITMA */
	wattron(menu_win, COLOR_PAIR(1));
	for(i = 0; i < 4; ++i)
	{	if(pilihan == i + 1) 
		{	 
			mvwprintw(menu_win, i, 0, ">%s", choices[i]);
		}
		else
		{
			mvwprintw(menu_win, i, 0, " %s", choices[i]);
		}
	}
	wattroff(menu_win, COLOR_PAIR(1));
	wrefresh(menu_win);
}

void main_menu(int *choice, float tunda)
/* I.S. choice sembarang */
/* F.S. choice berisi pilihan user */
/* Proses: Menampilkan main menu dan menunggu sampai user menentukan pilihannya */
{
	/* KAMUS LOKAL */
	WINDOW *title, *menu;
	int pilihan, ch;
	boolean chosen;

	/* ALGORITMA */
	title = create_newwin(Game_Height, Game_Width, Mid_y(Game_Height), Mid_x(Game_Width));
	START("src/Main/title.txt");
	wattron(title, COLOR_PAIR(1));
	while(!EOP)
	{
		wprintw(title, "%c", CC);
		wrefresh(title);
		delay(tunda);
		ADV();
	}
	wattroff(title, COLOR_PAIR(1)); 
	wrefresh(title);
	menu = create_newwin(4, 11,  Mid_y(Game_Height) + 22, Mid_x(Game_Width) + 95);
	chosen = false;
	pilihan = 1;
	print_menu(menu, pilihan);
	keypad(menu, TRUE);
	while(!chosen)
	{
		ch = wgetch(menu);
		switch(ch)
		{
			case KEY_UP:
				if(pilihan == 1)
				{
					pilihan = 4;

				}
				else
				{
					pilihan--;
				}
				break;
			case KEY_DOWN:
				if(pilihan == 4)
				{
					pilihan = 1;
				}
				else
				{
					pilihan++;
				}
				break;
			case ENTER :
				chosen = true;
				break;
		}
		print_menu(menu, pilihan);
	}
	delwin(title);
	delwin(menu);				//Biar bisa pop-up
	/*clear();
	refresh();*/
	*choice = pilihan;
}

void delay(float s)
/* I.S. s terdefinisi */
/* F.S. Proses ditunda selama s second */
{
	/* KAMUS LOKAL */
	int i;

	/* ALGORITMA */
	for(i = 0; i < (100000000 * s); i++)
	{
	}
}

void explore(Player *P)
{
	/* KAMUS LOKAL */
	WINDOW *P_Name, *P_Lvl, *P_HP, *P_Str, *P_Def, *P_Exp, *Message, *Command, *Map, *BatasKanan, *BatasKiri;
	int starty, startx;
	
	/* COBA PETA */
	Peta Test;
	Area START;
	CreateRandomPeta(&Test, "src/Peta/peta.txt");
	START = SubPeta(Test,1);
	Position(*P) = MakePOINT(3,3);
	Kata Masukan, GU, GD, GL, GR, EXIT;
	GU.TabKata[1] = 'G';
	GU.TabKata[2] = 'U';
	GU.Length = 2;
	GD.TabKata[1] = 'G';
	GD.TabKata[2] = 'D';
	GD.Length = 2;
	GL.TabKata[1] = 'G';
	GL.TabKata[2] = 'L';
	GL.Length = 2;
	GR.TabKata[1] = 'G';
	GR.TabKata[2] = 'R';
	GR.Length = 2;
	EXIT.TabKata[1] = 'E';
	EXIT.TabKata[2] = 'X';
	EXIT.TabKata[3] = 'I';
	EXIT.TabKata[4] = 'T';
	EXIT.Length = 4;

	/* ALGORITMA */
	starty = Mid_y(Game_Height);
	startx = Mid_x(Game_Width);
	BatasKanan = create_newwin(Game_Height,18,starty, startx + 103);
	Message = create_newwin(3, 104, starty + 24, startx);
	BatasKiri = create_newwin(23, 19, starty + 2, startx);
	Map = create_newwin(23,86, starty + 2, startx + 18);
	P_Name = create_newwin(3, 19, starty, startx);
	P_Lvl = create_newwin(3, 18, starty, startx + 18);
	P_HP = create_newwin(3, 18, starty, startx + 35);
	P_Str = create_newwin(3, 18, starty, startx + 52);
	P_Def = create_newwin(3, 18, starty, startx + 69);
	P_Exp = create_newwin(3, 18, starty, startx + 86);
	Command = create_newwin(3, 104, starty + 26, startx);
	wborder(BatasKanan, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(Message, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(BatasKiri, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(Map, 0, 0, 0, 0, 0, 0, ACS_BTEE, ACS_RTEE);
	wborder(P_Name, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(P_Lvl, 0, 0, 0, 0, ACS_TTEE, 0, ACS_PLUS, 0);;
	wborder(P_HP, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Str, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Def, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Exp, 0, 0, 0, 0, ACS_TTEE, ACS_TTEE, ACS_BTEE, ACS_RTEE);
	wborder(Command, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, ACS_BTEE);
	wmove(P_Name, 1, 1);
	wPrintArea(Map, START, Position(*P));
	wTulisKata(P_Name, Name(*P));
	mvwprintw(P_Lvl, 1, 1, "LVL: %d", Level(*P)); 
	mvwprintw(P_HP, 1, 1, "HP: %d", HP(*P)); 
	mvwprintw(P_Str, 1, 1, "STR: %d", Strength(*P)); 
	mvwprintw(P_Def, 1, 1, "DEF: %d", Defense(*P));
	mvwprintw(P_Exp, 1, 1, "EXP: %d", Exp(*P));
	mvwprintw(Command, 1, 1, "Command: ");  
	curs_set(1);
	wrefresh(BatasKanan);
	wrefresh(Message);
	wrefresh(BatasKiri);
	wrefresh(Map);
	wrefresh(P_Name);
	wrefresh(P_Lvl);
	wrefresh(P_HP);
	wrefresh(P_Str);
	wrefresh(P_Def);
	wrefresh(P_Exp);
	wrefresh(Command);

	echo();
	wBacaKata(Command,&Masukan);
	while(!IsKataSama(Masukan,EXIT))
	{
		if(IsKataSama(Masukan,GU))
		{
			if(IsPassable(START,Ordinat(Position(*P)) - 1,Absis(Position(*P))))
			{
				Ordinat(Position(*P))--;
			}
		}
		else if(IsKataSama(Masukan,GD))
		{
			if(IsPassable(START,Ordinat(Position(*P)) + 1,Absis(Position(*P))))
			{
				Ordinat(Position(*P))++;
			}
		}
		else if(IsKataSama(Masukan,GR))
		{
			if(IsPassable(START,Ordinat(Position(*P)),Absis(Position(*P)) + 1))
			{
				Absis(Position(*P))++;
			}
		}
		else if(IsKataSama(Masukan,GL))
		{
			if(IsPassable(START,Ordinat(Position(*P)),Absis(Position(*P)) - 1))
			{
				Absis(Position(*P))--;
			}
		}
		if(Absis(Position(*P)) > GetLastIdxKol(Info(START)))
		{
			START = East(START);
			Absis(Position(*P)) = 1;
		}
		if(Ordinat(Position(*P)) > GetLastIdxBrs(Info(START)))
		{
			START = South(START);
			Ordinat(Position(*P)) = 1;
		}
		if(Absis(Position(*P)) == 0)
		{
			START = West(START);
			Absis(Position(*P)) = GetLastIdxKol(Info(START));
		}
		if(Ordinat(Position(*P)) == 0)
		{
			START = North(START);
			Ordinat(Position(*P)) = GetLastIdxBrs(Info(START));
		}
		wPrintArea(Map, START, Position(*P));
		wrefresh(Map);
		werase(Command);
		mvwprintw(Command, 1, 1, "Command: "); 
		wborder(Command, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, ACS_BTEE);
		wrefresh(Command);
		wBacaKata(Command,&Masukan);
	}
	DealokasiPeta(&Test);
}

void battle()
{
	/* KAMUS LOKAL */
	WINDOW *P_Name, *P_Lvl, *P_HP, *P_Str, *P_Def, *P_Exp, *Round, *E_Name, *E_HP, *E_Command, *Message, *P_Command, *Inserted_Command;
	int starty, startx;
	
	/* ALGORITMA */
	starty = Mid_y(11);
	startx = Mid_x(Game_Width);
	Message = create_newwin(6, Game_Width, starty + 4, startx);
	E_Name = create_newwin(3, 19, starty + 2, startx);
	E_HP = create_newwin(3, 18, starty + 2, startx + 18);
	E_Command = create_newwin(3, 86, starty + 2, startx + 35);
	P_Name = create_newwin(3, 19, starty, startx);
	P_Lvl = create_newwin(3, 18, starty, startx + 18);
	P_HP = create_newwin(3, 18, starty, startx + 35);
	P_Str = create_newwin(3, 18, starty, startx + 52);
	P_Def = create_newwin(3, 18, starty, startx + 69);
	P_Exp = create_newwin(3, 18, starty, startx + 86);
	Round = create_newwin(3,18,starty, startx + 103);
	Inserted_Command = create_newwin(3, Game_Width, starty + 7, startx);
	P_Command = create_newwin(3, Game_Width, starty + 7, startx);
	wborder(Message, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(E_Name, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(E_HP, 0, 0, 0, 0, 0, 0, ACS_BTEE, ACS_BTEE);
	wborder(E_Command, 0, 0, 0, 0, 0, 0, ACS_BTEE, ACS_RTEE);
	wborder(P_Name, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(P_Lvl, 0, 0, 0, 0, ACS_TTEE, 0, ACS_PLUS, 0);;
	wborder(P_HP, 0, 0, 0, 0, ACS_TTEE, 0, ACS_PLUS, 0);
	wborder(P_Str, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Def, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Exp, 0, 0, 0, 0, ACS_TTEE, ACS_TTEE, ACS_BTEE, ACS_RTEE);
	wborder(Round, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, ACS_RTEE);
	wborder(P_Command, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
	wrefresh(Message);
	wrefresh(E_Name);
	wrefresh(E_HP);
	wrefresh(E_Command);;
	wrefresh(P_Name);
	wrefresh(P_Lvl);
	wrefresh(P_HP);
	wrefresh(P_Str);
	wrefresh(P_Def);
	wrefresh(P_Exp);
	wrefresh(Round);
	wrefresh(Inserted_Command);
	wrefresh(P_Command);
}