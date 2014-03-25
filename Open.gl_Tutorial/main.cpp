#include "main.h"

int main()
{
	Game game;
	if (game.Initialise())
	{
		game.MainLoop();
	}

	std::string blocker;
	//std::cin >> blocker;

	return 0;
}