/* Nama file    : BrightSouls.c            			*/
/* Last Edited  : 12 November 2016         			*/

#include <ncurses.h>
#include "../MesinKarKata/mesinkar.h"
#include "../Peta/peta.h"
#include "../Enemy/enemy.h"
#include "../Player/player.h"
#include "../StackQueue/stackqueue.h"
#include "boolean.h"

/* DEKLARASI FUNGSI DAN PROSEDUR */
WINDOW *create_newwin(int height, int width, int starty, int startx);
/* Menghasilkan pointer to WINDOW dengan tinggi sebesar height, lebar sebesar width, posisi sumbu y dimulai dari starty, dan posisi sumbu x dimulai dari startx */
void print_menu(WINDOW *menu_win, int pilihan);
/* I.S. menu_win dan pilihan[1..4] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */
void main_menu(int *choice);
/* I.S. choice sembarang */
/* F.S. choice berisi pilihan user */
/* Proses: Menampilkan main menu dan menunggu sampai user menentukan pilihannya */
void delay(float s);
/* I.S. s terdefinisi */
/* F.S. Proses ditunda selama s second */

int main()
{
	int pilihan;
	initscr();
	cbreak();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	bkgd(COLOR_PAIR(1));
	curs_set(0);
	refresh();
	main_menu(&pilihan);
	switch(pilihan)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
	}
	endwin();
	return 0;
}

/* REALISASI FUNGSI DAN PROSEDUR */
WINDOW *create_newwin(int height, int width, int starty, int startx)
/* Menghasilkan pointer to WINDOW dengan tinggi sebesar height, lebar sebesar width, posisi sumbu y dimulai dari starty, dan posisi sumbu x dimulai dari startx */
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	wbkgd(local_win, COLOR_PAIR(1));
	return local_win;
}

void print_menu(WINDOW *menu_win, int pilihan)
/* I.S. menu_win dan pilihan[1..4] terdefinisi */
/* F.S. Menampilkan menu dengan pilihan ke-pilihan ditunjuk dengan '>' */
{
	int i;	
	char *choices[] = {"New Game","Start Game","Load Game","Exit"};

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

void main_menu(int *choice)
/* I.S. choice sembarang */
/* F.S. choice berisi pilihan user */
/* Proses: Menampilkan main menu dan menunggu sampai user menentukan pilihannya */
{
	WINDOW *title, *menu;
	int pilihan, ch;
	boolean chosen;
	title = create_newwin(29, 121, (LINES - 29)/2, (COLS - 121)/2);
	START("title.txt");
	wattron(title, COLOR_PAIR(1));
	while(!EOP)
	{
		wprintw(title, "%c", CC);
		wrefresh(title);
		delay(0.001);
		ADV();
	}
	wattroff(title, COLOR_PAIR(1)); 
	wrefresh(title);
	menu = create_newwin(4, 11,  (LINES - 29)/2 + 22, (COLS - 121)/2 + 95);
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
	delwin(menu);
	clear();
	refresh();
	*choice = pilihan;
}

void delay(float s)
/* I.S. s terdefinisi */
/* F.S. Proses ditunda selama s second */
{
	int i;
	for(i = 0; i < (100000000 * s); i++)
	{
	}
}