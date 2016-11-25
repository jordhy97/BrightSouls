/* Nama file    : BrightSouls.c            			*/
/* Last Edited  : 24 November 2016         			*/

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "../MesinKarKata/mesinkar.h"
#include "../MesinKarKata/mesinkata.h"
#include "../Peta/peta.h"
#include "../Player/player.h"
#include "../Shared/boolean.h"
#include "../Enemy/enemy.h"
#include "../Point/point.h"
#include "../Jam/jam.h"


#define Game_Height 29
#define Game_Width 121

/* DEKLARASI FUNGSI DAN PROSEDUR */

void print_menu(WINDOW *menu_win, int pilihan);
/* I.S. menu_win dan pilihan[1..4] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */

void New_Game(Player *P);
/* I.S. P dan MAP Sembarang */
/* F.S. Membuat player baru dengan nama dari input user atau tidak terbentuk apa-apa jika user membatalkan */

void Create_explore_border();
/* I.S. sembarang */
/* F.S. menampilkan ke layar border untuk mode eksplorasi */

void SelectEnemy(TabEn TEnemy, Enemy *En, int LvlP);
/* I.S. TEnemy terdefinisi, LvlP terdefinisi, En sembarang */
/* F.S. En berisi data enemy yang dirandom berdasarkan LvlP dari file eksternal */

void explore(Player *P, Peta *MAP, JAM *PlayTime);
/* I.S. P, MAP, dan PlayTime terdefinisi */
/* F.S. Melakukan mode eksplorasi */

void Create_battle_border();
/* I.S. sembarang */
/* F.S. menampilkan ke layar border untuk mode battle */

void battle(Player *P, Enemy En, boolean *game_over, boolean *win);
/* I.S. P dan En terdefinisi, game_over dan win sembarang */
/* F.S. Melakukan Mode battle dan setelah selesai game_over berisi false jika HP(P) > 0 dan true jika tidak, win berisi true jika menang dan false jika tidak */

int Damage (int str, int def,int base);
/*Prekondisi: Strength, defense, dan base untuk battle terdefinisi*/
/*Menghitung besarnya damage pada saat battle*/

void DisplaySkill(Player P);
/* I.S. P terdefinisi */
/* F.S. Menampilkan Skill yang sudah ter-unlock ke layar */

void Load(Player *P, Peta *MAP, JAM *PlayTime);
/* I.S. P, MAP, dan PlayTime Sembarang */ 
/* F.S. me-load pilihan user */

void Save(Player P, Peta MAP, JAM StartPlay, JAM PlayTime);
/* I.S. P, MAP, dan StartPlay terdefinisi */
/* F.S. P dan MAP tersimpan ke file eksternal */

void SaveFile(char *namafile, Player P, JAM StartPlay, JAM PlayTime);
/* I.S. namafile, P dan StartPlay terdefinisi */
/* F.S. Game State tersimpan ke file dengan namafile */

void Display_saveFile(WINDOW *win, char *namafile, boolean *empty);
/* I.S. win dan namafile terdefinisi, empty sembarang */
/* F.S. Menampilkan isi save file ke win, empty true jika file kosong dan false jika tidak */

void GetOldPlayTime(char *namafile, JAM *J);
/* I.S. namafile terdefinisi, J sembarang */
/* F.S. J berisi playtime dari file dengan nama namafile */

int Mid_y(int y);
/* Mengembalikan ordinat tengah terhadap sumbu y terminal dengan offset sebesar (-y/2) */

int Mid_x(int x);
/* Mengembalikan absis tengah terhadap sumbu x terminal dengan offset sebesar (-x/2) */

WINDOW *create_newwin(int height, int width, int starty, int startx);
/* Menghasilkan pointer to WINDOW dengan tinggi sebesar height, lebar sebesar width, posisi sumbu y dimulai dari starty, dan posisi sumbu x dimulai dari startx */

void delay(float s);
/* I.S. s terdefinisi */
/* F.S. Proses ditunda selama s second */

void Pop_Up_Message(char *message, float t);
/* I.S. Sembarang */
/* F.S. menampilkan Pop_up message selama t second */

void Loading_Screen();
/* I.S. Sembarang */
/* F.S. Menampilkan loading Screen */

void Game_Over();
/* I.S. Sembarang */
/* F.S. Menampilkan game over screen */

void Credits();
/* I.S. Sembarang */
/* F.S. Menampilkan credits screen */

/*** Not Yet impemented ***/
//void Tutorial_explore();
//void Tutorial_battle();
/*************************/

int main()
{
	/* KAMUS */
	WINDOW *title, *menu;
	int pilihan, ch;
	boolean chosen, quit;
	Player P;
	Peta MAP;
	boolean new;
	JAM PlayTime;
	/* ALGORITMA */
	
	/* Inisialisasi Variable */
	initscr();
	cbreak();
	noecho();
	/* SET COLOR */
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	refresh();
	curs_set(0);
	Name(P).Length = 0;
	IDEff(MAP) = 0;
	quit = false;
	new = false;

	/* Main Menu */
	title = create_newwin(Game_Height, Game_Width, Mid_y(Game_Height), Mid_x(Game_Width));
	menu = create_newwin(4, 11,  Mid_y(Game_Height) + 22, Mid_x(Game_Width) + 95);
	/* Load title screen */
	START("src/Database/Text/title.txt");
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
		curs_set(0);
		noecho();
		/* Refresh title screen */
		wmove(title,0,0);
		START("src/Database/Text/title.txt");
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
				clear();
				refresh();
				New_Game(&P);
				SetJAM(&PlayTime, MakeJAM(0, 0, 0));
				new = true;
				break;
			case 2:
				/* Start Game */
				if(!IsKataEmpty(Name(P)))
				{	
					if(new)
					{
						CreateRandomPeta(&MAP, "src/Database/Areas/Areas.txt");
					}
					Loading_Screen();
					explore(&P, &MAP, &PlayTime);
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
				Load(&P, &MAP, &PlayTime);
				new = false;
				break;
			case 4:
				/* Exit */
				quit = true;
				break;
		}
	}while(!quit);

	/* Delete dan Dealokasi */
	clear();
	refresh();
	delwin(title);
	delwin(menu);
	endwin();
	system("clear");
	return 0;
}

/* REALISASI FUNGSI DAN PROSEDUR */


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

void New_Game(Player *P)
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
	wCreatePlayer(menu, P, nama, &created, "src/Database/skill.txt");
	if(created)
	{
		Pop_Up_Message("Player successfully created", 3);
	}
	wclear(menu);
	wrefresh(menu);
	delwin(menu);
}


void Create_explore_border()
/* I.S. sembarang */
/* F.S. menampilkan ke layar border untuk mode eksplorasi */
{
	/* KAMUS LOKAL */
	WINDOW *P_Name_Border, *P_Lvl_Border, *P_HP_Border, *P_Str_Border, *P_Def_Border, *P_Exp_Border, *Message_Border, *Command_Border, *BatasKanan, *BatasKiri;
	int starty, startx;

	/* ALGORITMA */
	/* Set Position */
	starty = Mid_y(Game_Height);
	startx = Mid_x(Game_Width);

	/* Create window */
	BatasKanan = create_newwin(Game_Height,18,starty, startx + 103);
	Message_Border = create_newwin(3, 104, starty + 24, startx);
	BatasKiri = create_newwin(23, 19, starty + 2, startx);
	P_Name_Border = create_newwin(3, 19, starty, startx);
	P_Lvl_Border = create_newwin(3, 18, starty, startx + 18);
	P_HP_Border = create_newwin(3, 18, starty, startx + 35);
	P_Str_Border = create_newwin(3, 18, starty, startx + 52);
	P_Def_Border = create_newwin(3, 18, starty, startx + 69);
	P_Exp_Border = create_newwin(3, 18, starty, startx + 86);
	Command_Border = create_newwin(3, 104, starty + 26, startx);

	/* Create border */
	wborder(BatasKanan, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(Message_Border, 0, 0, 0, 0, 0, ACS_RTEE, 0, 0);
	wborder(BatasKiri, 0, 0, 0, 0, 0, 0, ACS_LTEE, ACS_BTEE);
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
	delwin(P_Name_Border);
	delwin(P_Lvl_Border);
	delwin(P_HP_Border);
	delwin(P_Str_Border);
	delwin(P_Def_Border);
	delwin(P_Exp_Border);
	delwin(Command_Border);
	
}

void SelectEnemy(TabEn TEnemy, Enemy *En, int LvlP)
/* I.S. TEnemy terdefinisi, LvlP terdefinisi, En sembarang */
/* F.S. En berisi data enemy yang dirandom berdasarkan LvlP dari file eksternal */
{
	/* KAMUS LOKAL */
	int chosen;
	char *path = "src/Database/Enemy/";
	char *txt = ".txt";
	char filename[100];
	int i, j;

	/* ALGORITMA */
	srand(time(NULL));
	chosen = rand() % LvlP + 1;
	i = 0;
	while(path[i] != '\0')
	{
		filename[i] = path[i];
		i++;
	}
	for(j = 1; j <= ElmtTabEn(TEnemy,chosen).Length; j++)
	{
		filename[i] = ElmtTabEn(TEnemy,chosen).TabKata[j];
		i++;
	}
	j = 0;
	while(txt[j] != '\0')
	{
		filename[i] = txt[j];
		j++;
		i++;
	}
	filename[i] = '\0';
	LoadFileEnemy(En, filename, 'e');
}

void explore(Player *P, Peta *MAP, JAM *PlayTime)
/* I.S. P, MAP, dan PlayTime terdefinisi */
/* F.S. Melakukan mode eksplorasi */
{
	/* KAMUS LOKAL */
	WINDOW *P_Name, *P_Lvl, *P_HP, *P_Str, *P_Def, *P_Exp, *Message, *Command, *Map;
	int starty, startx;
	Kata Masukan, GU, GR, GD, GL, SKILL, SAVE, LOAD, EXIT;
	POINT NextPOINT;
	boolean move, quit, win, game_over, end;
	TabEn TEnemy;
	Enemy En;
	Area START, CurrArea;
	JAM StartPlay;
	/* ALGORITMA */

	/* Inisialasi */
	CurrArea = SubPeta(*MAP,CArea(*P));
	START = AlokasiArea(Info(CurrArea));
	LoadNamaEnemy(&TEnemy, "src/Database/Enemy/enemy.txt");
	GetCurrentJAM(&StartPlay);
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
	wTulisKata(P_Name, Name(*P));
	wprintw(P_Lvl, "LVL: %d", Level(*P)); 
	wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P)); 
	wprintw(P_Str, "STR: %d", Strength(*P)); 
	wprintw(P_Def, "DEF: %d", Defense(*P));
	wprintw(P_Exp, "EXP: %d", Exp(*P));

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
	end = false;
	do
	{
		move = true;
		wclear(Map);
		wPrintArea(Map, START, Position(*P));
		wrefresh(Map);
		wrefresh(Message);
		wclear(Command);
		wprintw(Command, "Command: "); 
		wrefresh(Command);
		wBacaKata(Command,&Masukan);
		wclear(Message);
		if(IsKataSama(Masukan, GU))
		{
			if(IsPassable(START, PlusDelta(Position(*P), 0, -1)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(*P), 0, -1));
			}
		}
		else if(IsKataSama(Masukan, GR))
		{
			if(IsPassable(START, PlusDelta(Position(*P), 1, 0)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(*P), 1, 0));
			}
		}
		else if(IsKataSama(Masukan, GD))
		{
			if(IsPassable(START, PlusDelta(Position(*P), 0, 1)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(*P), 0, 1));
			}
		}
		else if(IsKataSama(Masukan, GL))
		{
			if(IsPassable(START, PlusDelta(Position(*P), -1, 0)))
			{
				SetPOINT(&NextPOINT, PlusDelta(Position(*P), -1, 0));
			}
		}
		else if(IsKataSama(Masukan, SKILL))
		{
			//DisplaySkill
			clear();
			refresh();
			curs_set(0);
			DisplaySkill(*P);
			move = false;
			Create_explore_border();
			wclear(P_Lvl);
			wclear(P_HP);
			wclear(P_Str);
			wclear(P_Def);
			wclear(P_Exp);
			wprintw(P_Lvl, "LVL: %d", Level(*P)); 
			wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P)); 
			wprintw(P_Str, "STR: %d", Strength(*P)); 
			wprintw(P_Def, "DEF: %d", Defense(*P));
			wprintw(P_Exp, "EXP: %d", Exp(*P));;
			wrefresh(P_Lvl);
			wrefresh(P_HP);
			wrefresh(P_Str);
			wrefresh(P_Def);
			wrefresh(P_Exp);
			curs_set(1);
		}
		else if(IsKataSama(Masukan, SAVE))
		{
			/* SAVE */
			clear();
			refresh();
			curs_set(0);
			Save(*P, *MAP, StartPlay, *PlayTime);
			move = false;
			Create_explore_border();
			wclear(P_Lvl);
			wclear(P_HP);
			wclear(P_Str);
			wclear(P_Def);
			wclear(P_Exp);
			wprintw(P_Lvl, "LVL: %d", Level(*P)); 
			wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P)); 
			wprintw(P_Str, "STR: %d", Strength(*P)); 
			wprintw(P_Def, "DEF: %d", Defense(*P));
			wprintw(P_Exp, "EXP: %d", Exp(*P));;
			wrefresh(P_Lvl);
			wrefresh(P_HP);
			wrefresh(P_Str);
			wrefresh(P_Def);
			wrefresh(P_Exp);
			curs_set(1);
		}
		else if(IsKataSama(Masukan, LOAD))
		{
			/* LOAD */
			clear();
			refresh();
			curs_set(0);
			Load(P, MAP, PlayTime);
			GetCurrentJAM(&StartPlay);
			CurrArea = SubPeta(*MAP,CArea(*P));
			START = AlokasiArea(Info(CurrArea));
			move = false;
			Create_explore_border();
			wclear(P_Lvl);
			wclear(P_HP);
			wclear(P_Str);
			wclear(P_Def);
			wclear(P_Exp);
			wprintw(P_Lvl, "LVL: %d", Level(*P)); 
			wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P)); 
			wprintw(P_Str, "STR: %d", Strength(*P)); 
			wprintw(P_Def, "DEF: %d", Defense(*P));
			wprintw(P_Exp, "EXP: %d", Exp(*P));;
			wrefresh(P_Lvl);
			wrefresh(P_HP);
			wrefresh(P_Str);
			wrefresh(P_Def);
			wrefresh(P_Exp);
			curs_set(1);
		}
		else if(IsKataSama(Masukan, EXIT))
		{
			quit = true;
			move = false;
		}
		else
		{
			wprintw(Message, "Invalid Command!");  
			move = false;
		}
		if(move)
		{
			if(IsEnemy(START, NextPOINT))
			{
				/* BATTLE */
				SelectEnemy(TEnemy, &En, Level(*P));
				win = false;
				clear();
				refresh();
				Loading_Screen();
				battle(P, En, &game_over, &win);
				if(!game_over)
				{
					Loading_Screen();
					Create_explore_border();
					ClearPOINT(&START, Position(*P));
					wclear(P_Lvl);
					wclear(P_HP);
					wclear(P_Str);
					wclear(P_Def);
					wclear(P_Exp);
					wprintw(P_Lvl, "LVL: %d", Level(*P)); 
					wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P)); 
					wprintw(P_Str, "STR: %d", Strength(*P)); 
					wprintw(P_Def, "DEF: %d", Defense(*P));
					wprintw(P_Exp, "EXP: %d", Exp(*P));;
					wrefresh(P_Lvl);
					wrefresh(P_HP);
					wrefresh(P_Str);
					wrefresh(P_Def);
					wrefresh(P_Exp);
					if(win)
					{
						SetPOINT(&Position(*P), NextPOINT);
					}
				}
				curs_set(1);
			}
			else
			{
				SetPOINT(&Position(*P), NextPOINT);
			}
			if(IsBoss(START, NextPOINT))
			{
				/* BATTLE */
				LoadFileEnemy(&En, "src/Database/Enemy/boss.txt",'b');
				win = false;
				clear();
				refresh();
				Loading_Screen();
				battle(P, En, &game_over, &win);
				if(win)
				{
					end = true;
				}
			}
			if(IsMedicine(START, Position(*P)))
			{
				ClearPOINT(&START, Position(*P));
				ClearPOINT(&CurrArea, Position(*P));
				wprintw(Message, "Got a medicine! HP +%d", Max_HP(*P) - HP(*P));
				HP(*P) = Max_HP(*P);
				wclear(P_HP);
				wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P)); 
				wrefresh(P_HP);
			}
			/* Changing Area */
			if((Ordinat(Position(*P)) < GetFirstIdxBrs(Info(START))) || (Absis(Position(*P)) > GetLastIdxKol(Info(START))) || (Ordinat(Position(*P)) > GetLastIdxBrs(Info(START))) || (Absis(Position(*P)) < GetFirstIdxKol(Info(START))))
			{	
				if(Ordinat(Position(*P)) < GetFirstIdxBrs(Info(START)))
				{
					CArea(*P) = Koneksi(*MAP, CArea(*P), 1);
					CurrArea = Neighbour(CurrArea, 1);
					SetPOINT(&Position(*P), P_Neighbour(CurrArea, 3));
					DealokasiArea(START);
					START = AlokasiArea(Info(CurrArea));

				}
				else if(Absis(Position(*P)) > GetLastIdxKol(Info(START)))
				{
					CArea(*P) = Koneksi(*MAP, CArea(*P), 2);
					CurrArea = Neighbour(CurrArea, 2);
					SetPOINT(&Position(*P), P_Neighbour(CurrArea, 4));
					DealokasiArea(START);
					START = AlokasiArea(Info(CurrArea));
				}
				else if(Ordinat(Position(*P)) > GetLastIdxBrs(Info(START)))
				{
					CArea(*P) = Koneksi(*MAP, CArea(*P), 3);
					CurrArea = Neighbour(CurrArea, 3);
					SetPOINT(&Position(*P), P_Neighbour(CurrArea, 1));
					DealokasiArea(START);
					START = AlokasiArea(Info(CurrArea));
				}
				else if(Absis(Position(*P)) < GetFirstIdxKol(Info(START)))
				{
					CArea(*P) = Koneksi(*MAP, CArea(*P), 4);
					CurrArea = Neighbour(CurrArea, 4);
					SetPOINT(&Position(*P), P_Neighbour(CurrArea, 2));
					DealokasiArea(START);
					START = AlokasiArea(Info(CurrArea));
				}
				clear();
				refresh();
				Loading_Screen();
				Create_explore_border();
				wclear(P_Lvl);
				wclear(P_HP);
				wclear(P_Str);
				wclear(P_Def);
				wclear(P_Exp);
				wprintw(P_Lvl, "LVL: %d", Level(*P)); 
				wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P)); 
				wprintw(P_Str, "STR: %d", Strength(*P)); 
				wprintw(P_Def, "DEF: %d", Defense(*P));
				wprintw(P_Exp, "EXP: %d", Exp(*P));;
				wrefresh(P_Lvl);
				wrefresh(P_HP);
				wrefresh(P_Str);
				wrefresh(P_Def);
				wrefresh(P_Exp);
				curs_set(1);
			}
		}
	}while(!quit && !game_over && !end);
	if(game_over)
	{
		Game_Over();
		Credits();
	}
	if(end)
	{
		Credits();
	}
	delwin(Command);
	delwin(Message);
	delwin(Map);
	delwin(P_Name);
	delwin(P_Lvl);
	delwin(P_HP);
	delwin(P_Str);
	delwin(P_Def);
	delwin(P_Exp);
	DealokasiPeta(MAP);
	Name(*P).Length = 0;
	DealokTree(&Skill(*P)); 
}

void Create_battle_border()
{

	/* KAMUS LOKAL */
	WINDOW *Message_Border, *E_Name_Border, *E_HP_Border, *E_Command_Border;
	WINDOW *P_Name_Border, *P_Lvl_Border, *P_HP_Border, *P_Str_Border, *P_Def_Border, *P_Exp_Border, *Round_Border; 
	WINDOW *P_Command_Border, *Inserted_Command_Border;
	int starty, startx;

	/* ALGORITMA */
	/* Set Position */
	starty = Mid_y(14);
	startx = Mid_x(Game_Width);
	
	/* Create Window */
	Message_Border = create_newwin(6, Game_Width, starty + 4, startx);
	E_Name_Border = create_newwin(3, 19, starty + 2, startx);
	E_HP_Border = create_newwin(3, 18, starty + 2, startx + 18);
	E_Command_Border = create_newwin(3, 86, starty + 2, startx + 35);
	P_Name_Border = create_newwin(3, 19, starty, startx);
	P_Lvl_Border = create_newwin(3, 18, starty, startx + 18);
	P_HP_Border = create_newwin(3, 18, starty, startx + 35);
	P_Str_Border = create_newwin(3, 18, starty, startx + 52);
	P_Def_Border = create_newwin(3, 18, starty, startx + 69);
	P_Exp_Border = create_newwin(3, 18, starty, startx + 86);
	Round_Border = create_newwin(3,18,starty, startx + 103);
	Inserted_Command_Border = create_newwin(3, Game_Width, starty + 9, startx);
	P_Command_Border = create_newwin(3, Game_Width, starty + 11, startx);
	
	/* Create border */
	wborder(Message_Border, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(E_Name_Border, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(E_HP_Border, 0, 0, 0, 0, 0, 0, ACS_BTEE, ACS_BTEE);
	wborder(E_Command_Border, 0, 0, 0, 0, 0, 0, ACS_BTEE, ACS_RTEE);
	wborder(P_Name_Border, 0, 0, 0, 0, 0, 0, ACS_LTEE, 0);
	wborder(P_Lvl_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_PLUS, 0);;
	wborder(P_HP_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_PLUS, 0);
	wborder(P_Str_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Def_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, 0);
	wborder(P_Exp_Border, 0, 0, 0, 0, ACS_TTEE, ACS_TTEE, ACS_BTEE, ACS_RTEE);
	wborder(Round_Border, 0, 0, 0, 0, ACS_TTEE, 0, ACS_BTEE, ACS_RTEE);
	wborder(Inserted_Command_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
	wborder(P_Command_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
	
	/* Display */
	wrefresh(Message_Border);
	wrefresh(E_Name_Border);
	wrefresh(E_HP_Border);
	wrefresh(E_Command_Border);
	wrefresh(P_Name_Border);
	wrefresh(P_Lvl_Border);
	wrefresh(P_HP_Border);
	wrefresh(P_Str_Border);
	wrefresh(P_Def_Border);
	wrefresh(P_Exp_Border);
	wrefresh(Round_Border);
	wrefresh(Inserted_Command_Border);
	wrefresh(P_Command_Border);
	
	/* Dealokasi */
	delwin(Message_Border);
	delwin(E_Name_Border);
	delwin(E_HP_Border);
	delwin(E_Command_Border);
	delwin(P_Name_Border);
	delwin(P_Lvl_Border);
	delwin(P_HP_Border);
	delwin(P_Str_Border);
	delwin(P_Def_Border);
	delwin(P_Exp_Border);
	delwin(Round_Border);
	delwin(Inserted_Command_Border);
	delwin(P_Command_Border);
}


void battle(Player *P, Enemy En, boolean *game_over, boolean *win)
/* I.S. P dan En terdefinisi, game_over dan win sembarang */
/* F.S. Melakukan Mode battle dan setelah selesai game_over berisi false jika HP(P) > 0 dan true jika tidak, win berisi true jika menang dan false jika tidak */
{
	/* KAMUS LOKAL */
	WINDOW *P_Name, *P_Lvl, *P_HP, *P_Str, *P_Def, *P_Exp, *Round, *E_Name, *E_HP, *E_Command, *Message, *P_Command, *Inserted_Command;
	int starty, startx, RoundNow, close1, close2, action, base, i, enemyhp, oldstr, olddef, oldmax_hp;
	ElmtStack QMusuh, QPemain, CurrQMusuh, CurrQPemain;
	Kata input, E, F, A, B;
	boolean aliveP, aliveE;
	char temp,player,enemy;

	/* ALGORITMA */
	/* Create border */
	Create_battle_border();

	/* Set Position */
	starty = Mid_y(14);
	startx = Mid_x(Game_Width);

	/* Create window */
	Message = create_newwin(4, Game_Width - 2, starty + 5, startx + 1);
	E_Name = create_newwin(1, 17, starty + 3, startx + 1);
	E_HP = create_newwin(1, 16, starty + 3, startx + 19);
	E_Command = create_newwin(1, 84, starty + 3, startx + 36);
	P_Name = create_newwin(1, 17, starty + 1, startx + 1);
	P_Lvl = create_newwin(1, 16, starty + 1, startx + 19);
	P_HP = create_newwin(1, 16, starty + 1, startx + 36);
	P_Str = create_newwin(1, 16, starty + 1, startx + 53);
	P_Def = create_newwin(1, 16, starty + 1, startx + 70);
	P_Exp = create_newwin(1, 16, starty + 1, startx + 87);
	Round = create_newwin(1,16, starty + 1, startx + 104);
	Inserted_Command = create_newwin(1, Game_Width - 2, starty + 10, startx + 1);
	P_Command = create_newwin(1, Game_Width - 2, starty + 12, startx + 1);
	
	/* Display */
	wmove(P_Name, 0, 0);
	wTulisKata(P_Name, Name(*P));
	wprintw(P_Lvl, "LVL: %d", Level(*P)); 
	wprintw(P_Str, "STR: %d", Strength(*P)); 
	wprintw(P_Def, "DEF: %d", Defense(*P));
	wprintw(P_Exp, "EXP: %d", Exp(*P));
	wmove(E_Name, 0, 0);
	wTulisKata(E_Name, e_name(En));
	wrefresh(P_Name);
	wrefresh(P_Lvl);
	wrefresh(P_Str);
	wrefresh(P_Def);
	wrefresh(P_Exp);
	wrefresh(E_Name);
	wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P));
	wrefresh(P_HP);
	wprintw(E_HP, "HP: %d", e_hp(En));
	wrefresh(E_HP);
	curs_set(0);
	scrollok(Message, TRUE);
	wTulisKata(Message, e_name(En));
	wprintw(Message," Attacked!");
	wrefresh(Message);
	if ((Level(*P)>=1) && (Level(*P)<=10))
		{
			base = 1;
	}
	else
	{
		base = 2;
	}
	CreateKata(&E, "E");
	CreateKata(&F, "F");
	CreateKata(&A, "A");
	CreateKata(&B, "B");
	aliveE = true;
	aliveP = true;
	RoundNow = 0;
	enemyhp = e_hp(En);

	echo();
	/* BATTLE STARTS */
	srand(time(NULL));
	do
	{	
		curs_set(1);
		RoundNow++;
		wclear(Round);
		wprintw(Round, "Round %d", RoundNow);
		wrefresh(Round);
		AttackEnemy(&En, &QMusuh);
		close1 = rand() % 4 + 1;
		close2 = rand() % 4 + 1;
		while (close1 == close2) 
		{
			close1 = rand() % 4 + 1;
			close2 = rand() % 4 + 1;
		} 
		wclear(Inserted_Command);
		wprintw(Inserted_Command, "Inserted Commands:  _ _ _ _");
		wrefresh(Inserted_Command);
		wclear(E_Command);
		wprintw(E_Command, "Command: ");
		wPrintQueueBattleE(E_Command, QMusuh , 0, close1, close2);
		wrefresh(E_Command);
		echo();
		CreateEmptyQ(&QPemain);
		wprintw(Message,"\nPlease input your command!");
		wrefresh(Message);
		do
		{
			wclear(P_Command);
			wprintw(P_Command, "Commands:           ");
			wrefresh(P_Command);
			wBacaKata(P_Command, &input);
			if ((!IsKataSama(input, E)) && (!IsKataSama(input, A)) && (!IsKataSama(input, B))&& (!IsKataSama(input, F)))
			{
				do
				{
					wprintw(Message, "\nInvalid Command");
					wrefresh(Message);
					wclear(P_Command);
					wprintw(P_Command, "Commands:           ");
					wrefresh(P_Command);
					wBacaKata(P_Command, &input);
				}while((!IsKataSama(input, E)) && (!IsKataSama(input, A)) && (!IsKataSama(input, B))&& (!IsKataSama(input, F)));
			}
			if (IsKataSama(input, E))
			{
				if (!IsEmptyQ(QPemain))
				{
					for (i = 1; i <= (NBElmtQ(QPemain)-1); i++)
					{
						Del(&QPemain,&temp);
						Add(&QPemain,temp);
					}
					Del(&QPemain,&temp);
				}
			}
			else
			{
				if (!IsFullQ(QPemain))
				{
					Add(&QPemain,input.TabKata[1]);
				}
			}
			wclear(Inserted_Command);
			wprintw(Inserted_Command, "Inserted Commands:  _ _ _ _");
			wmove(Inserted_Command, 0, 20);
			wPrintQueueBattleP(Inserted_Command, QPemain, 0);
			wrefresh(Inserted_Command);
		}while(NBElmtQ(QPemain) < 4);	
		CreateEmptyQ(&CurrQPemain);
		CreateEmptyQ(&CurrQMusuh);
		CurrQPemain = QPemain;
		CurrQMusuh = QMusuh;

		/*dequeue*/
		action = 1;
		do
		{
			curs_set(0);
			Del(&CurrQPemain,&player);
			Del(&CurrQMusuh	,&enemy);
			wclear(E_Command);
			wprintw(E_Command, "Command: ");
			wPrintQueueBattleE(E_Command, QMusuh , action, close1, close2);
			wrefresh(E_Command);
			wclear(Inserted_Command);
			wprintw(Inserted_Command, "Inserted Commands:  _ _ _ _");
			wmove(Inserted_Command, 0, 20);
			wPrintQueueBattleP(Inserted_Command, QPemain, action);
			wrefresh(Inserted_Command);
			if (((player == 'A') || (player == 'F')) && (player == enemy)) 
			{
				e_hp(En) = e_hp(En) - ((Damage(Strength(*P),e_def(En),base))/2);
				HP(*P) = HP(*P) - ((Damage(e_str(En),Defense(*P),base))/2);
				wprintw(Message, "\nBalanced! ");
				wTulisKata(Message, e_name(En)); 
				wprintw(Message, "'s HP -%d! ",((Damage(Strength(*P),e_def(En),base))/2));
				wTulisKata(Message, Name(*P)); 
				wprintw(Message, "'s HP -%d!",((Damage(e_str(En),Defense(*P),base))/2));
			}
			else if ((player == 'B') && (player == enemy))
			{
				wprintw(Message, "\nBalanced!");
			}
			else if ((player == 'B') && (enemy == 'A'))
			{
					wprintw(Message, "\n");
					wTulisKata(Message, e_name(En));
					wprintw(Message, " attacks ");
					wTulisKata(Message, Name(*P)); 
					wprintw(Message, ", but it's blocked!");
			}
			else if ((player == 'A') && (enemy == 'B'))
			{
					wprintw(Message, "\n");
					wTulisKata(Message, Name(*P));
					wprintw(Message, " attacks ");
					wTulisKata(Message, e_name(En)); 
					wprintw(Message, ", but it's blocked!");
			} 
			else if ((player == 'F') && (enemy == 'B'))
			{
					e_hp(En) = e_hp(En) - Damage(Strength(*P),e_def(En),base);
					wprintw(Message, "\n");
					wTulisKata(Message, Name(*P));
					wprintw(Message, " flanks ");
					wTulisKata(Message, e_name(En));
					wprintw(Message, "! ");
					wTulisKata(Message, e_name(En));
					wprintw(Message, "'s HP -%d!",Damage(Strength(*P),e_def(En),base));
			}
			else if ((player == 'B') && (enemy == 'F'))
			{
					HP(*P) = HP(*P) - Damage(e_str(En),Defense(*P),base);
					wprintw(Message, "\n");
					wTulisKata(Message, e_name(En));
					wprintw(Message, " flanks ");
					wTulisKata(Message, Name(*P)); 
					wprintw(Message, "! ");
					wTulisKata(Message, Name(*P));
					wprintw(Message, "'s HP -%d!",Damage(e_str(En),Defense(*P),base));
			}
			else if ((player == 'A') && (enemy == 'F'))
			{
					e_hp(En) = e_hp(En) - Damage(Strength(*P),e_def(En),base);
					if (e_hp(En) < 0)
					{
						e_hp(En) = 0;
					}
					wprintw(Message, "\n");
					wTulisKata(Message, Name(*P));
					wprintw(Message, " attacks ");
					wTulisKata(Message, e_name(En));
					wprintw(Message, "! ");
					wTulisKata(Message, e_name(En));
					wprintw(Message, "'s HP -%d!",Damage(Strength(*P),e_def(En),base));
			}
			else if ((player == 'F') && (enemy == 'A'))
			{
					HP(*P) = HP(*P) - Damage(e_str(En),Defense(*P),base);
					wprintw(Message, "\n");
					wTulisKata(Message, e_name(En));
					wprintw(Message, " attacks ");
					wTulisKata(Message, Name(*P));
					wprintw(Message, "! ");
					wTulisKata(Message, Name(*P));
					wprintw(Message, "'s HP -%d!",Damage(e_str(En),Defense(*P),base));
			}
			if (e_hp(En) <= 0)
			{
				e_hp(En) = 0;
				aliveE = false;
			}
			else if (HP(*P) <= 0)
			{
				HP(*P) = 0;
				aliveP = false;
			}
			else
			{
				action++;
			}
			wclear(P_HP);
			wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P));
			wrefresh(P_HP);
			wclear(E_HP);
			wprintw(E_HP, "HP: %d", e_hp(En));
			wrefresh(E_HP);
			wrefresh(Message);
			delay(3);
		}while((action <= 4) && (aliveE) && (aliveP));
	}while((!IsEmptyS(e_attack(En))) && (aliveE) && (aliveP));
	if ((aliveP) && (aliveE))
	{
		*game_over = false;
		if (e_hp(En) >= (enemyhp/2))
		{	
			*win = false;
			wprintw(Message, "\nYou got away!");
		}
		else
		{
			*win = true;
			wprintw(Message, "\n");
			wTulisKata(Message, e_name(En)); 
			wprintw(Message, " escaped!");
		}
	}
	else if ((aliveP) && (!aliveE))
	{
		*win = true;
		*game_over = false;
		wprintw(Message, "\nYou win!");
		wrefresh(Message);
		delay(3);
		Exp(*P) = Exp(*P) + e_exp(En);
		wprintw(Message, "\nYou earned %d experience points!",(((enemyhp - e_hp(En))*e_exp(En)) / enemyhp));
		wrefresh(Message);
		wclear(P_Exp);
		wprintw(P_Exp, "EXP: %d", Exp(*P));
		wrefresh(P_Exp);
		delay(3);
		if(IsLevelUp(*P))
		{
			wprintw(Message, "\nLevel Up!");
			wrefresh(Message);
			oldstr = Strength(*P);
			olddef = Defense(*P);
			oldmax_hp = Max_HP(*P);
			LevelUp(P);
			wclear(P_Lvl);
			wprintw(P_Lvl, "LVL: %d", Level(*P)); 
			wrefresh(P_Lvl);
			delay(3); 
			wclear(P_Str);
			wprintw(P_Str, "STR: %d", Strength(*P));
			wrefresh(P_Str);
			wprintw(Message, "\nSTR +%d", Strength(*P) - oldstr);
			wrefresh(Message);
			delay(3); 
			wclear(P_Def);
			wprintw(P_Def, "DEF: %d", Defense(*P));
			wrefresh(P_Def);
			wprintw(Message, "\nDEF +%d", Defense(*P) - olddef);
			wrefresh(Message);
			delay(3); 
			wclear(P_HP);
			wprintw(P_HP, "HP: %d/%d", HP(*P), Max_HP(*P));
			wrefresh(P_HP);
			wprintw(Message, "\nMAX HP +%d", Max_HP(*P) - oldmax_hp);
			curs_set(0);
		}
	}
	else
	{
		*win = false;
		*game_over = true;
		wprintw(Message, "\nYou lose!");
	}
	wrefresh(Message);
	delay(4);
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

int Damage (int str, int def,int base)
/*Prekondisi: Strength, defense, dan base untuk battle terdefinisi*/
/*Menghitung besarnya damage pada saat battle*/
{
	if (str>=(def/2))
	{
		return (base+(str-(def/2)));
	}
	else
	{
		return base;
	}
}

void DisplaySkill(Player P)
/* I.S. P terdefinisi */
/* F.S. Menampilkan Skill yang sudah ter-unlock ke layar */
{
	/* KAMUS LOKAL */
	WINDOW *win, *border;

	/* ALGORITMA */
	border = create_newwin(Game_Height, Game_Width, Mid_y(Game_Height), Mid_x(Game_Width));
	win = create_newwin(Game_Height - 2, Game_Width - 2, Mid_y(Game_Height) + 1, Mid_x(Game_Width) + 1);
	wborder(border, 0, 0, 0, 0, 0, 0, 0, 0);
	wprintw(win, "Skill List\n\n");
	wPrintTree(win, Skill(P), 0, 3);
	mvwprintw(win, 26, 0, "Press Any KEY to EXIT");
	wrefresh(border);
	wrefresh(win);
	wgetch(win);
	clear();
	refresh();
	delwin(border);
	delwin(win);
}

void Load(Player *P, Peta *MAP, JAM *PlayTime)
/* I.S. P, MAP, dan PlayTime Sembarang */ 
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
	Display_saveFile(slot1, "src/Database/State/savedata1.txt", &empty1);
	Display_saveFile(slot2, "src/Database/State/savedata2.txt", &empty2);	

	/* Choosing Save File */
	keypad(Exit, TRUE);
	pilihan = 1;
	chosen = false;
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
			LoadPlayer(P, "src/Database/State/player1.txt", "src/Database/State/skill1.txt");
			/* Dealokasi current peta */
			DealokasiPeta(MAP);
			LoadPeta(MAP,"src/Database/State/subpeta1.txt", "src/Database/State/koneksi1.txt");
			GetOldPlayTime("src/Database/State/savedata1.txt", PlayTime);
			Pop_Up_Message("File successfully loaded", 3);
			break;
		case 2:
			LoadPlayer(P, "src/Database/State/player2.txt", "src/Database/State/skill2.txt");
			/* Dealokasi current peta */
			DealokasiPeta(MAP);
			LoadPeta(MAP,"src/Database/State/subpeta2.txt", "src/Database/State/koneksi2.txt");
			GetOldPlayTime("src/Database/State/savedata2.txt", PlayTime);
			Pop_Up_Message("File successfully loaded", 3);
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

void Save(Player P, Peta MAP, JAM StartPlay, JAM PlayTime)
/* I.S. P, MAP, dan StartPlay terdefinisi */
/* F.S. P dan MAP tersimpan ke file eksternal */
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
	do
	{
		/* Reading from external files */
		chosen = false;
		Display_saveFile(slot1, "src/Database/State/savedata1.txt", &empty1);
		Display_saveFile(slot2, "src/Database/State/savedata2.txt", &empty2);	
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
				SavePlayer(P, "src/Database/State/player1.txt", "src/Database/State/skill1.txt");
				SavePeta(MAP,"src/Database/State/subpeta1.txt", "src/Database/State/koneksi1.txt");
				SaveFile("src/Database/State/savedata1.txt", P, StartPlay, PlayTime);
				Pop_Up_Message("File successfully saved", 3);
				break;
			case 2:
				SavePlayer(P, "src/Database/State/player2.txt", "src/Database/State/skill2.txt");
				SavePeta(MAP,"src/Database/State/subpeta2.txt", "src/Database/State/koneksi2.txt");
				SaveFile("src/Database/State/savedata2.txt", P, StartPlay, PlayTime);
				Pop_Up_Message("File successfully saved", 3);
				break;
		}
		/* Create border */
		wborder(slot1_Border, 0, 0, 0, 0, 0, 0, 0, 0);
		wborder(slot2_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
		wborder(Exit_Border, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);

		/* Display */
		wrefresh(slot1_Border);
		wrefresh(slot2_Border);
		wrefresh(Exit_Border);	
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

void SaveFile(char *namafile, Player P, JAM StartPlay, JAM PlayTime)
/* I.S. namafile, P dan StartPlay terdefinisi */
/* F.S. Game State tersimpan ke file dengan namafile */
{
	/* KAMUS LOKAL */
	FILE *fout;
	time_t t;
	int i;
	JAM now;

	/* ALGORITMA */
	GetCurrentJAM(&now);
	SetJAM(&PlayTime, AddJAM(PlayTime, DetikToJAM(Durasi(StartPlay,now))));
	time(&t);
	fout = fopen(namafile, "w");
	for(i = 1; i <= Name(P).Length; i++)
	{
		fprintf(fout, "%c", Name(P).TabKata[i]);	
	}
	fprintf(fout, "\n%d\n%s%d:%d:%d", Level(P), ctime(&t), Hour(PlayTime), Minute(PlayTime), Second(PlayTime));
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

void Loading_Screen()
/* I.S. Sembarang */
/* F.S. Menampilkan loading Screen */
{
	/* KAMUS LOKAL */
	char *loading = "Now Loading...";
	WINDOW *win;
	int i, j, ulang;

	/* ALGORITMA */
	curs_set(0);

	win = create_newwin(Game_Height, Game_Width, Mid_y(Game_Height), Mid_x(Game_Width));
	srand(time(NULL));
	ulang = rand() % 2 + 1;
	for(j = 1; j <= ulang; j++)
	{
		i = 0;
		START("src/Database/Text/title.txt");
		while(!EOP)
		{
			wprintw(win, "%c", CC);
			ADV();
		}
		wrefresh(win);
		wmove(win, Game_Height - 1, Game_Width - 15);
		while (loading[i] != '\0')
		{
			wprintw(win, "%c", loading[i]);
			wrefresh(win);
			delay(0.25);
			i++;
		}
		wclear(win);
	}
	clear();
	refresh();
	delwin(win);
}

void Game_Over()
/* I.S. Sembarang */
/* F.S. Menampilkan game over screen */
{
	/* KAMUS LOKAL */
	WINDOW *win;

	/* ALGORITMA */
	curs_set(0);

	win = create_newwin(18, 76, Mid_y(18), Mid_x(76));
	START("src/Database/Text/GameOver.txt");
	while(!EOP)
	{
		wprintw(win, "%c", CC);
		delay(0.001);
		wrefresh(win);
		ADV();
	}
	wrefresh(win);
	delay(5);
	clear();
	refresh();
	delwin(win);
}

void Credits()
/* I.S. Sembarang */
/* F.S. Menampilkan credits screen */
{

}