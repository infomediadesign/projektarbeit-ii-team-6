#include "Game.h"
#include "Scenes/MainMenu.h"

auto main() -> int
{
	auto game = Redge::Game(1280, 720);
	game.SetScene(std::make_unique<Redge::MainMenu>(&game));

	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}
}
