#include "DebugScene.h"

#include <raymath.h>

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host), m_FloorTiles("assets/FloorTiles.png", 16, 16)
	{
		Camera.zoom = 5;
	}

	auto DebugScene::Update() -> void
	{
		Vector2 movement{};
		movement.x -= static_cast<float>(IsKeyDown(KEY_A));
		movement.x += static_cast<float>(IsKeyDown(KEY_D));
		movement.y -= static_cast<float>(IsKeyDown(KEY_W));
		movement.y += static_cast<float>(IsKeyDown(KEY_S));

		if (movement.y != 0)
			movement.x = 0;

		constexpr float stepFrequency = 0.02;
		constexpr float frameFrequency = stepFrequency * 5;

		if (Vector2Length(movement) != 0)
		{
			m_TimeSinceLastStep += GetFrameTime();
			m_TimeSinceLastFrame += GetFrameTime();

			if (m_TimeSinceLastStep >= stepFrequency)
			{
				m_TimeSinceLastStep -= stepFrequency;
				m_Character.SetPosition(Vector2Add(m_Character.GetPosition(), movement));
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

		Camera.target = m_Character.GetPosition();
		Camera.target.x += m_Character.GetSize().x / 2;
		Camera.target.y += m_Character.GetSize().y / 2;

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
				m_FloorTiles.DrawTile(indexX, indexY, position);
				position.x += static_cast<float>(m_FloorTiles.GetTileWidth());
			}

			position.x = 0;
			position.y += static_cast<float>(m_FloorTiles.GetTileHeight());
		}
	}

	auto DebugScene::RenderForeground() const -> void
	{
		m_Character.Draw();
	}

	auto DebugScene::RenderUI() const -> void
	{
		DrawText("Debug Scene", 10, 10, 50, WHITE);
	}
} // namespace Redge
