#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mapCreation.h"
#include "console.h"
#include "gameMechanic.h"
#include "ghostAi.h"



main()
{
	int mapNr;
	Map map;
	Player player;
	Ghost *ghosts;	

	game.player = &player;
	game.map = &map;
	game.ghostCount = 0;

	DWORD userInputThread, movementTimerThread;
	HANDLE userInputThreadHandle, movementThreadHandle;
	initScreen();

	while(1)
	{
		setColor(0x1F);
		system("cls");

		menu(&mapNr);
		system("cls");

		ghosts = malloc(game.ghostCount * sizeof(Ghost));
		game.score = 0;
		game.ghost = ghosts;
		player.block = 0;
		player.blockCount = 0;


		resetDirections(&player, ghosts, game.ghostCount);
		createMap(1, &map, &player, ghosts, game.ghostCount, mapNr);
		printMap(&map, &player, ghosts, game.ghostCount);

		movementThreadHandle = CreateThread(NULL, 0, move, 0 , 0, &movementTimerThread);
		userInputThreadHandle = CreateThread(NULL, 0, userInput, 0, 0, &userInputThread);

		WaitForSingleObject(movementThreadHandle, INFINITE);
		WaitForSingleObject(userInputThreadHandle, INFINITE);

		input = NULL;
		free(ghosts);

	}
//	free(ghosts);


	return 0;
}