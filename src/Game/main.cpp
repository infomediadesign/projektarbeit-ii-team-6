#include "Game.h"
#include "Scenes/DebugScene.h"

auto main() -> int
{
	auto game = Redge::Game(1280, 720);
	game.SetScene(std::make_unique<Redge::DebugScene>(&game));

	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}
}
