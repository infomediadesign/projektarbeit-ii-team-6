#include "Game.h"

auto main() -> int
{
	auto game = Redge::Game(1280, 720);

	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}
}
