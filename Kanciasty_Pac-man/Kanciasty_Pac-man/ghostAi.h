#pragma once
#include <time.h>

#include "mapCreation.h"
#include "gameMechanic.h"

//Duchu nie mog¹ zawracaæ na skrzy¿owaniu
//Mog¹ siê cofaæ jedynie gdy natrafi¹ na blokadê postawion¹ przez gracza


//Nadaje duch¹ pocz¹tkowy kierunek ruchu
void initGhosts();

//Wywo³uje funkcje steruj¹ca duchami w zale¿noœci od poziomu trudnoœci
void ghostAi();

// stara siê zrównaæ z graczem na osi X, gdy to zrobi stara siê zrównaæ na osi Y
void ghostZero();

//Duch 1: na skrzy¿owaniach szuka zapachu gracza, je¿eli go znajduje to za nim pod¹¿a
//gdy nie ma skrzy¿owania porusza siê przed siebie
void ghostOne();

//Duch 2: pseudo losowo wybiera kierunki
void ghostTwo();

//Duch 3: stara siê zrównaæ z graczem na osi Y, gdy to zrobi stara siê zrównaæ na osi X
void ghostThree();

//Sprawdza czy duch i znajduje siê na polu bêd¹cym skrzy¿owaniem
int checkForIntersection(int i);

//Okreœla po³o¿enie ducha wzglêdem gracza na osi X
int checkDirToPlayerX(int i);

//Okreœla po³o¿enie ducha wzglêdem gracza na osi Y
int checkDirToPlayerY(int i);

//Szuka zapachu gracza na wszystkich polach, na które duch mo¿e przejœæ z obecnego pola
void searchForSmell(int i);

//Sprawdza czy mo¿liwy jest ruch na podan¹ pozycjê
int tryToMove(COORD);
int tryUp(int i);
int tryDown(int i);
int tryLeft(int i);
int tryRight(int i);

//Zmienia kierunek ducha tak, aby przy nastepnym odœwie¿eniu pozycji poszed³ w podan¹ stronê
void goUp(int i);
void goDown(int i);
void goLeft(int i);
void goRight(int i);
void goRandom(int i);
void goBack(int i);