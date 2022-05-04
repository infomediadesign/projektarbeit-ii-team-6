#include "DebugScene.h"

#include <raymath.h>

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host), m_FloorTiles("assets/FloorTiles.png", 16, 16)
	{
	}

	constexpr float g_Scale = 10;

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
		Vector2 movement{};
		movement.x -= static_cast<float>(IsKeyDown(KEY_LEFT));
		movement.x += static_cast<float>(IsKeyDown(KEY_RIGHT));
		movement.y -= static_cast<float>(IsKeyDown(KEY_UP));
		movement.y += static_cast<float>(IsKeyDown(KEY_DOWN));

		constexpr float stepFrequency = 0.02;
		constexpr float frameFrequency = stepFrequency * 5;

		if (Vector2Length(movement) != 0)
		{
			m_TimeSinceLastStep += GetFrameTime();
			m_TimeSinceLastFrame += GetFrameTime();

			if (m_TimeSinceLastStep >= stepFrequency)
			{
				m_TimeSinceLastStep -= stepFrequency;
				m_Character.SetPosition(Vector2Add(m_Character.GetPosition(), Vector2Scale(movement, g_Scale)));
			}

			if (m_TimeSinceLastFrame >= frameFrequency)
			{
				m_TimeSinceLastFrame -= frameFrequency;
				m_Character.NextFrame();
			}
		}
		else
		{
			m_TimeSinceLastStep = 0;
			m_TimeSinceLastFrame = 0;
			m_Character.ResetFrame();
		}

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

	}

	auto DebugScene::RenderWorld() const -> void
	{
		Vector2 position{};

		for (auto indexY = 0; indexY < m_FloorTiles.GetTileCountY(); ++indexY)
		{
			for (auto indexX = 0; indexX < m_FloorTiles.GetTileCountX(); ++indexX)
			{
				m_FloorTiles.DrawTileScaled(indexX, indexY, position, g_Scale);
				position.x += static_cast<float>(m_FloorTiles.GetTileWidth()) * g_Scale;
			}

			position.x = 0;
			position.y += static_cast<float>(m_FloorTiles.GetTileHeight()) * g_Scale;
		}

		m_Character.DrawScaled(g_Scale);
	}

	auto DebugScene::RenderForeground() const -> void
	{
	}

	auto DebugScene::RenderUI() const -> void
	{
	}
} // namespace Redge
