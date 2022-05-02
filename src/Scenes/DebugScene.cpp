#include "DebugScene.h"

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host), m_FloorTiles("assets/FloorTiles.png", 16, 16)
	{
	}

	constexpr int scale = 10;

	auto RoundUp(int value, int multiple) -> int
	{
		if (multiple == 0)
			return value;

		auto remainder = value % multiple;
		if (remainder == 0)
			return value;

		return value + multiple - remainder;
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

		m_CharacterPos.x += static_cast<float>(horizontal) * distancePerSec * GetFrameTime();
		m_CharacterPos.y += static_cast<float>(vertical) * distancePerSec * GetFrameTime();

		m_Character.Position.x = RoundUp(static_cast<int>(m_CharacterPos.x), scale);
		m_Character.Position.y = RoundUp(static_cast<int>(m_CharacterPos.y), scale);

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

		static float timeSinceLastDraw = 0;
		constexpr float timeBetweenFrames = 0.2;

		if (horizontal != 0 || vertical != 0)
		{
			timeSinceLastDraw += GetFrameTime();
			if (timeSinceLastDraw >= timeBetweenFrames)
			{
				timeSinceLastDraw -= timeBetweenFrames;
				m_Character.NextFrame();
			}
		}
		else
		{
			timeSinceLastDraw = 0;
			m_Character.currentframe = 0;
		}
	}

	auto DebugScene::RenderWorld() const -> void
	{
		Vector2 position{};

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
