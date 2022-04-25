#include "DebugScene.h"

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host), m_FloorTiles("assets/FloorTiles.png", 16, 16)
	{
	}

	auto DebugScene::Update() -> void
	{
		constexpr auto distancePerSec = 500;

		auto horizontal = 0;
		horizontal -= static_cast<int>(IsKeyDown(KEY_LEFT));
		horizontal += static_cast<int>(IsKeyDown(KEY_RIGHT));
		auto vertical = 0;
		vertical -= static_cast<int>(IsKeyDown(KEY_UP));
		vertical += static_cast<int>(IsKeyDown(KEY_DOWN));

		m_Character.Position.x += static_cast<float>(horizontal) * distancePerSec * GetFrameTime();
		m_Character.Position.y += static_cast<float>(vertical) * distancePerSec * GetFrameTime();

		switch (horizontal)
		{
		case -1:
			m_Character.Direction = Orientation::Left;
			break;

		case 1:
			m_Character.Direction = Orientation::Right;
			break;

		default:
			break;
		}

		switch (vertical)
		{
		case -1:
			m_Character.Direction = Orientation::Up;
			break;

		case 1:
			m_Character.Direction = Orientation::Down;
			break;

		default:
			break;
		}
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

		m_Character.DrawScaled(scale);
	}

	auto DebugScene::RenderForeground() const -> void
	{
	}

	auto DebugScene::RenderUI() const -> void
	{
	}
} // namespace Redge
