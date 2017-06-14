#pragma once

#include "mapCreation.h"
#include "console.h"
#include "ghostAi.h"

char input, win;
Game game;
COORD playerNextDir;
COORD previous;

//Ustala nastêpn¹ pozycje duchów
//Przesuwa gracza i duchy o jedno pole
//Sprawdza czy gracz przegra³/wygra³
//Odœwie¿a punkty
DWORD WINAPI move();

void movePlayer();

void moveGhosts();

int playerCollision(int);

void checkeDeath();

void gameLoose();

void gameWin();

//Ustala kierunek gracza na podstawie informacji odbieranych z klawiatury
DWORD WINAPI userInput();


