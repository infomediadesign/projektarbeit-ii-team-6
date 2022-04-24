#include "DebugScene.h"

namespace Redge
{
	DebugScene::DebugScene(Game* host) :
		Scene(host), m_FloorTiles("assets/FloorTiles.png", 16, 16), m_Character("assets/dude2.png", 16, 32)
	{
	}

	auto DebugScene::Update() -> void
	{
	}

	auto DebugScene::RenderWorld() const -> void
	{
		Vector2 position{};
		constexpr float scale = 10;

		for (auto indexY = 0; indexY < m_FloorTiles.GetTileCountY(); ++indexY)
		{
			for (auto indexX = 0; indexX < m_FloorTiles.GetTileCountX(); ++indexX)
			{
				m_FloorTiles.DrawTileScaled(indexX, indexY, position, scale);
				position.x += static_cast<float>(m_FloorTiles.GetTileWidth()) * scale;
			}

			position.x = 0;
			position.y += static_cast<float>(m_FloorTiles.GetTileHeight()) * scale;
		}

		position = Vector2{};
		for (auto i = 0; i < m_Character.GetTileCountX(); i++)
		{
			m_Character.DrawTileScaled(i, 0, position, scale);
			position.x += static_cast<float>(m_Character.GetTileWidth()) * scale;
		}
	}

	auto DebugScene::RenderForeground() const -> void
	{
	}

	auto DebugScene::RenderUI() const -> void
	{
	}
} // namespace Redge
