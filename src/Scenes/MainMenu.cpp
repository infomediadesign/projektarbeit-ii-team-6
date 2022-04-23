#include "MainMenu.h"

namespace Redge
{
	MainMenu::MainMenu(Game* host) : Scene(host)
	{
		m_FloorTiles = Tileset("assets/FloorTiles.png", 16, 16);
	}

	auto MainMenu::Update() -> void
	{
	}

	auto MainMenu::RenderWorld() const -> void
	{
		Vector2 position{};

		for (auto indexY = 0; indexY < m_FloorTiles.GetTileCountY(); ++indexY)
		{
			constexpr float scale = 10;
			for (auto indexX = 0; indexX < m_FloorTiles.GetTileCountX(); ++indexX)
			{
				m_FloorTiles.DrawTileScaled(indexX, indexY, position, scale);
				position.x += static_cast<float>(m_FloorTiles.GetTileWidth()) * scale;
			}

			position.x = 0;
			position.y += static_cast<float>(m_FloorTiles.GetTileHeight()) * scale;
		}
	}

	auto MainMenu::RenderForeground() const -> void
	{
	}

	auto MainMenu::RenderUI() const -> void
	{
	}
} // namespace Redge
