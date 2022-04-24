#include "DebugScene.h"

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host), m_FloorTiles("assets/FloorTiles.png", 16, 16)
	{
	}

	auto DebugScene::Update() -> void
	{
	}

	auto DebugScene::RenderWorld() const -> void
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

	auto DebugScene::RenderForeground() const -> void
	{
	}

	auto DebugScene::RenderUI() const -> void
	{
	}
} // namespace Redge
