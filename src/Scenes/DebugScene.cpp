#include "DebugScene.h"

#include <raymath.h>

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

		Vector2 movement{};
		movement.x -= static_cast<float>(IsKeyDown(KEY_LEFT));
		movement.x += static_cast<float>(IsKeyDown(KEY_RIGHT));
		movement.y -= static_cast<float>(IsKeyDown(KEY_UP));
		movement.y += static_cast<float>(IsKeyDown(KEY_DOWN));

		movement = Vector2Normalize(movement);
		movement = Vector2Scale(movement, distancePerSec * GetFrameTime());
		m_CharacterPos = Vector2Add(m_CharacterPos, movement);

		m_Character.SetPosition(Vector2{
			static_cast<float>(RoundUp(static_cast<int>(m_CharacterPos.x), scale)),
			static_cast<float>(RoundUp(static_cast<int>(m_CharacterPos.y), scale))
		});

		if (movement.y < 0)
		{
			m_Character.SetDirection(Orientation::Up);
		}
		else if (movement.y > 0)
		{
			m_Character.SetDirection(Orientation::Down);
		}
		else if (movement.x < 0)
		{
			m_Character.SetDirection(Orientation::Left);
		}
		else if (movement.x > 0)
		{
			m_Character.SetDirection(Orientation::Right);
		}

		static float s_TimeSinceLastDraw = 0;
		constexpr float timeBetweenFrames = 0.1;

		if (Vector2Length(movement) != 0)
		{
			s_TimeSinceLastDraw += GetFrameTime();
			if (s_TimeSinceLastDraw >= timeBetweenFrames)
			{
				s_TimeSinceLastDraw -= timeBetweenFrames;
				m_Character.NextFrame();
			}
		}
		else
		{
			s_TimeSinceLastDraw = 0;
			m_Character.ResetFrame();
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
