/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada area.h */

#include "area.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */
/****************** KONSTRUKTOR ******************/
void CreateEmptyArea (Area *A)
/* I.S. A sembarang  */
/* F.S. Terbentuk Area kosong. Lihat definisi di atas. */
{
	/* ALGORITMA */
	*A = NilArea;
}

/****************** Manajemen Memori ******************/
addressArea AlokasiArea (infotypeArea X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, North(P)=Nil, South(P)=Nil, West(P)=Nil, East(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
	/* KAMUS LOKAL */
	addressArea P;
	int i;

	/* ALGORITMA */
	P = (addressArea) malloc(sizeof(ElmtArea));
	if(P != NilArea)
	{
		Info(P) = X;
		for(i = 1; i <= MaxNeighbour; i++)
		{
			Neighbour(P,i) = NilArea;	
		}
	}
	return P;
}

void DealokasiArea (addressArea P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	/* ALGORITMA */
	free(P);
}

/*** PENAMBAHAN ELEMEN ***/
void SetNeighbour (Area *A, Area P, int i)
/* I.S. A tidak kosong */
/* F.S. Area A dan Area P terhubung dengan North(A) = P */
{
	/* ALGORITMA */
	Neighbour(*A, i) = P; 
}

/*** Proses Current Area ***/
void PrintArea (Area A, POINT P)
/* I.S. A tidak kosong dan P (posisi Player) terdefinisi*/
/* F.S. Isi Info(A) dicetak dengan posisi di P diganti dengan 'P' */
{
	int i, j;
	for(i = GetFirstIdxBrs(Info(A)); i <= GetLastIdxBrs(Info(A)); i++)
	{
		for(j = GetFirstIdxKol(Info(A)); j <= GetLastIdxKol(Info(A)); j++)
		{
			if(Absis(P) == j && Ordinat(P) == i)
			{
				printf("P");
			}
			else
			{
				printf("%c", Elmt(Info(A),i,j));
			}
			if(j != GetLastIdxKol(Info(A)))
			{
				printf("  ");
			}
		}
		printf("\n\n");
	}
}

/*** I/O Khusus Ncurses ***/
void wPrintArea (WINDOW *win, Area A, POINT P)
/* I.S. A tidak kosong dan P terdefinisi*/
/* F.S. Isi Info(A) dicetak ke win dengan posisi di P diganti dengan 'P' */
{
	/* KAMUS LOKAL */
	int i, j, k;

	/* ALGORITMA */
	init_pair(2, COLOR_GREEN, COLOR_YELLOW);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	wattron(win, COLOR_PAIR(3));
	for(i = GetFirstIdxBrs(Info(A)); i <= GetLastIdxBrs(Info(A)); i++)
	{
		for(k = 1; k <= 3; k++)
		{
			for(j = GetFirstIdxKol(Info(A)); j <= GetLastIdxKol(Info(A)); j++)
			{
				if(k == 2)
				{
					if(Elmt(Info(A),i,j) == '#')
					{
						wattron(win, COLOR_PAIR(2));
						wprintw(win, "       ");
						wattroff(win, COLOR_PAIR(2));
					}
					else if(Absis(P) == j && Ordinat(P) == i)
					{
						wattron(win, COLOR_PAIR(3));
						wprintw(win, "   P   ");
						wattroff(win, COLOR_PAIR(3));
					}
					else
					{
						wattron(win, COLOR_PAIR(3));
						if(Elmt(Info(A),i,j) == '.')
						{
							wprintw(win, "       ");
						}
						else
						{
							wprintw(win, "   %c   ", Elmt(Info(A),i,j));
						}
						wattroff(win, COLOR_PAIR(3));
					}
				}
				else
				{
					if(Elmt(Info(A),i,j) == '#')
					{
						wattron(win, COLOR_PAIR(2));
						wprintw(win, "       ");
						wattroff(win, COLOR_PAIR(2));
					}
					else
					{
						wattron(win, COLOR_PAIR(3));
						wprintw(win, "       ");
						wattroff(win, COLOR_PAIR(3));
					}
				}
			}
		}
	}
}

/*** Operasi Lain pada Area ***/
void SetAreaPoint(Area *A)
/* I.S. Area A tidak kosong dan di keempat sisi A (atas, kanan, bawah, kiri) terdapat maksimal satu karakter '.' */
/* F.S. P_Neighbour(A, i) diisi dengan titik yang sesuai pada posisi i[1..4] yang sesuai */
/* Note : Prosedur khusus untuk area dengan jumlah tetangga maksimal 4 dengan lokasi tetangga di atas, kanan, bawah, kiri */
{
	/* KAMUS LOKAL */
	int i;
	boolean found;

	/* ALGORITMA */
	//Search North
	i = GetFirstIdxKol(Info(*A)); 	
	found = false;
	while((i <= GetLastIdxKol(Info(*A))) && (!found))
	{
		if(Elmt(Info(*A),GetFirstIdxBrs(Info(*A)),i) == '.')
		{
			found = true;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		P_Neighbour(*A, 1) = MakePOINT(i, GetFirstIdxBrs(Info(*A)));
	}

	//Search East
	i = GetFirstIdxBrs(Info(*A));		
	found = false;
	while((i <= GetLastIdxBrs(Info(*A))) && (!found))
	{
		if(Elmt(Info(*A),i,GetLastIdxKol(Info(*A))) == '.')
		{
			found = true;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		P_Neighbour(*A, 2) = MakePOINT(GetLastIdxKol(Info(*A)), i);
	}

	//Search South
	i = GetFirstIdxKol(Info(*A)); 
	found = false;
	while((i <= GetLastIdxKol(Info(*A))) && (!found))
	{
		if(Elmt(Info(*A),GetLastIdxBrs(Info(*A)),i) == '.')
		{
			found = true;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		P_Neighbour(*A, 3) = MakePOINT(i, GetLastIdxBrs(Info(*A)));
	}

	//Search West
	i = GetFirstIdxBrs(Info(*A));		
	found = false;
	while((i <= GetLastIdxBrs(Info(*A))) && (!found))
	{
		if(Elmt(Info(*A),i,GetFirstIdxKol(Info(*A))) == '.')
		{
			found = true;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		P_Neighbour(*A, 4) = MakePOINT(GetFirstIdxKol(Info(*A)), i);
	}
}

/*** TEST Daerah***/
boolean IsPassable(Area A, POINT P)
/* Menghasilkan true jika koordinat P pada Area A dapat dilewati dan false jika tidak */
{
	/* ALGORITMA */
	return (Elmt(Info(A), Ordinat(P), Absis(P)) != Wall);
}

boolean IsEnemy(Area A, POINT P)
/* Menghasilkan true jika koordinat P pada Area A adalah enemy dan false jika tidak */
{
	/* ALGORITMA */
	return (Elmt(Info(A), Ordinat(P), Absis(P)) == Musuh);
}

boolean IsMedicine(Area A, POINT P)
/* Menghasilkan true jika koordinat P pada Area A adalah medicine dan false jika tidak */
{
	/* ALGORITMA */
	return (Elmt(Info(A), Ordinat(P), Absis(P)) == Medicine);
}

boolean IsBoss(Area A, POINT P)
/* Menghasilkan true jika koordinat P pada Area A adalah boss dan false jika tidak */
{
	/* ALGORITMA */
	return (Elmt(Info(A), Ordinat(P), Absis(P)) == Boss);
}

void ClearPOINT(Area *A, POINT P)
/* I.S. A dan P terdefinisi */
/* F.S. koordinat P pada Area A diganti menjadi path */
{
	/* ALGORITMA */
	Elmt(Info(*A), Ordinat(P), Absis(P)) = Path;	
}