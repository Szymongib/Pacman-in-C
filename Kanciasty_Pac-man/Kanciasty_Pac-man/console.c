#include <windows.h>
#include <stdio.h>

#include "console.h"
#include "mapCreation.h"
#include "gameMechanic.h"

void menu(int *mapNr)
{
	char m='/0';

	putStrXY(20, 0, "Pac - man");
	putStrXY(2, 2, "Wybierz mape:");
	putStrXY(36, 13, "[q] - wyjscie");
	putStrXY(2, 3, "1 - Mapa 1");
	putStrXY(2, 4, "2 - Mapa 2");
	putStrXY(2, 5, "3 - Mapa 3");
	printf("\n");

	//Wybór mapy
	do
	{
		m = getKey();
		m = tolower(m);

		switch (m)
		{
		case '1':
			*mapNr = 1;
			break;
		case '2':
			*mapNr = 2;
			break;
		case '3':
			*mapNr = 3;
			break;
		case 'q':
			exit(0);
		default:
			putStrXY(2, 7, "Niepoprawny znak sprobuj ponownie.");
			m = '\0';
			break;
		}
	} while (m == '\0');

	putStrXY(0, 7, "                                      ");

	m = NULL;

	putStrXY(28, 2, "Wybierz poziom trudnosci:");
	putStrXY(28, 3, "1 - Bardzo latwy");
	putStrXY(28, 4, "2 - Latwy");
	putStrXY(28, 5, "3 - Sredni");
	putStrXY(28, 6, "4 - Trudny");
	printf("\n");

	do
	{
		m = getKey();
		m = tolower(m);

		switch (m)
		{
		case '1':
			game.ghostCount = 1;
			game.maxBlockCount = 5;
			break;
		case '2':
			game.ghostCount = 2;
			game.maxBlockCount = 4;
			break;
		case '3':
			game.ghostCount = 3;
			game.maxBlockCount = 3;
			break;
		case '4':
			game.ghostCount = 4;
			game.maxBlockCount = 2;
			break;
		case 113:
			exit(0);
		default:
			putStrXY(2, 7, "Niepoprawny znak sprobuj ponownie");
			m = '\0';
			break;
		}
	} while (m == '\0');
	putStrXY(0, 7, "                                      ");

	putStrXY(10, 9, "Wybrano mape i poziom trudnosci,");
	putStrXY(5, 10, "nacisnij dowolny klawisz by rozpoczac gre.");
	putStrXY(36, 13, "             ");
	getKey();

}

void initScreen()
{
	// Wymaga: windows.h
	// wy³¹czenie mrugania kursora - dzia³a od windowsa XP
	CONSOLE_CURSOR_INFO cciInfo;
	cciInfo.dwSize = 1;
	cciInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo);
	consoleSize();
	setColor(0x1F);
	system("chcp 852");
	system("cls");
}

void consoleSize()
{
	//system("MODE CON: COLS=110 LINES=25");
	// zwiêkszenie czcionki dzia³a od windowsa vista
	CONSOLE_FONT_INFOEX x;
	x.cbSize = sizeof(x);
	x.dwFontSize.Y = FONTSIZE;
	x.dwFontSize.X = FONTSIZE-12;
	x.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &x);
}

void setColor(unsigned short id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id);
}

void putCharXY(int x, int y, unsigned char z)
{
	COORD a;
	a.X = x;
	a.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
	printf("%c", z);
}

void putStrXY(int x, int y, const char *s)
{
	while (*s)
		putCharXY(x++, y, *s++);
}

char getKey()
{
	return getch();
}

