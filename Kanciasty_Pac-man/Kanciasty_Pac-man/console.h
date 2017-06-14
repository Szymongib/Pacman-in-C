#pragma once

//Wyœwietla menu
void menu(int*);

//Ustawia parametry konsoli
void initScreen();

//Ustawia rozmiar znaków w consoli
void consoleSize();

//Ustawia kolor
void setColor(unsigned short id);

//Wstawia znak w okreœlone miejsce
void putCharXY(int x, int y, unsigned char z);

//Wstawia ³añcuch znaków w okreœlone miejsce
void putStrXY(int x, int y, const char *s);

//Pobiera znak od u¿ytkownika
char getKey();
