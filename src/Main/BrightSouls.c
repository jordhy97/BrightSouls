/* Nama file    : BrightSouls.c            			*/
/* Last Edited  : 20 November 2016         			*/

#include <ncurses.h>
#include <time.h>
#include "../MesinKarKata/mesinkar.h"
#include "../MesinKarKata/mesinkata.h"
#include "../Peta/peta.h"
#include "../Enemy/enemy.h"
#include "../Player/player.h"
#include "../StackQueue/stackqueue.h"
#include "../Shared/boolean.h"
#include "../Matriks/matriks.h"
#include "../Jam/jam.h"

#define Game_Height 29
#define Game_Width 121

/* GLOBAL VARIABLE (GAME STATE) */
Player P;
Peta MAP;
JAM T_Start;
boolean new;

/* DEKLARASI FUNGSI DAN PROSEDUR */
int Mid_y(int y);
/* Mengembalikan ordinat tengah terhadap sumbu y terminal dengan offset sebesar (-y/2) */

int Mid_x(int x);
/* Mengembalikan absis tengah terhadap sumbu x terminal dengan offset sebesar (-x/2) */

WINDOW *create_newwin(int height, int width, int starty, int startx);
/* Menghasilkan pointer to WINDOW dengan tinggi sebesar height, lebar sebesar width, posisi sumbu y dimulai dari starty, dan posisi sumbu x dimulai dari startx */

void print_menu(WINDOW *menu_win, int pilihan);
/* I.S. menu_win dan pilihan[1..4] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */

void delay(float s);
/* I.S. s terdefinisi */
/* F.S. Proses ditunda selama s second */

void Create_explore_border();
/* I.S. sembarang */
/* F.S. menampilkan ke layar border untuk mode eksplorasi */

void explore();
/* Mode eksplorasi */

void battle();
/* Mode battle */

void Load();
/* I.S. Sembarang */ 
/* F.S. me-load pilihan user */

void Pop_Up_Message(char *message, float t);
/* I.S. Sembarang */
/* F.S. menampilkan Pop_up message selama t second */

void Display_saveFile(WINDOW *win, char *namafile, boolean *empty);
/* I.S. win dan namafile terdefinisi, empty sembarang */
/* F.S. Menampilkan isi save file ke win, empty true jika file kosong dan false jika tidak */

void New_Game();
/* I.S. Sembarang */
/* F.S. Membuat player baru dengan nama dari input user atau tidak terbentuk apa-apa jika user membatalkan */

void Save();
/* I.S. Sembarang */
/* F.S. Game State tersimpan ke file eksternal */

void SaveFile(char *namafile);
/* I.S. namafile terdefinisi */
/* F.S. Game State tersimpan ke file dengan namafile */

void GetOldPlayTime(char *namafile, JAM *J);
/* I.S. namafile terdefinisi, J sembarang */
/* F.S. J berisi playtime dari file dengan nama namafile */

/*** Not Yet impemented ***/
//void Tutorial_explore();
//void Tutorial_battle();
/*************************/

int main()
{
	/* KAMUS */
	WINDOW *title, *menu;
	int pilihan, ch;
	boolean chosen, mulai, quit;

	/* ALGORITMA */
	
	/* Inisialisasi Variable */
	initscr();
	cbreak();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	//bkgd(COLOR_PAIR(1));
	curs_set(0);
	refresh();
	Name(P).Length = 0;
	IDEff(MAP) = 0;
	mulai = false;
	quit = false;
	new = false;

	/* Main Menu */
	title = create_newwin(Game_Height, Game_Width, Mid_y(Game_Height), Mid_x(Game_Width));
	menu = create_newwin(4, 11,  Mid_y(Game_Height) + 22, Mid_x(Game_Width) + 95);
	/* Load title screen */
	START("src/Database/title.txt");
	while(!EOP)
	{
		wprintw(title, "%c", CC);
		wrefresh(title);
		delay(0.001);
		ADV();
	}
	pilihan = 1;
	keypad(menu, TRUE);
	do
	{
		/* Refresh title screen */
		wmove(title,0,0);
		START("src/Database/title.txt");
		while(!EOP)
		{
			wprintw(title, "%c", CC);
			wrefresh(title);
			ADV();
		}
		wrefresh(title);
		print_menu(menu, pilihan);
		chosen = false;
		/* Choosing options in main menu */
		do
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
		}while(!chosen);

		/* Process chosen option */
		switch(pilihan)
		{
			case 1:
				/* New Game Menu */
				New_Game();
				break;
			case 2:
				/* Start Game */
				if(!IsKataEmpty(Name(P)))
				{
					mulai = true;
				}
				else
				{
					Pop_Up_Message("You haven't created/loaded a player", 3);
				}
				break;
			case 3:
				/* Load Game */
				clear();
				refresh();
				Load();
				break;
			case 4:
				/* Exit */
				quit = true;
				break;
		}
	}while((!mulai) && (!quit));

	/* Delete dan Dealokasi */
	clear();
	refresh();
	delwin(title);
	delwin(menu);

	/* Start Game */
	if(mulai)
	{
		if(new)
		{
			CreateRandomPeta(&MAP, "src/Database/Areas.txt");
		}
		explore();
	}
	endwin();
	return 0;
}

/* REALISASI FUNGSI DAN PROSEDUR */
int Mid_y(int y)
/* Mengembalikan ordinat tengah terhadap sumbu y terminal dengan offset sebesar (-y/2) */
{
	/* ALGORITMA */
	return ((LINES - y) / 2);
}

int Mid_x(int x)
/* Mengembalikan absis tengah terhadap sumbu x terminal dengan offset sebesar (-x/2) */
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
	wrefresh(menu_win);
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

void Create_explore_border()
/* I.S. sembarang */
/* F.S. menampilkan ke layar border untuk mode eksplorasi */
{
	/* KAMUS LOKAL */
	WINDOW *P_Name_Border, *P_Lvl_Border, *P_HP_Border, *P_Str_Border, *P_Def_Border, *P_Exp_Border, *Message_Border, *Command_Border, *Map_Border, *BatasKanan, *BatasKiri;
	int starty, startx;

	/* ALGORITMA */
	/* Set Position */
	starty = Mid_y(Game_Height);
	startx = Mid_x(Game_Width);

	/* Create window */
	BatasKanan = create_newwin(Game_Height,18,starty, startx + 103);
	Message_Border = create_newwin(3, 104, starty + 24, startx);
	BatasKiri = create_newwin(23, 19, starty + 2, startx);
	Map_Border = create_newwin(23,86, starty + 2, startx + 18);
	P_Name_Border = create_newwin(3, 19, starty, startx);
	P_Lvl_Border = create_newwin(3, 18, starty, startx + 18);
	P_HP_Border = create_newwin(3, 18, starty, startx + 35);
	P_Str_Border = create_newwin(3, 18, starty, startx + 52);
	P_Def_Border = create_newwin(3, 18, starty, startx + 69);
	P_Exp_Border = create_newwin(3, 18, starty, startx + 86);
	Command_Border = create_newwin(3, 104, starty + 26, startx);

	/* Create border */
	wborder(BatasKanan, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(Message_Border, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(BatasKiri, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(Map_Border, 0, 0, 0, 0, 0, 0, ACS_BTEE, ACS_RTEE);
	wborder(P_Name_Border, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(P_Lvl_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_PLUS, 0);;
	wborder(P_HP_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Str_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Def_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Exp_Border, 0, 0, 0, 0, ACS_TTEE, ACS_TTEE, ACS_BTEE, ACS_RTEE);
	wborder(Command_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, ACS_BTEE);
	
	/* Display */
	wrefresh(BatasKanan);
	wrefresh(Message_Border);
	wrefresh(BatasKiri);
	wrefresh(Map_Border);
	wrefresh(P_Name_Border);
	wrefresh(P_Lvl_Border);
	wrefresh(P_HP_Border);
	wrefresh(P_Str_Border);
	wrefresh(P_Def_Border);
	wrefresh(P_Exp_Border);
	wrefresh(Command_Border);
	
	/* Dealokasi */
	delwin(BatasKanan);
	delwin(Message_Border);
	delwin(BatasKiri);
	delwin(Map_Border);
	delwin(P_Name_Border);
	delwin(P_Lvl_Border);
	delwin(P_HP_Border);
	delwin(P_Str_Border);
	delwin(P_Def_Border);
	delwin(P_Exp_Border);
	delwin(Command_Border);
	
}

void explore()
/* Mode eksplorasi */
{
	/* KAMUS LOKAL */
	WINDOW *P_Name, *P_Lvl, *P_HP, *P_Str, *P_Def, *P_Exp, *Message, *Command, *Map;
	int starty, startx;
	Kata Masukan, GU, GR, GD, GL, SKILL, SAVE, LOAD, EXIT;
	POINT NextPOINT;
	boolean valid, quit, win, game_over, end;
	Area START;

	
	/* ALGORITMA */

	/* Inisialasi */
	START = SubPeta(MAP,CArea(P));
	Position(P) = MakePOINT(5,6);

	/* Create All Possible Command */
	CreateKata(&GU, "GU");
	CreateKata(&GR, "GR");
	CreateKata(&GD, "GD");
	CreateKata(&GL, "GL");
	CreateKata(&SKILL, "SKILL");
	CreateKata(&SAVE, "SAVE");
	CreateKata(&LOAD, "LOAD");
	CreateKata(&EXIT, "EXIT");
	
	/* Create border */
	Create_explore_border();

	/* Set Position */
	starty = Mid_y(Game_Height);
	startx = Mid_x(Game_Width);

	/* Create window */
	Message = create_newwin(1, 102, starty + 25, startx + 1);
	Map = create_newwin(21,84, starty + 3, startx + 19);
	P_Name = create_newwin(1, 17, starty + 1, startx + 1);
	P_Lvl = create_newwin(1, 16, starty + 1, startx + 19);
	P_HP = create_newwin(1, 16, starty + 1, startx + 36);
	P_Str = create_newwin(1, 16, starty + 1, startx + 53);
	P_Def = create_newwin(1, 16, starty + 1, startx + 70);
	P_Exp = create_newwin(1, 16, starty + 1, startx + 87);
	Command = create_newwin(1, 102, starty + 27, startx + 1);
	
	/* Display */
	wmove(P_Name, 0, 0);
	wTulisKata(P_Name, Name(P));
	wprintw(P_Lvl, "LVL: %d", Level(P)); 
	wprintw(P_HP, "HP: %d", HP(P)); 
	wprintw(P_Str, "STR: %d", Strength(P)); 
	wprintw(P_Def, "DEF: %d", Defense(P));
	wprintw(P_Exp, "EXP: %d", Exp(P));

	wrefresh(P_Name);
	wrefresh(P_Lvl);
	wrefresh(P_HP);
	wrefresh(P_Str);
	wrefresh(P_Def);
	wrefresh(P_Exp);

	echo();
	curs_set(1);
	quit = false;
	game_over = false;
	do
	{
		valid = true;
		wPrintArea(Map, START, Position(P));
		wrefresh(Map);
		wrefresh(Message);
		wclear(Command);
		wprintw(Command, "Command: "); 
		wrefresh(Command);
		wBacaKata(Command,&Masukan);
		wclear(Message);
		if(IsKataSama(Masukan, GU))
		{
			if(IsPassable(START, PlusDelta(Position(P), 0, -1)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(P), 0, -1));
			}
		}
		else if(IsKataSama(Masukan, GR))
		{
			if(IsPassable(START, PlusDelta(Position(P), 1, 0)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(P), 1, 0));
			}
		}
		else if(IsKataSama(Masukan, GD))
		{
			if(IsPassable(START, PlusDelta(Position(P), 0, 1)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(P), 0, 1));
			}
		}
		else if(IsKataSama(Masukan, GL))
		{
			if(IsPassable(START, PlusDelta(Position(P), -1, 0)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(P), -1, 0));
			}
		}
		else if(IsKataSama(Masukan, SKILL))
		{
			//DisplaySkill
		}
		else if(IsKataSama(Masukan, SAVE))
		{
			Save();
		}
		else if(IsKataSama(Masukan, LOAD))
		{
			Load();
		}
		else if(IsKataSama(Masukan, EXIT))
		{
			quit = true;
		}
		else
		{
			valid = false;
			wprintw(Message, "Invalid Command!");  
		}
		if(valid && !quit)
		{
			if(IsEnemy(START, NextPOINT))
			{
				/* BATTLE */
				battle();
			}
			else if(!IsKataSama(Masukan, EXIT))	
			{
				SetPOINT(&Position(P), NextPOINT);
			}
			if(IsMedicine(START, Position(P)))
			{
				ClearPOINT(&START, Position(P));
				wprintw(Message, "Got a medicine! HP +%d", Max_HP(P) - HP(P));
				HP(P) = Max_HP(P);
				wclear(P_HP);
				wprintw(P_HP, "HP: %d", HP(P)); 
				wrefresh(P_HP);
			}
			/* Changing Area */
			if(Ordinat(Position(P)) < GetFirstIdxBrs(Info(START)))
			{
				START = Neighbour(START, 1);
				SetPOINT(&Position(P), P_Neighbour(START, 3));
			}
			else if(Absis(Position(P)) > GetLastIdxKol(Info(START)))
			{
				START = Neighbour(START, 2);
				SetPOINT(&Position(P), P_Neighbour(START, 4));
			}
			else if(Ordinat(Position(P)) > GetLastIdxBrs(Info(START)))
			{
				START = Neighbour(START, 3);
				SetPOINT(&Position(P), P_Neighbour(START, 1));
			}
			else if(Absis(Position(P)) < GetFirstIdxKol(Info(START)))
			{
				START = Neighbour(START, 4);
				SetPOINT(&Position(P), P_Neighbour(START, 2));
			}
		}
	}while(!quit && !game_over && !end);
	DealokasiPeta(&MAP);
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

	clear();
	refresh();
	delwin(Message);
	delwin(E_Name);
	delwin(E_HP);
	delwin(E_Command);
	delwin(P_Name);
	delwin(P_Lvl);
	delwin(P_HP);
	delwin(P_Str);
	delwin(P_Def);
	delwin(P_Exp);
	delwin(Round);
	delwin(Inserted_Command);
	delwin(P_Command);
}


void Load()
/* I.S. Sembarang */ 
/* F.S. me-load pilihan user */
{
	/* KAMUS LOKAL */
	WINDOW *slot1, *slot2, *Exit, *slot1_Border, *slot2_Border, *Exit_Border;
	int starty, startx, pilihan, ch;
	boolean chosen, empty1, empty2;
	
	/* ALGORITMA */
	/* Set Position */
	starty = Mid_y(17);
	startx = Mid_x(Game_Width);

	/* Create window */
	slot1_Border = create_newwin(8, 121, starty, startx);
	slot2_Border = create_newwin(8, 121, starty + 7, startx);
	Exit_Border = create_newwin(3, 121, starty + 14, startx);
	slot1 = create_newwin(6, 119, starty + 1, startx + 1);
	slot2 = create_newwin(6, 119, starty + 8, startx + 1);
	Exit = create_newwin(1, 119, starty + 15, startx + 1);

	/* Create border */
	wborder(slot1_Border, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(slot2_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
	wborder(Exit_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);

	/* Display */
	wrefresh(slot1_Border);
	wrefresh(slot2_Border);
	wrefresh(Exit_Border);	

	/* Reading from external files */
	Display_saveFile(slot1, "src/Database/savedata1.txt", &empty1);
	Display_saveFile(slot2, "src/Database/savedata2.txt", &empty2);	

	/* Choosing Save File */
	keypad(Exit, TRUE);
	pilihan = 1;
	chosen = false;
	do
	{	wmove(slot1,0, 0);
		wmove(slot2,0, 0);
		wmove(Exit,0, 0);
		if(pilihan == 1)
		{
			wprintw(slot1, ">Slot 1");
			wprintw(slot2, " Slot 2");
			wprintw(Exit, " Exit");
		}
		else if (pilihan == 2)
		{
			wprintw(slot1, " Slot 1");
			wprintw(slot2, ">Slot 2");
			wprintw(Exit, " Exit");
		}
		else
		{
			wprintw(slot1, " Slot 1");
			wprintw(slot2, " Slot 2");
			wprintw(Exit, ">Exit");	
		}
		wrefresh(slot1);
		wrefresh(slot2);
		wrefresh(Exit);
		ch = wgetch(Exit);
		switch(ch)
		{
			case KEY_UP:
				if(pilihan == 1)
				{
					pilihan = 3;
				}
				else
				{
					pilihan--;
				}
				break;
			case KEY_DOWN:
				if(pilihan == 3)
				{
					pilihan = 1;
				}
				else
				{
					pilihan++;
				}
				break;
			case ENTER :
				if((pilihan == 1 && !empty1) || (pilihan == 2 && !empty2) || (pilihan == 3))
				{
					chosen = true;
				}
				break;
		}
	}while(!chosen);

	/* Load Files based on choice */
	switch(pilihan)
	{
		case 1:
			//LoadPlayer(&P, "player1.txt");
			/* Dealokasi current peta */
			//DealokasiPeta(&MAP);
			//LoadPeta(&MAP,"subpeta1.txt", "koneksi1.txt");
			Pop_Up_Message("File successfully loaded", 3);
			new = false;
			break;
		case 2:
			//LoadPlayer(&P, "player2.txt");
			/* Dealokasi current peta */
			//DealokasiPeta(&MAP);
			//LoadPeta(&MAP,"subpeta2.txt", "koneksi2.txt");
			Pop_Up_Message("File successfully loaded", 3);
			new = false;
			break;
	}

	/* Delete dan Dealokasi */
	clear();
	refresh();
	delwin(slot1_Border);
	delwin(slot2_Border);
	delwin(Exit_Border);
	delwin(slot1);
	delwin(slot2);
	delwin(Exit);
}

void Display_saveFile(WINDOW *win, char *namafile, boolean *empty)
/* I.S. win dan namafile terdefinisi, empty sembarang */
/* F.S. Menampilkan isi save file ke win, empty true jika file kosong dan false jika tidak */
{
	/* KAMUS LOKAL */
	int i, level, H, M, S;
	char nama[50], LastPlayed[50];
	JAM TimePlayed;

	/* ALGORITMA */
	START(namafile);
	if(EOP)
	{
		mvwprintw(win, 2, 57, "Empty");
		*empty = true;
	}
	else
	{
		*empty = false;
		i = 0;
		do
		{
			nama[i] = CC;
			i++;
			ADV();
		}while(CC != ENTER);
		nama[i] = '\0';
		ADV();
		level = 0;
		do
		{
			level = level * 10 + (CC -'0');
			ADV();
		}while(CC != ENTER);
		ADV();
		i = 0;
		do
		{
			LastPlayed[i] = CC;
			i++;
			ADV();
		}while(CC != ENTER);
		LastPlayed[i] = '\0';
		ADV();
		H = 0;
		do
		{	
			H = H * 10 + (CC - '0');	
			ADV();
		}while(CC != ':');
		ADV();
		M = 0;
		do
		{	
			M = M * 10 + (CC - '0');	
			ADV();
		}while(CC != ':');
		ADV();
		S = 0;
		do
		{	
			S = S * 10 + (CC - '0');	
			ADV();
		}while(CC != MARK);
		TimePlayed = MakeJAM(H,M,S);
		mvwprintw(win, 2, 0, " Player: %s", nama);
		mvwprintw(win, 3, 0, " Level: %d", level);
		mvwprintw(win, 4, 0, " Last Played: %s", LastPlayed);
		mvwprintw(win, 5, 0, " Play Time: ");
		wTulisJAM(win, TimePlayed);
	}
}

void Pop_Up_Message(char *message, float t)
/* I.S. Sembarang */
/* F.S. menampilkan Pop_up message selama t second */
{
	/* KAMUS LOKAL */
	int panjang;
	WINDOW *Pop_Up;

	/* ALGORITMA */
	panjang = 0;
	while(message[panjang] != '\0')
	{
		panjang++;
	}
	Pop_Up = create_newwin(3, 100, Mid_y(3), Mid_x(100));	
	wborder(Pop_Up, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(Pop_Up, 1, (100-panjang)/2, message);
	wrefresh(Pop_Up);			
	delay(t);
	wclear(Pop_Up);
	wrefresh(Pop_Up);
	delwin(Pop_Up);
}

void New_Game()
/* I.S. Sembarang */
/* F.S. Membuat player baru dengan nama dari input user atau tidak terbentuk apa-apa jika user membatalkan */
{
	/* KAMUS LOKAL */
	WINDOW *menu;
	Kata nama;
	boolean created;

	/* ALGORITMA */
	menu = create_newwin(Game_Height, Game_Width, Mid_y(Game_Height), Mid_x(Game_Width));
	wborder(menu, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(menu,1,1, " Enter Player Name: ");
	mvwprintw(menu,2,1, " (max 17 character and contains no spaces)");
	wrefresh(menu);
	curs_set(1);
	echo();
	do
	{
		wmove(menu,1, 21);
		wBacaKata(menu,&nama);
	}while(nama.Length == 0);
	if(nama.Length > 17)
	{
		nama.Length = 17;
	}
	curs_set(0);
	noecho();
	wCreatePlayer(menu, &P, nama, &created);
	if(created)
	{
		Pop_Up_Message("Player successfully created", 3);
	}
	wclear(menu);
	wrefresh(menu);
	delwin(menu);
	new = true;
}

void Save()
/* I.S. Sembarang */
/* F.S. Game State tersimpan ke file eksternal */
{
	/* KAMUS LOKAL */
	WINDOW *slot1, *slot2, *Exit, *slot1_Border, *slot2_Border, *Exit_Border;
	int starty, startx, pilihan, ch;
	boolean chosen, empty1, empty2;
	
	/* ALGORITMA */
	/* Set Position */
	starty = Mid_y(17);
	startx = Mid_x(Game_Width);

	/* Create window */
	slot1_Border = create_newwin(8, 121, starty, startx);
	slot2_Border = create_newwin(8, 121, starty + 7, startx);
	Exit_Border = create_newwin(3, 121, starty + 14, startx);
	slot1 = create_newwin(6, 119, starty + 1, startx + 1);
	slot2 = create_newwin(6, 119, starty + 8, startx + 1);
	Exit = create_newwin(1, 119, starty + 15, startx + 1);

	/* Create border */
	wborder(slot1_Border, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(slot2_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
	wborder(Exit_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);

	/* Display */
	wrefresh(slot1_Border);
	wrefresh(slot2_Border);
	wrefresh(Exit_Border);	

	/* Choosing Save File */
	keypad(Exit, TRUE);
	pilihan = 1;
	chosen = false;
	do
	{
		/* Reading from external files */
		Display_saveFile(slot1, "src/Database/savedata1.txt", &empty1);
		Display_saveFile(slot2, "src/Database/savedata2.txt", &empty2);	
		do
		{	wmove(slot1, 0, 0);
			wmove(slot2, 0, 0);
			wmove(Exit, 0, 0);
			if(pilihan == 1)
			{
				wprintw(slot1, ">Slot 1");
				wprintw(slot2, " Slot 2");
				wprintw(Exit, " Exit");
			}
			else if (pilihan == 2)
			{
				wprintw(slot1, " Slot 1");
				wprintw(slot2, ">Slot 2");
				wprintw(Exit, " Exit");
			}
			else
			{
				wprintw(slot1, " Slot 1");
				wprintw(slot2, " Slot 2");
				wprintw(Exit, ">Exit");	
			}
			wrefresh(slot1);
			wrefresh(slot2);
			wrefresh(Exit);
			ch = wgetch(Exit);
			switch(ch)
			{
				case KEY_UP:
					if(pilihan == 1)
					{
						pilihan = 3;
					}
					else
					{
						pilihan--;
					}
					break;
				case KEY_DOWN:
					if(pilihan == 3)
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
		}while(!chosen);

	/* Save Files based on choice */
		switch(pilihan)
		{
			case 1:
				//LoadPlayer(&P, "player1.txt");
				/* Dealokasi current peta */
				//DealokasiPeta(&MAP);
				//LoadPeta(&MAP,"subpeta1.txt", "koneksi1.txt");
				SaveFile("src/Database/savedata1.txt");
				Pop_Up_Message("File successfully saved", 3);
				break;
			case 2:
				//LoadPlayer(&P, "player2.txt");
				/* Dealokasi current peta */
				//DealokasiPeta(&MAP);
				//LoadPeta(&MAP,"subpeta2.txt", "koneksi2.txt");
				SaveFile("src/Database/savedata2.txt");
				Pop_Up_Message("File successfully saved", 3);
				break;
		}
	}while(pilihan != 3);

	/* Delete dan Dealokasi */
	clear();
	refresh();
	delwin(slot1_Border);
	delwin(slot2_Border);
	delwin(Exit_Border);
	delwin(slot1);
	delwin(slot2);
	delwin(Exit);
}

void SaveFile(char *namafile)
/* I.S. namafile terdefinisi */
/* F.S. Game State tersimpan ke file dengan namafile */
{
	/* KAMUS LOKAL */
	FILE *fout;
	time_t t;
	int i;
	JAM now, PlayTime;

	/* ALGORITMA */
	GetCurrentJAM(&now);
	GetOldPlayTime(namafile, &PlayTime);
	SetJAM(&PlayTime, AddJAM(PlayTime, DetikToJAM(Durasi(T_Start,now))));
	time(&t);
	fout = fopen(namafile, "w");
	for(i = 1; i <= Name(P).Length; i++)
	{
		fprintf(fout, "%c", Name(P).TabKata[i]);	
	}
	fprintf(fout, "\n%d\n%s\n%d:%d:%d", Level(P), ctime(&t), Hour(PlayTime), Minute(PlayTime), Second(PlayTime));
	fprintf(fout, "%c", MARK);
	fclose(fout);
}

void GetOldPlayTime(char *namafile, JAM *J)
/* I.S. namafile terdefinisi, J sembarang */
/* F.S. J berisi playtime dari file dengan nama namafile */
{
	/* KAMUS LOKAL */
	int H, M, S;

	/* ALGORITMA */
	START(namafile);
	if(EOP)
	{
		*J = MakeJAM(0,0,0);
	}
	else
	{
		do
		{
			ADV();
		}while(CC != ENTER);
		ADV();
		do
		{
			ADV();
		}while(CC != ENTER);
		ADV();
		do
		{
			ADV();
		}while(CC != ENTER);
		ADV();
		H = 0;
		do
		{	
			H = H * 10 + (CC - '0');	
			ADV();
		}while(CC != ':');
		ADV();
		M = 0;
		do
		{	
			M = M * 10 + (CC - '0');	
			ADV();
		}while(CC != ':');
		ADV();
		S = 0;
		do
		{	
			S = S * 10 + (CC - '0');	
			ADV();
		}while(CC != MARK);
		*J = MakeJAM(H,M,S);
	}
}