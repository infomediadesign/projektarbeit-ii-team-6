#include "Game.h"

#include <raylib.h>

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
		(void)this;
		return !WindowShouldClose();
	}

	auto Game::Update() -> void
	{
		(void)this;
	}

	auto Game::Render() const -> void
	{
		BeginDrawing();
		ClearBackground(PINK);

		RenderWorld();
		RenderForeground();
		RenderUI();

		EndDrawing();
	}

	auto Game::RenderWorld() const -> void
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
} // namespace Redge
