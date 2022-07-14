#include "Game.h"
#include "Scenes/TiledScene.h"

auto main() -> int
{
	auto game = Redge::Game(1280, 720);
	game.SetScene(std::make_shared<Redge::TiledScene>(&game));
	game.Run();
}
