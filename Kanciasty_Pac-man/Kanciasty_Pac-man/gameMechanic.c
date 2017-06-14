#include <stdlib.h>
#include <stdio.h>
#include "gameMechanic.h"
#include "mapCreation.h"

DWORD WINAPI move()
{
	srand(time(NULL));
	win = 0;
	playerNextDir.X = 0;
	playerNextDir.Y = 0;

	while (input != 'q')
	{
		game.player->dir.X = playerNextDir.X;
		game.player->dir.Y = playerNextDir.Y;
		movePlayer();
		refreshPlayerPosition();
		refreshPoints();
		if (game.score >= 65)
			win = 1;
		if (win != 0)
			break;
		checkeDeath();
		if (win != 0)
			break;
		moveGhosts();
		refreshGhostPosition();
		checkeDeath();
		if (win != 0)
			break;
		previous = game.player->dir;
		decreasePlayerSmell();
		Sleep(250);
	}

	if (win == 1)
	{
		gameWin();
	}
	else if (win == -1)
	{
		gameLoose();
	}
}

void movePlayer()
{
	unsigned char nextPosition = game.map->elements[game.player->y + game.player->dir.Y][game.player->x + game.player->dir.X];

	if (playerCollision(nextPosition))
	{
		return;
	}
	else
	{
		nextPosition = game.map->elements[game.player->y + previous.Y][game.player->x + previous.X];
		if (playerCollision(nextPosition))
		{
			game.player->dir = previous;
		}
		else
		{
			game.player->dir.X = 0;
			game.player->dir.Y = 0;
		}
	}
}

void moveGhosts()
{
	ghostAi();
}

int playerCollision(int nextPosition)
{
	if (nextPosition == CORNER)
		return 0;
	else
	{
		return 1;
	}
}

void checkeDeath()
{
	int i = 0;

	for (i = 0; i < game.ghostCount; i++)
	{
		if (game.player->x == game.ghost[i].x && game.player->y == game.ghost[i].y)
		{
			win = -1;
		}
	}

}

void gameLoose()
{
	setColor(0xC8);
	putStrXY(8, 2, "                                   ");
	setColor(0x4F);
	putStrXY(8, 3, "                                   ");
	putStrXY(8, 4, "                                   ");
	putStrXY(8, 5, "           Przegrywasz ;(          ");
	putStrXY(8, 6, "                                   ");
	putStrXY(8, 7, "      [spacja] - wroc do menu      ");
	putStrXY(8, 8, "         [q] - wyjdz z gry         ");
	putStrXY(8, 9, "                                   ");
	putStrXY(8, 10, "                                   ");
	setColor(0xC8);
	putStrXY(8, 11, "                                   ");
}

void gameWin()
{
	setColor(0xA1);
	putStrXY(8, 2, "                                   ");
	setColor(0x2F);
	putStrXY(8, 3, "                                   ");
	putStrXY(8, 4, "                                   ");
	putStrXY(8, 5, "       Gratulacje WYGRYWASZ!       ");
	putStrXY(8, 6, "                                   ");
	putStrXY(8, 7, "      [spacja] - wroc do menu      ");
	putStrXY(8, 8, "         [q] - wyjdz z gry         ");
	putStrXY(8, 9, "                                   ");
	putStrXY(8, 10, "                                   ");
	setColor(0xA1);
	putStrXY(8, 11, "                                   ");
}

DWORD WINAPI userInput()
{
	while (tolower(input) != 'q')
	{
		input = getKey();
		input = tolower(input);

		if (win == 0)
		{
			//strza³ki
			if (input == -32 || input == 0)
			{
				switch (_getch())
				{
				case UP:
					playerNextDir.X = 0;
					playerNextDir.Y = -1;
					break;
				case DOWN:
					playerNextDir.X = 0;
					playerNextDir.Y = 1;
					break;
				case RIGHT:
					playerNextDir.X = 1;
					playerNextDir.Y = 0;
					break;
				case LEFT:
					playerNextDir.X = -1;
					playerNextDir.Y = 0;
					break;
				default:
					break;
				}
			}
			//w-a-s-d
			if (input == 'w')
			{
				playerNextDir.X = 0;
				playerNextDir.Y = -1;
			}
			else if (input == 's')
			{
				playerNextDir.X = 0;
				playerNextDir.Y = 1;
			}
			else if (input == 'd')
			{
				playerNextDir.X = 1;
				playerNextDir.Y = 0;
			}
			else if (input == 'a')
			{
				playerNextDir.X = -1;
				playerNextDir.Y = 0;
			}
			else if (input == 'b')
			{
				if (game.player->blockCount < game.maxBlockCount)
				{
					game.player->block = 1;
					game.player->blockCount++;
					putCharXY(BOARDWIDTH + 3 + 19, 6, game.maxBlockCount - game.player->blockCount + 48);
				}
				else
				{
					putStrXY(BOARDWIDTH + 3, 8, "Nie mozna postawic");
					putStrXY(BOARDWIDTH + 3, 9, "wiecej blokad.");
				}
			}
		}
		else if (input == ' ' && win != 0)
			break;
		else if (input == 'q' && win != 0)
			exit(0);
	}
}
