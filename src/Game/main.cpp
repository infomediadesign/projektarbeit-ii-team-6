#include "Game.h"
#include "Scenes/MainMenu.h"

auto main() -> int
{
	auto game = Redge::Game(1600, 900);
	game.SetScene(std::make_shared<Redge::MainMenu>(&game));
	game.Run();
}
