#include "ghostAi.h"

void initGhosts()
{
	int i = 0;
	for (i = 0; i < game.ghostCount; i++)
	{
		game.ghost[i].dir.X = 0;
		game.ghost[i].dir.Y = -1;
	}
}

void ghostAi()
{
	int i=0;
	if(game.ghostCount==1)
		ghostZero();
	else if (game.ghostCount == 2)
	{
		ghostZero();
		ghostOne();
	}
	else if (game.ghostCount == 3)
	{
		ghostZero();
		ghostOne();
		ghostTwo();
	}
	else
	{
		ghostZero();
		ghostOne();
		ghostTwo();
		ghostThree();
	}
	
	for (i = 0; i < game.ghostCount; i++)
	{
		game.ghost[i].prevDir = game.ghost[i].dir;
	}
}


void ghostZero()
{
	int dirToPlayerX = 0;
	int dirToPlayerY = 0;
	int upDist = 0, downDist = 0, leftDist = 0, rightDist = 0;
	COORD nextPos;
	nextPos.X = game.ghost[0].x;
	nextPos.Y = game.ghost[0].y;

	if (checkForIntersection(0))
	{
		dirToPlayerX = checkDirToPlayerX(0);
		if (dirToPlayerX != 0)
		{
			nextPos.X += dirToPlayerX;
			if (tryToMove(nextPos) && (-game.ghost[0].prevDir.X != dirToPlayerX))
			{
				game.ghost[0].dir.X = dirToPlayerX;
				game.ghost[0].dir.Y = 0;
			}
			else
			{
				nextPos.X -= dirToPlayerX;
				dirToPlayerY = checkDirToPlayerY(0);
				if (dirToPlayerY != 0)
				{
					nextPos.Y += dirToPlayerY;
					if (tryToMove(nextPos) && (-game.ghost[0].prevDir.Y != dirToPlayerY))
					{
						game.ghost[0].dir.X = 0;
						game.ghost[0].dir.Y = dirToPlayerY;
					}
					else
						goRandom(0);
				}
				else
					goRandom(0);
			}
		}
		else
		{
			dirToPlayerY = checkDirToPlayerY(0);
			if (dirToPlayerY != 0)
			{
				nextPos.Y += dirToPlayerY;
				if (tryToMove(nextPos) && (-game.ghost[0].prevDir.Y != dirToPlayerY))
				{
					game.ghost[0].dir.X = 0;
					game.ghost[0].dir.Y = dirToPlayerY;
				}
				else
				{
					nextPos.X -= dirToPlayerX;
					dirToPlayerX = checkDirToPlayerX(0);
					if (dirToPlayerX != 0)
					{
						nextPos.X += dirToPlayerX;
						if (tryToMove(nextPos) && (-game.ghost[0].prevDir.X != dirToPlayerX))
						{
							game.ghost[0].dir.Y = 0;
							game.ghost[0].dir.X = dirToPlayerX;
						}
						else
							goRandom(0);
					}
					else
						goRandom(0);
				}
			}
			else
				goRandom(0);
		}
	}
	else
	{
		nextPos.X += game.ghost[0].dir.X;
		nextPos.Y += game.ghost[0].dir.Y;
		if (tryToMove(nextPos))
			return;
		else
		{
			if (game.ghost[0].dir.Y != 0)
			{
				if (tryLeft(0))
					goLeft(0);
				else if (tryRight(0))
					goRight(0);
				else
					goRandom(0);
			}
			else if (game.ghost[0].dir.X != 0)
			{
				if (tryDown(0))
					goDown(0);
				else if (tryUp(0))
					goUp(0);
				else
					goRandom(0);
			}
			else
				goRandom(0);
		}
	}
}

void ghostOne()
{
	COORD nextPos;
	nextPos.X = game.ghost[1].x;
	nextPos.Y = game.ghost[1].y;

	
	if (checkForIntersection(1))
	{
		searchForSmell(1);
	}
	else
	{
		nextPos.X += game.ghost[1].dir.X;
		nextPos.Y += game.ghost[1].dir.Y;
		if (tryToMove(nextPos))
			return;
		else
		{
			if (game.ghost[1].dir.Y != 0)
			{
				if (tryLeft(1))
					goLeft(1);
				else if (tryRight(1))
					goRight(1);
				else
					goRandom(1);
			}
			else if (game.ghost[1].dir.X != 0)
			{
				if (tryDown(1))
					goDown(1);
				else if (tryUp(1))
					goUp(1);
				else
					goRandom(1);
			}
			else
				goRandom(1);
		}
	}


}

void ghostTwo()
{
	COORD nextPos;
	nextPos.X = game.ghost[2].x + game.ghost[2].dir.X;
	nextPos.Y = game.ghost[2].y + game.ghost[2].dir.Y;

	if (checkForIntersection(2))
	{
		goRandom(2);
	}
	else
	{
		if (tryToMove(nextPos))
			return;
		else
		{
			if (game.ghost[2].dir.Y != 0)
			{
				if (tryLeft(2))
					goLeft(2);
				else if (tryRight(2))
					goRight(2);
				else
					goRandom(2);
			}
			else if (game.ghost[2].dir.X != 0)
			{
				if (tryDown(2))
					goDown(2);
				else if (tryUp(2))
					goUp(2);
				else
					goRandom(2);
			}
			else
				goRandom(2);
		}

	}
}

void ghostThree()
{
	int dirToPlayerX = 0;
	int dirToPlayerY = 0;
	COORD nextPos;
	nextPos.X = game.ghost[3].x;
	nextPos.Y = game.ghost[3].y;

	if (checkForIntersection(3))
	{
		dirToPlayerY = checkDirToPlayerY(3);
		if (dirToPlayerY != 0)
		{
			nextPos.Y += dirToPlayerY;
			if (tryToMove(nextPos) && (-game.ghost[3].prevDir.Y != dirToPlayerY))
			{
				game.ghost[3].dir.Y = dirToPlayerY;
				game.ghost[3].dir.X = 0;
			}
			else
			{
				nextPos.Y -= dirToPlayerY;
				dirToPlayerX = checkDirToPlayerX(3);
				if (dirToPlayerX != 0)
				{
					nextPos.X += dirToPlayerX;
					if (tryToMove(nextPos) && (-game.ghost[3].prevDir.X != dirToPlayerX))
					{
						game.ghost[3].dir.Y = 0;
						game.ghost[3].dir.X = dirToPlayerX;
					}
					else
						goRandom(3);
				}
				else
					goRandom(3);
			}
		}
		else
		{
			dirToPlayerX = checkDirToPlayerX(3);
			if (dirToPlayerX != 0)
			{
				nextPos.X += dirToPlayerX;
				if (tryToMove(nextPos) && (-game.ghost[3].prevDir.X != dirToPlayerX))
				{
					game.ghost[3].dir.Y = 0;
					game.ghost[3].dir.X = dirToPlayerX;
				}
				else
				{
					nextPos.X -= dirToPlayerX;
					dirToPlayerY = checkDirToPlayerY(3);
					if (dirToPlayerY != 0)
					{
						nextPos.Y += dirToPlayerY;
						if (tryToMove(nextPos) && (-game.ghost[3].prevDir.Y != dirToPlayerY))
						{
							game.ghost[3].dir.X = 0;
							game.ghost[3].dir.Y = dirToPlayerY;
						}
						else
							goRandom(3);
					}
					else
						goRandom(3);
				}
			}
			else
				goRandom(3);
		}
	}
	else
	{
		nextPos.X += game.ghost[3].dir.X;
		nextPos.Y += game.ghost[3].dir.Y;
		if (tryToMove(nextPos))
			return;
		else
		{
			if (game.ghost[3].dir.Y != 0)
			{
				if (tryLeft(3))
					goLeft(3);
				else if(tryRight(3))
					goRight(3);
				else
					goRandom(3);
			}
			else if (game.ghost[3].dir.X != 0)
			{
				if (tryDown(3))
					goDown(3);
				else if(tryUp(3))
					goUp(3);
				else
					goRandom(3);
			}
			else
				goRandom(3);
		}
	}
}


int checkForIntersection(int i)
{
	if (game.map->ifIntersection[game.ghost[i].y][game.ghost[i].x])
		return 1;
	else
		return 0;
}

int checkDirToPlayerX(int i)
{
	int dirToPlayer = 0;

	if ((game.ghost[i].x - game.player->x) > 0)
		dirToPlayer = -1;
	else if ((game.ghost[i].x - game.player->x) < 0)
		dirToPlayer = 1;
	else if ((game.ghost[i].x - game.player->x) ==0)
		dirToPlayer = 0;

	return dirToPlayer;
}
int checkDirToPlayerY(int i)
{
	int dirToPlayer = 0;

	if ((game.ghost[i].y - game.player->y) > 0)
		dirToPlayer = -1;
	else if ((game.ghost[i].y - game.player->y) < 0)
		dirToPlayer = 1;
	else if ((game.ghost[i].y - game.player->y) == 0)
		dirToPlayer = 0;

	return dirToPlayer;
}

void searchForSmell(int i)
{
	int smell = 0;
	unsigned char go = 'A';

	//Szuka najsilniejszego zapachu i ustala kierunek
	if (tryUp(i))
	{
		if (game.map->playerSmell[game.ghost[i].y - 1][game.ghost[i].x] > smell)
		{
			smell = game.map->playerSmell[game.ghost[i].y - 1][game.ghost[i].x];
			go = 'U';
		}
	}
	if (tryDown(i))
	{
		if (game.map->playerSmell[game.ghost[i].y + 1][game.ghost[i].x] > smell)
		{
			smell = game.map->playerSmell[game.ghost[i].y + 1][game.ghost[i].x];
			go = 'D';
		}
	}
	if (tryRight(i))
	{
		if (game.map->playerSmell[game.ghost[i].y][game.ghost[i].x + 1] > smell)
		{
			smell = game.map->playerSmell[game.ghost[i].y][game.ghost[i].x + 1];
			go = 'R';
		}
	}
	if (tryLeft(i))
	{
		if (game.map->playerSmell[game.ghost[i].y][game.ghost[i].x - 1] > smell)
		{
			smell = game.map->playerSmell[game.ghost[i].y][game.ghost[i].x - 1];
			go = 'L';
		}
	}
	
	switch (go)
	{
	case 'A':
		goRandom(i);
		break;
	case 'U':
		goUp(i);
		break;
	case 'D':
		goDown(i);
		break;
	case 'R':
		goRight(i);
		break;
	case  'L':
		goLeft(i);
		break;
	default:
		goRandom(i);
		break;
	}
}

int tryToMove(COORD nextPos)
{
	if (game.map->elements[nextPos.Y][nextPos.X] != CORNER &&
		game.map->elements[nextPos.Y][nextPos.X] != BLOCK )
	{
		return 1;
	}
	else
		return 0;
}

int tryUp(int i)
{
	if (checkForIntersection(i))
	{
		if (game.map->elements[game.ghost[i].y - 1][game.ghost[i].x] != CORNER &&
			game.map->elements[game.ghost[i].y - 1][game.ghost[i].x] != BLOCK &&
			-game.ghost[i].prevDir.Y != -1)
			return 1;
		else
			return 0;
	}
	else
	{
		if (game.map->elements[game.ghost[i].y - 1][game.ghost[i].x] != CORNER &&
			game.map->elements[game.ghost[i].y - 1][game.ghost[i].x] != BLOCK)
			return 1;
		else
			return 0;
	}
	
}
int tryDown(int i)
{
	if (checkForIntersection(i))
	{
		if (game.map->elements[game.ghost[i].y + 1][game.ghost[i].x] != CORNER &&
			game.map->elements[game.ghost[i].y + 1][game.ghost[i].x] != BLOCK &&
			-game.ghost[i].prevDir.Y != 1)
			return 1;
		else
			return 0;
	}
	else
	{
		if (game.map->elements[game.ghost[i].y + 1][game.ghost[i].x] != CORNER &&
			game.map->elements[game.ghost[i].y + 1][game.ghost[i].x] != BLOCK)
			return 1;
		else
			return 0;
	}
	
}
int tryLeft(int i)
{
	if (checkForIntersection(i))
	{
		if (game.map->elements[game.ghost[i].y][game.ghost[i].x - 1] != CORNER &&
			game.map->elements[game.ghost[i].y][game.ghost[i].x - 1] != BLOCK &&
			-game.ghost[i].prevDir.X != -1)
			return 1;
		else
			return 0;
	}
	else
	{
		if (game.map->elements[game.ghost[i].y][game.ghost[i].x - 1] != CORNER &&
			game.map->elements[game.ghost[i].y][game.ghost[i].x - 1] != BLOCK)
			return 1;
		else
			return 0;
	}
	
}
int tryRight(int i)
{
	if (checkForIntersection(i))
	{
		if (game.map->elements[game.ghost[i].y][game.ghost[i].x + 1] != CORNER &&
			game.map->elements[game.ghost[i].y][game.ghost[i].x + 1] != BLOCK &&
			-game.ghost[i].prevDir.X != 1)
			return 1;
		else
			return 0;
	}
	else
	{
		if (game.map->elements[game.ghost[i].y][game.ghost[i].x + 1] != CORNER &&
			game.map->elements[game.ghost[i].y][game.ghost[i].x + 1] != BLOCK)
			return 1;
		else
			return 0;
	}
	
}

void goUp(int i)
{
	game.ghost[i].dir.X = 0;
	game.ghost[i].dir.Y = -1;
}
void goDown(int i)
{
	game.ghost[i].dir.X = 0;
	game.ghost[i].dir.Y = 1;
}
void goLeft(int i)
{
	game.ghost[i].dir.X = -1;
	game.ghost[i].dir.Y = 0;
}
void goRight(int i)
{
	game.ghost[i].dir.X = 1;
	game.ghost[i].dir.Y = 0;
}

void goRandom(int i)
{
	char r;
	int blocked = 0;
	r = rand()%4;

	while (1) 
	{
		if (r == 0)
		{
			if (tryUp(i))
			{
				goUp(i);
				break;
			}
			else
			{
				r++;
				blocked++;
			}
		}
		if (r == 1)
		{
			if (tryDown(i))
			{
				goDown(i);
				break;
			}
			else
			{
				r++;
				blocked++;
			}
		}
		if (r == 2)
		{
			if (tryRight(i))
			{
				goRight(i);
				break;
			}
			else
			{
				r++;
				blocked++;
			}
		}
		if(r == 3)
		{
			if (tryLeft(i))
			{
				goLeft(i);
				break;
			}
			else
			{
				r=0;
				blocked++;
			}
		}
		if (blocked > 4)
		{
			goBack(i);
			break;
		}
	}

}

void goBack(int i)
{
	game.ghost[i].dir.X = -game.ghost[i].prevDir.X;
	game.ghost[i].dir.Y = -game.ghost[i].prevDir.Y;
}
