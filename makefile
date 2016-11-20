OBJS = BrightSouls.o mesinkar.o mesinkata.o area.o peta.o enemy.o player.o stackqueue.o matriks.o point.o jam.o
ObjectDir = obj/
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

COBJS = $(addprefix $(ObjectDir),$(OBJS))
BrightSouls : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -lncurses -o bin/BrightSouls
	make clean1

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

clean1:
	\rm *.o 

clean2:
	\rm bin/BrightSouls

run:
	bin/BrightSouls