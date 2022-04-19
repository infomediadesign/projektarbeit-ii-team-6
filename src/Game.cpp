#include "Game.h"

#include <string>

#include <raylib.h>

namespace Redge
{
	Game::Game(const uint16_t width, const uint16_t height)
	{
		InitWindow(width, height, "Codename: Redge");
		m_Tileset = Tileset("assets/Tileset.png", 32, 32);
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
		// TEMP: Print entire tile-set
		Vector2 position{};
		for (auto y = 0; y < m_Tileset.GetTileCountY(); ++y)
		{
			for (auto x = 0; x < m_Tileset.GetTileCountX(); ++x)
			{
				m_Tileset.DrawTile(x, y, position);
				position.x += static_cast<float>(m_Tileset.GetTileWidth());
			}

			position.x = 0;
			position.y += static_cast<float>(m_Tileset.GetTileHeight());
		}
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
