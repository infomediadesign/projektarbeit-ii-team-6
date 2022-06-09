#include "Character.h"

#include "Graphics/Tilemap.h"

#include <raylib.h>
#include <raymath.h>

namespace Redge
{
	Character::Character(Vector2 position) : m_Position(position)
	{
	}

	auto Character::Update(Tiled::Layer& layer) -> void
	{
		Vector2 movement{};
		movement.x -= static_cast<float>(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
		movement.x += static_cast<float>(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT));
		movement.y -= static_cast<float>(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
		movement.y += static_cast<float>(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN));

		//if (movement.y != 0)
		//	movement.x = 0;

		constexpr float stepFrequency = 0.02;
		constexpr float frameFrequency = stepFrequency * 5;

		if (Vector2Length(movement) != 0)
		{
			m_TimeSinceLastStep += GetFrameTime();
			m_TimeSinceLastFrame += GetFrameTime();

			if (m_TimeSinceLastStep >= stepFrequency)
			{
				m_TimeSinceLastStep -= stepFrequency;
				auto newPosition = Vector2Add(m_Position, movement);

				Rectangle boundingBox{};
				boundingBox.x = newPosition.x;
				boundingBox.y = newPosition.y + m_Character.GetTileHeight() / 8 * 5;
				boundingBox.width = m_Character.GetTileWidth();
				boundingBox.height = m_Character.GetTileHeight() / 8 * 3;

				auto collision = false;
				for (const auto& rect : layer.Rectangles)
				{
					if (!rect.Visible)
						continue;

					if (CheckCollisionRecs(boundingBox, rect.Value))
					{
						collision = true;
						break;
					}
				}

				if (!collision)
					m_Position = newPosition;
			}

			if (m_TimeSinceLastFrame >= frameFrequency)
			{
				m_TimeSinceLastFrame -= frameFrequency;
				NextFrame();
			}
		}
		else
		{
			m_TimeSinceLastStep = 0;
			m_TimeSinceLastFrame = 0;
			ResetFrame();
		}

		if (movement.y < 0)
		{
			UpdateDirection(Orientation::Up);
		}
		else if (movement.y > 0)
		{
			UpdateDirection(Orientation::Down);
		}
		else if (movement.x < 0)
		{
			UpdateDirection(Orientation::Left);
		}
		else if (movement.x > 0)
		{
			UpdateDirection(Orientation::Right);
		}
	}

	auto Character::Render() const -> void
	{
		m_Character.DrawTile(m_CurrentFrame, static_cast<uint16_t>(m_Direction), m_Position);
	}

	auto Character::RenderUI() const -> void
	{
	}

	auto Character::SetCameraTarget(Camera2D& camera) const -> void
	{
		camera.target = m_Position;
		camera.target.x += m_Character.GetTileWidth() / 2;
		camera.target.y += m_Character.GetTileHeight() / 2;

		camera.offset.x = GetScreenWidth() / 2;
		camera.offset.y = GetScreenHeight() / 2;
	}

	auto Character::NextFrame() -> void
	{
		++m_CurrentFrame %= m_Character.GetTileCountX();
	}

	auto Character::ResetFrame() -> void
	{
		m_CurrentFrame = 0;
	}

	auto Character::UpdateDirection(Orientation dir) -> void
	{
		if (m_Direction != dir)
			ResetFrame();

		m_Direction = dir;
	}
} // namespace Redge
