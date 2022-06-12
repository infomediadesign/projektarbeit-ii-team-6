#include "Character.h"

#include "Graphics/Tilemap.h"

#include <string>

#include <raylib.h>
#include <raymath.h>

namespace Redge
{
	auto TextureDeleter::operator()(Texture2D* texture) const noexcept -> void
	{
		UnloadTexture(*texture);
		delete texture;
	}

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

		if (m_AirSupply > 0)
			m_AirSupply -= GetFrameTime();
		else
		{
			m_TimeSinceDamage += GetFrameTime();
			if (m_TimeSinceDamage >= 1)
			{
				m_TimeSinceDamage -= 1;
				m_Health -= 1;
			}
		}

		if (m_Health <= 0)
			; // Kill off player

		if (IsKeyPressed(KEY_C))
			++m_CrystalCount;

		if (IsKeyPressed(KEY_SPACE))
			m_PrimaryWeapon = !m_PrimaryWeapon;
	}

	auto Character::Render() const -> void
	{
		m_Character.DrawTile(m_CurrentFrame, static_cast<uint16_t>(m_Direction), m_Position);
	}

	auto Character::RenderUI() const -> void
	{
		auto topLeft = Vector2{30, 30};
		auto topRight = Vector2{static_cast<float>(GetScreenWidth()) - 30, 30};
		auto bottomLeft = Vector2{30, static_cast<float>(GetScreenHeight()) - 30};
		auto bottomRight =
			Vector2{static_cast<float>(GetScreenHeight()) - 30, static_cast<float>(GetScreenWidth()) - 30};

		// Health bar (top left)

		constexpr auto healthScale = 3;

		m_HealthBar.DrawTileScaled(0, 2, topLeft, healthScale);

		const auto healthWidth = m_HealthBar.GetTileWidth();
		const auto healthHeight = m_HealthBar.GetTileHeight();

		m_HealthBar.DrawTilePartScaled(0, 1, topLeft,
			Vector2{static_cast<float>(healthWidth) * (m_Health / s_MaxHealth), static_cast<float>(healthHeight)},
			healthScale);

		m_HealthBar.DrawTilePartScaled(0, 0, topLeft,
			Vector2{static_cast<float>(healthWidth) * (m_AirSupply / s_MaxAirSupply), static_cast<float>(healthHeight)},
			healthScale);

		topLeft.x += healthWidth;
		topLeft.y += healthHeight;

		// Crystal count (top right)

		constexpr auto fontSize = 50;
		float crystalScale = fontSize / m_CrystalTexture->height;

		topRight = Vector2Subtract(topRight, Vector2{m_CrystalTexture->width * crystalScale, 0});

		DrawTextureEx(*m_CrystalTexture, topRight, 0, crystalScale, WHITE);

		auto crystalText = std::to_string(m_CrystalCount);

		topRight.x -= MeasureText(crystalText.c_str(), fontSize) + 10;
		topRight.y += m_CrystalTexture->height * crystalScale / 2 - fontSize / 2;

		DrawText(crystalText.c_str(), topRight.x, topRight.y, fontSize, WHITE);

		// Weapons (bottom left)
		float itemSlotsScale = 3;

		bottomLeft.y -= m_WeaponSlotTexture->height * itemSlotsScale;

		if (!m_PrimaryWeapon) // HACK: need to mirror the image only horizontal, this mirrors both axis
		{
			bottomLeft = Vector2Add(bottomLeft,
				Vector2{m_WeaponSlotTexture->width * itemSlotsScale, m_WeaponSlotTexture->height * itemSlotsScale});
			itemSlotsScale *= -1;
		}

		DrawTextureEx(*m_WeaponSlotTexture, bottomLeft, 0, itemSlotsScale, WHITE);
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
