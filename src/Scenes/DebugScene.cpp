#include "DebugScene.h"

#include <raymath.h>

namespace Redge
{
	DebugScene::DebugScene(Game* host) :
		Scene(host), m_Tilemap(Tilemap::FromTiled("assets/Levels/Tilemap.json"))
	{
		Camera.zoom = 5;
	}

	auto DebugScene::Update() -> void
	{
		Vector2 movement{};
		movement.x -= static_cast<float>(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
		movement.x += static_cast<float>(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT));
		movement.y -= static_cast<float>(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
		movement.y += static_cast<float>(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN));

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
				auto newPosition = Vector2Add(m_Character.GetPosition(), movement);
				Rectangle boundingBox{};
				boundingBox.x = newPosition.x;
				boundingBox.y = newPosition.y + m_Character.GetSize().y / 2;
				boundingBox.width = m_Character.GetSize().x;
				boundingBox.height = m_Character.GetSize().y / 2;
				if (!m_Tilemap.CheckCollision(boundingBox))
					m_Character.SetPosition(newPosition);
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
		m_Tilemap.Draw();
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
