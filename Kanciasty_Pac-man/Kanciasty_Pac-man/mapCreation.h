#pragma once

#include "config.h"

typedef struct
{
	int x;
	int y;
	COORD dir;
	int block;
	int blockCount;
} Player;

typedef struct
{
	int x;
	int y;
	COORD dir;
	COORD prevDir;
} Ghost;

typedef struct
{
	unsigned char elements[BOARDHEIGHT][BOARDWIDTH];
	unsigned char ifIntersection[BOARDHEIGHT][BOARDWIDTH];
	int playerSmell[BOARDHEIGHT][BOARDWIDTH];
} Map ;

typedef struct
{
	Map *map;
	Player *player;
	Ghost *ghost;
	int ghostCount;
	int score;
	int maxBlockCount;

} Game;

//Reaetuje kierunki nastêpnego ruchu duchów i gracza
void resetDirections(Player*, Ghost[], int);

//Wczytuje mapê z pliku
void createMap(int, Map*, Player*, Ghost[], int, int);

//Znajduje skrzy¿owania i zapisuje je do tablicy map.ifIntersection[][]
void chceckForIntersection(Map*);

//Wyœwietla mapê na ekranie
void printMap(Map*, Player*, Ghost[], int);

//Odœwie¿a licznik punktów
void refreshPoints();

//Odœwie¿a pozycje gracza
void refreshPlayerPosition();

//Odœwie¿a pozycje duchów
void refreshGhostPosition();

//Zmniejsza zapach gracza o 1 na wszystkich polach na których zapach > 0
void decreasePlayerSmell();