/* Deskripsi    : Realisasi/ kode program dari semua prototype yg didefinisikan pada peta.h */

#include "peta.h"
#include "../MesinKarKata/mesinkar.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

ID GetLastID (Peta P)
/* Mengirimkan ID terbesar P */
{
	/* ALGORITMA */
	return (IDEff(P) + IDMin - 1);
}	

/****************** KONSTRUKTOR (VIA FILE EKSTERNAL) ******************/
void CreateRandomPeta(Peta *PHasil, char *namafileAreas)
/* I.S. PHasil sembarang, file dengan nama namafileAreas terdefinisi dan siap dibaca */
/* F.S. PHasil berisi Peta yang dikonstruksi dari file Area dengan nama namafile yang dibentuk secara acak */
{
	/* KAMUS LOKAL */
	Peta P;
	int arah, count, i;
	ID next, start;
	boolean used[IDMax+1];

	/* ALGORITMA */
	LoadSubPeta(&P, namafileAreas);
	for(i = IDMin; i <= GetLastID(P); i++)
	{
		used[i] = false;
	}
	srand(time(NULL));
	count = 1;
	next = rand() % GetLastID(P) + 1;
	SubPeta(*PHasil, count) = SubPeta(P, next);
	SetAreaPoint(&SubPeta(*PHasil, count));
	for(i = 1; i <= 4; i++)
	{
		Koneksi(*PHasil, count, i) = IDUndef;
	}
	used[next] = true;
	do
	{ 
		do
		{
			/* Choosing current area to process */
			start = rand() % count + 1;		
			i = 1;
			while((i < 4) && Koneksi(*PHasil, start, i) != IDUndef)
			{
				i++;
			}
		}while(Koneksi(*PHasil, start, i) != IDUndef);
		do
		{
			/* Choosing the direction to connect */
			arah = rand() % 4 + 1;				
		}while(Koneksi(*PHasil, start, arah) != IDUndef);
		do
		{
			/* Choosing next area to connect to current area */
			next = rand() % GetLastID(P) + 1;		
		}while(used[next]);
		count++;
		SubPeta(*PHasil, count) = SubPeta(P, next);
		SetAreaPoint(&SubPeta(*PHasil, count));
		for(i = 1; i <= 4; i++)
		{
			Koneksi(*PHasil, count, i) = IDUndef;
		}
		used[next] = true;
		switch(arah)
		{
			case 1 :
			{
				Koneksi(*PHasil, start, 1) = count;
				Koneksi(*PHasil, count, 3) = start;
				break;
			}
			case 2 :
			{
				Koneksi(*PHasil, start, 2) = count;
				Koneksi(*PHasil, count, 4) = start;
				break;
			}
				case 3 :
			{
				Koneksi(*PHasil, start, 3) = count;
				Koneksi(*PHasil, count, 1) = start;
				break;
			}
			case 4 :
			{
				Koneksi(*PHasil, start, 4) = count;
				Koneksi(*PHasil, count, 2) = start;
				break;
			}
		}
	}while(count != GetLastID(P));
	IDEff(*PHasil) = count;
	CreateKoneksi(PHasil);
	CloseUnconnectedSubMapPoint(PHasil);
	SetBoss(PHasil);
}

void CloseUnconnectedSubMapPoint(Peta *P)
/* I.S. P terdefinisi */
/* F.S. setiap titik keluar di keempat sisi P yang tidak memiliki tetangga ditutup (diganti dengan Wall) */
{
	/* KAMUS LOKAL */
	int i, j;

	/* ALGORITMA */
	for(i = IDMin; i <= GetLastID(*P); i++)
	{
		for(j = 1; j <= 4; j++)
		{
			if(Koneksi(*P, i, j) == IDUndef)
			{
				switch(j)
				{
					case 1:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 1)), Absis(P_Neighbour(SubPeta(*P,i), 1))) = Wall;
						break;
					case 2:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 2)), Absis(P_Neighbour(SubPeta(*P,i), 2))) = Wall;
						break;
					case 3:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 3)), Absis(P_Neighbour(SubPeta(*P,i), 3))) = Wall;
						break;
					case 4:
						Elmt(Info(SubPeta(*P,i)), Ordinat(P_Neighbour(SubPeta(*P,i), 4)), Absis(P_Neighbour(SubPeta(*P,i), 4))) = Wall;
						break;
				}
			}
		}
	}
}

void FindFarthestSubPeta(Peta *P, ID Start, int jarak, int *maks, ID *IDMaks, boolean *visited)
/* I.S. P, Start, jarak, dan visited terdefinisi, maks dan IDMaks sembarang */
/* F.S. maks berisi jarak antara Subpeta terjauh dengan subpeta dengan ID start dan IDMaks berisi IDnya */
{
	/* KAMUS LOKAL */
	boolean end;
	int i;

	/* ALGORITMA */
	end = true;
	visited[Start] = true;
	for(i = 1; i <= 4; i++)
	{
		if(((Neighbour(SubPeta(*P,Start), i)) != NilArea) && (!visited[Koneksi(*P, Start, i)]))
		{
			end = false;
			FindFarthestSubPeta(P, Koneksi(*P, Start, i), jarak + 1, maks, IDMaks, visited);
		}
	}
	if(end)
	{
		if(*maks < jarak)
		{
			*maks = jarak;
			*IDMaks = Start;
		}
	}

}

void SetBoss(Peta *P)
/* I.S. P terdefinisi */
/* F.S. SubPeta terjauh dari SubPeta(*P,1) diubah menjadi Area Boss dan semua enemy dan medicine dihapus */
{
	/* KAMUS LOKAL */
	ID IDMaks;
	int maks, i, x, y;
	boolean visited[IDMax+1];

	/* ALGORITMA */
	for(i = IDMin; i <= GetLastID(*P); i++)
	{
		visited[i] = false;
	}
	maks = 0;
	IDMaks = IDUndef;
	FindFarthestSubPeta(P, 1, 0, &maks, &IDMaks, visited);
	y = (GetFirstIdxBrs(Info(SubPeta(*P, IDMaks))) + GetLastIdxBrs(Info(SubPeta(*P, IDMaks)))) / 2;
	x = (GetFirstIdxKol(Info(SubPeta(*P, IDMaks))) + GetLastIdxKol(Info(SubPeta(*P, IDMaks)))) / 2;
	Elmt(Info(SubPeta(*P, IDMaks)), y, x) = Boss;
}

void LoadPeta(Peta *P, char *namafileSubPeta, char *namafileKoneksi)
/* I.S. P sembarang, namafileSubPeta, dan namafileKoneksi terdefinisi */
/* F.S. Terbentuk Peta P sesuai dengan data yang ada di dalam file eksternal */
{
	/* KAMUS LOKAL */
	int i;

	/* ALGORITMA */
	LoadSubPeta(P, namafileSubPeta);
	LoadKoneksi(P, namafileKoneksi);
	CreateKoneksi(P);
	for(i = IDMin; i <= GetLastID(*P); i++)
	{
		SetAreaPoint(&SubPeta(*P,i));
	}
}

void LoadSubPeta(Peta *P, char *namafile)
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. Terbentuk SubPeta P (kumpulan Area) sesuai dengan data yang ada di file dengan nama namafile */
{
	/* KAMUS LOKAL */
	ID i;

	/* ALGORITMA */
	i = IDMin - 1;
	STARTMATRIKS(namafile);
	while(!EndMATRIKS)
	{
		i++;
		CreateEmptyArea(&SubPeta(*P,i));
		SubPeta(*P,i) = AlokasiArea(CMATRIKS);
		ADVMATRIKS();
	}
	IDEff(*P) = i;
}

void LoadKoneksi(Peta *P, char *namafile)
/* I.S. P sembarang, namafile terdefinisi */
/* F.S. Terbentuk koneksi antar-Area di P sesuai dengan data yang ada di file dengan nama namafile */
{
	/* KAMUS LOKAL */
	ID Node, tetangga;
	int arah;

	/* ALGORITMA */
	START(namafile);
	while(CC != MARK)
	{
		Node = 0;
		arah = 0;
		while(CC != BLANK)
		{
			Node = Node * 10 + (CC - '0');
			ADV();
		}
		ADV();
		while((CC != ENTER) && (CC != MARK))
		{
			tetangga = 0;
			while((CC != BLANK) && (CC != ENTER) && (CC != MARK))
			{
				tetangga = tetangga * 10 + (CC - '0');
				ADV();
			}
			arah++;
			Koneksi(*P,Node,arah) = tetangga;
			if(CC == BLANK)
			{
				ADV();
			}	
		}
		if(CC == ENTER)
		{
			ADV();
		}
	}
}

void CreateKoneksi(Peta *P)
/* I.S. P terdefinisi */
/* F.S. Antar-Area pada P terhubung berdasarkan data koneksi P */
{
	/* KAMUS LOKAL */
	int Node, tetangga, arah;

	/* ALGORITMA */
	for(Node = IDMin; Node <= GetLastID(*P); Node++)
	{
		for(arah = 1; arah <= 4; arah++)
		{
			tetangga = Koneksi(*P,Node,arah);
			if(tetangga != IDUndef)
			{
				switch(arah)
				{
					case 1 :
					{
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 1);
						break;
					}
					case 2 :
					{
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 2);
						break;
					}
					case 3 :
					{
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 3);
						break;
					}
					case 4 :
					{
						SetNeighbour(&SubPeta(*P,Node), SubPeta(*P,tetangga), 4);
						break;
					}
				}
			}
		}
	}
}

void SavePeta(Peta P, char *namafileSubPeta, char *namafileKoneksi)
/* I.S. P, namafileSubPeta dan namafileKoneksi terdefinisi */
/* F.S. Data P tersimpan di dalam file eksternal dengan nama namafileSubPeta untuk data SubPeta dan namafileKoneksi untuk data Koneksi */
{
	/* KAMUS LOKAL */
	FILE *fout;
	int i, j, k;

	/* ALGORITMA */
	/* Saving SubPeta */
	fout = fopen(namafileSubPeta, "w");
	fprintf(fout, "%d %d\n", NBrsEff(Info(SubPeta(P,IDMin))), NKolEff(Info(SubPeta(P,IDMin))));
	for(i = IDMin; i <= GetLastID(P); i++)
	{
		for(j = GetFirstIdxBrs(Info(SubPeta(P,i))); j <= GetLastIdxBrs(Info(SubPeta(P,i))); j++)
		{
			for(k = GetFirstIdxKol(Info(SubPeta(P,i))); k <= GetLastIdxKol(Info(SubPeta(P,i))); k++)
			{
				fprintf(fout,"%c", Elmt(Info(SubPeta(P,i)), j, k));
			}
			fprintf(fout, "\n");
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "%c", MARK);
	fclose(fout);

	/* Saving Koneksi */
	fout = fopen(namafileKoneksi, "w");
	for(i = IDMin; i <= GetLastID(P); i++)
	{
		fprintf(fout, "%d ", i);
		for(j = 1; j <= 4; j++)
		{
			fprintf(fout, "%d", Koneksi(P, i, j));
			if(j != 4)
			{
				fprintf(fout, " ");
			}
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "%c", MARK);
	fclose(fout);
}

/****************** Manajemen Memori ******************/
void DealokasiPeta(Peta *P)
/* I.S. P terdefinisi */
/* F.S. Semua address di P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian semua address (Area) di P */
{	
	/* KAMUS LOKAL */
	int i;
	
	/* ALGORITMA */
	for(i = IDMin; i <= GetLastID(*P); i++)
	{
		DealokasiArea(SubPeta(*P,i));
	}
	IDEff(*P) = 0;
}