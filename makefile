OBJS = BrightSouls.o mesinkar.o mesinkata.o area.o peta.o enemy.o player.o stackqueue.o matriks.o point.o jam.o bintree.o
DRIVER = 
ObjectDir = obj/
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all :  
	make driver
	make main
	make clean

driver : mmesinkata mpoint mstackqueue menemy mjam mmatriks mbintree mplayer mpeta

main : BrightSouls

mmesinkata : mmesinkata.o mesinkata.o mesinkar.o
	$(CC) $(LFLAGS) mmesinkata.o mesinkata.o mesinkar.o -lncurses -o bin/Driver/mmesinkata

mpoint : mpoint.o point.o
	$(CC) $(LFLAGS) mpoint.o point.o -o bin/Driver/mpoint

mstackqueue : mstackqueue.o stackqueue.o
	$(CC) $(LFLAGS) mstackqueue.o stackqueue.o -lncurses -o bin/Driver/mstackqueue

menemy : menemy.o enemy.o mesinkar.o mesinkata.o stackqueue.o
	$(CC) $(LFLAGS) menemy.o enemy.o mesinkar.o mesinkata.o stackqueue.o -lncurses -o bin/Driver/menemy

mjam : mjam.o jam.o
	$(CC) $(LFLAGS) mjam.o jam.o -lncurses -o bin/Driver/mjam 

mmatriks : mmatriks.o matriks.o mesinkar.o
	$(CC) $(LFLAGS) mmatriks.o matriks.o mesinkar.o -o bin/Driver/mmatriks 

mbintree : mbintree.o bintree.o mesinkar.o
	$(CC) $(LFLAGS) mbintree.o bintree.o mesinkar.o -lncurses -o bin/Driver/mbintree

mplayer: mplayer.o player.o mesinkar.o mesinkata.o bintree.o point.o
	$(CC) $(LFLAGS) mplayer.o player.o mesinkar.o mesinkata.o bintree.o point.o -lncurses -o bin/Driver/mplayer

mpeta: mpeta.o peta.o mesinkar.o mesinkata.o matriks.o area.o point.o
	$(CC) $(LFLAGS) mpeta.o peta.o mesinkar.o mesinkata.o matriks.o area.o point.o -lncurses -o bin/Driver/mpeta

BrightSouls : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -lncurses -o bin/BrightSouls

mmesinkata.o : src/MesinKarKata/mesinkata.h src/MesinKarKata/mesinkata.c src/MesinKarKata/mesinkar.c
	$(CC) $(CFLAGS) src/MesinKarKata/mmesinkata.c

mpoint.o : src/Point/point.h src/Point/point.c
	$(CC) $(CFLAGS) src/Point/mpoint.c

mstackqueue.o : src/StackQueue/stackqueue.h src/StackQueue/stackqueue.c
	$(CC) $(CFLAGS) src/StackQueue/mstackqueue.c

menemy.o : src/Enemy/enemy.h src/Enemy/enemy.c src/MesinKarKata/mesinkar.c src/MesinKarKata/mesinkata.c src/StackQueue/stackqueue.c
	$(CC) $(CFLAGS) src/Enemy/menemy.c

mjam.o : src/Jam/jam.h src/Jam/jam.c
	$(CC) $(CFLAGS) src/Jam/mjam.c

mmatriks.o : src/Matriks/matriks.h src/Matriks/matriks.c src/MesinKarKata/mesinkar.c
	$(CC) $(CFLAGS) src/Matriks/mmatriks.c

mbintree.o : src/BinTree/bintree.h src/BinTree/bintree.c src/MesinKarKata/mesinkar.c
	$(CC) $(CFLAGS) src/BinTree/mbintree.c

mplayer.o : src/Player/player.h src/Player/player.c src/MesinKarKata/mesinkar.c src/MesinKarKata/mesinkata.c src/BinTree/bintree.c src/Point/point.c 
	$(CC) $(CFLAGS) src/Player/mplayer.c

mpeta.o : src/Peta/peta.h src/Peta/peta.c src/MesinKarKata/mesinkar.c src/MesinKarKata/mesinkata.c src/Matriks/matriks.c src/Peta/area.c src/Point/point.c 
	$(CC) $(CFLAGS) src/Peta/mpeta.c

BrightSouls.o : src/MesinKarKata/mesinkar.h src/MesinKarKata/mesinkar.c src/MesinKarKata/mesinkata.h src/MesinKarKata/mesinkata.c src/Matriks/matriks.h src/Matriks/matriks.c src/Peta/area.h src/Peta/area.c src/Peta/peta.h src/Peta/peta.c src/Enemy/enemy.h src/Enemy/enemy.c src/Player/player.h src/Player/player.c src/StackQueue/stackqueue.h src/StackQueue/stackqueue.c src/Point/point.h src/Point/point.c
	$(CC) $(CFLAGS) src/Main/BrightSouls.c 

mesinkar.o : src/MesinKarKata/mesinkar.h src/MesinKarKata/mesinkar.c
	$(CC) $(CFLAGS) src/MesinKarKata/mesinkar.c 

mesinkata.o : src/MesinKarKata/mesinkar.h src/MesinKarKata/mesinkar.c src/MesinKarKata/mesinkata.h src/MesinKarKata/mesinkata.c 
	$(CC) $(CFLAGS) src/MesinKarKata/mesinkata.c 

matriks.o : src/Matriks/matriks.h src/Matriks/matriks.c
	$(CC) $(CFLAGS) src/Matriks/matriks.c 

area.o : src/Peta/area.h src/Peta/area.c
	$(CC) $(CFLAGS) src/Peta/area.c 

peta.o : src/Peta/peta.h src/Peta/peta.c
	$(CC) $(CFLAGS) src/Peta/peta.c 

enemy.o : src/Enemy/enemy.h src/Enemy/enemy.c
	$(CC) $(CFLAGS) src/Enemy/enemy.c 

player.o : src/Player/player.h src/Player/player.c
	$(CC) $(CFLAGS) src/Player/player.c 

stackqueue.o : src/StackQueue/stackqueue.h src/StackQueue/stackqueue.c
	$(CC) $(CFLAGS) src/StackQueue/stackqueue.c 

point.o : src/Point/point.h src/Point/point.c
	$(CC) $(CFLAGS) src/Point/point.c 

jam.o : src/Jam/jam.h src/Jam/jam.c
	$(CC) $(CFLAGS) src/Jam/jam.c

bintree.o : src/BinTree/bintree.h src/BinTree/bintree.c
	$(CC) $(CFLAGS) src/BinTree/bintree.c 

clean:
	\rm *.o 