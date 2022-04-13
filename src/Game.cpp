#include "Game.h"

#include <raylib.h>
#include <string>

namespace Redge
{
	Game::Game(const uint16_t width, const uint16_t height)
	{
		InitWindow(width, height, "Codename: Redge");
	}

	Game::~Game()
	{
		CloseWindow();
	}

	auto Game::IsRunning() const -> bool
	{
		return !WindowShouldClose();
	}

	auto Game::Update() -> void
	{
	}

	auto Game::Render() const -> void
	{
		BeginDrawing();
		ClearBackground(PINK);

		RenderBackground();
		RenderForeground();
		RenderUI();

		EndDrawing();
	}

	auto Game::RenderBackground() const -> void
	{
		(void)this;
	}

	auto Game::RenderForeground() const -> void
	{
		(void)this;
	}

	auto Game::RenderUI() const -> void
	{
		(void)this;
	}
}
