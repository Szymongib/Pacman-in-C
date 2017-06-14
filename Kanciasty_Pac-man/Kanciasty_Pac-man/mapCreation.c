#include <stdio.h>
#include <stdlib.h>

#include "mapCreation.h"
#include "console.h"
#include "gameMechanic.h"


void resetDirections(Player *player, Ghost ghost[], int ghostCount)
{
	int i = 0;
	player->dir.X = 0;
	player->dir.Y = 0;

	for (i = 0; i < ghostCount; i++)
	{
		ghost[i].dir.X = 0;
		ghost[i].dir.Y = 0;
	}
}

void createMap(int nrMapy, Map *map, Player *player, Ghost ghost[], int ghostCount, int mapNr)
{
	unsigned char z;
	int row = 0;
	int column = 0;
	int ghostNumber = 0;
	FILE *plik;

	//Wczytuje plik na podstawie wyboru w menu
	switch (mapNr)
	{
	case 1:
		plik = fopen("map1.txt", "r");
		break;
	case 2:
		plik = fopen("map2.txt", "r");
		break;
	case 3:
		plik = fopen("map3.txt", "r");
		break;
	default:
		printf("ERROR - nie znaleziono pliku");
		getch();
		exit(0);
		break;
	}
	
	if (plik == NULL)
	{
		printf("ERROR - otwieranie pliku nie powiodlo sie");
		system("pause");
		exit(0);
	}

	while (row<BOARDHEIGHT)
	{
		z = fgetc(plik);
		if (z == EOF)
			break;

		if (z == '\n')
		{
			row++;
			column = 0;
			continue;
		}

		switch (z)
		{
		case ' ':
			map->elements[row][column] = EMPTY;
			break;
		case '+':
			map->elements[row][column] = PICK_UP;
			break;
		case 'C':
			map->elements[row][column] = CORNER;
			break;
		case 'X':
			player->x = column;
			player->y = row;
			map->elements[row][column] = EMPTY;
			break;
		default:
			break;
		}

		if (z == '1' || z == '2' || z == '3' || z == '4')
		{
			if ((z - 48) <= game.ghostCount)
			{
				ghost[ghostNumber].x = column;
				ghost[ghostNumber].y = row;
				ghostNumber++;
				map->elements[row][column] = EMPTY;
			}
			else
				map->elements[row][column] = EMPTY;
		}

		map->ifIntersection[row][column] = 0;
		map->playerSmell[row][column] = 0;
		column++;
	}
	chceckForIntersection(map);
}

void chceckForIntersection(Map *map)
{
	int i = 0, k = 0;
	int check = 0;

	for (i = 1; i < BOARDHEIGHT-1; i++)
	{
		for (k = 1; k < BOARDWIDTH - 1; k++)
		{
			if (map->elements[i][k] != CORNER)
			{
				if (map->elements[i + 1][k] != CORNER)
					check++;
				if (map->elements[i - 1][k] != CORNER)
					check++;
				if (map->elements[i][k + 1] != CORNER)
					check++;
				if (map->elements[i][k - 1] != CORNER)
					check++;
				if (check >= 3)
					map->ifIntersection[i][k] = 1;
				else
					map->ifIntersection[i][k] = 0;
			}
			else
				map->ifIntersection[i][k] = 0;
			check = 0;
		}
	}
}

void printMap(Map *map, Player *player, Ghost ghost[], int ghostCount)
{
	int i = 0, k = 0;
	unsigned char z = ' ';
	setColor(0x1E);

	for (i = 0; i < BOARDHEIGHT; i++)
	{
		for (k = 0; k < BOARDWIDTH; k++)
		{
			z = map->elements[i][k];
			putCharXY(k, i, z);
		}
	}

	putCharXY(player->x, player->y, PLAYER);
	for (i = 0; i < game.ghostCount; i++)
	{
		putCharXY(ghost[i].x, ghost[i].y, GHOST);
	}

	putStrXY(BOARDWIDTH + 3, 0, "punkty: ");
	putStrXY(BOARDWIDTH + 3, 2, "[q] - powrot do menu");
	putStrXY(BOARDWIDTH + 3, 4, "[b] - postaw blokade");
	putStrXY(BOARDWIDTH + 3, 6, "Pozostale blokady: ");
	putCharXY(BOARDWIDTH + 3 + 19, 6, game.maxBlockCount+48);
	refreshPoints();
}

void refreshPoints()
{
	COORD pointsCoord;
	pointsCoord.X = BOARDWIDTH + 10;
	pointsCoord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pointsCoord);
	printf("%d", game.score);
}

void refreshPlayerPosition()
{
	setColor(0x1F);

	putCharXY(game.player->x + game.player->dir.X, game.player->y + game.player->dir.Y, PLAYER);

	if (game.map->elements[game.player->y][game.player->x] == PICK_UP)
		game.score++;

	//Wstawianie pustego elementu w miejsce gdzie przebywal gracz
	if (game.player->block == 1)
	{
		game.map->elements[game.player->y][game.player->x] = BLOCK;
		putCharXY(game.player->x, game.player->y, BLOCK);
		game.player->block = 0;
	}
	else
	{
		game.map->elements[game.player->y][game.player->x] = EMPTY;
			
		if ((game.player->x + game.player->dir.X) != game.player->x || (game.player->y + game.player->dir.Y) != game.player->y)
		{
			putCharXY(game.player->x, game.player->y, EMPTY);
		}
	}
	
	//Aktualizacja pozycji gracza
	game.player->x += game.player->dir.X;
	game.player->y += game.player->dir.Y;

	

	//Ustawianie zapachu gracza na max
	game.map->playerSmell[game.player->y][game.player->x] = PLAYER_SMELL_MAX;

}

void refreshGhostPosition()
{
	int i = 0;
	int color;
	

	for (i = 0; i < game.ghostCount; i++)
	{
		setColor(0xA+i);
		putCharXY(game.ghost[i].x + game.ghost[i].dir.X, game.ghost[i].y + game.ghost[i].dir.Y, GHOST);
		//Wstawianie poprzedniego elementu na pozycje ducha
		setColor(0x1E);
		putCharXY(game.ghost[i].x, game.ghost[i].y, game.map->elements[game.ghost[i].y][game.ghost[i].x]);

		if (i == 1)
			game.map->playerSmell[game.ghost[i].y][game.ghost[i].x] = 0;
		//Aktualizacja pozycji ducha
		game.ghost[i].x += game.ghost[i].dir.X;
		game.ghost[i].y += game.ghost[i].dir.Y;
	}
}

void decreasePlayerSmell()
{
	int i = 0, k = 0;

	for (i = 1; i < BOARDHEIGHT - 1; i++)
	{
		for (k = 1; k < BOARDWIDTH - 1; k++)
		{
			if (game.map->playerSmell[i][k] > 0)
			{
				game.map->playerSmell[i][k]--;
			}
		}
	}
}
