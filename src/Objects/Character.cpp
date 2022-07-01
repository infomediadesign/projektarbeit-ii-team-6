#include "Character.h"

#include "Tiled/Layer.h"
#include "Tiled/Property.h"

#include <raymath.h>

namespace Redge
{
	Character::Character(Vector2 position, float speed, float maxHealth, float maxOxygen) :
		m_CurrentPosition(position), m_PreviousPosition(position), m_CharacterSpeed(speed), m_Health(maxHealth),
		m_MaxHealth(maxHealth), m_Oxygen(maxOxygen), m_MaxOxygen(maxOxygen)
	{
	}

	auto Character::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		// NOTE: utility key binds for now
		if (IsKeyPressed(KEY_TAB))
			m_PrimaryWeaponSelected = !m_PrimaryWeaponSelected;

		if (IsKeyPressed(KEY_C))
			++m_CrystalCount;

		if (IsKeyPressed(KEY_R))
		{
			m_Health = m_MaxHealth;
			m_Oxygen = m_MaxOxygen;
		}

		Vector2 movement{};
		movement.x -= static_cast<float>(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
		movement.x += static_cast<float>(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT));
		movement.y -= static_cast<float>(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
		movement.y += static_cast<float>(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN));

		if (movement.y < 0)
			m_Animation = Animation::Up;
		else if (movement.y > 0)
			m_Animation = Animation::Down;
		else if (movement.x < 0)
			m_Animation = Animation::Left;
		else if (movement.x > 0)
			m_Animation = Animation::Right;

		if (Vector2Length(movement) == 0)
		{
			m_CurrentFrame = 0;
			m_CurrentFrameTime = 0;
		}
		else
		{
			movement = Vector2Normalize(movement);
			movement = Vector2Scale(movement, m_CharacterSpeed * m_SpeedMultiplier * GetFrameTime());

			m_PreviousPosition = m_CurrentPosition;
			m_CurrentPosition = Vector2Add(m_CurrentPosition, movement);

			m_CurrentFrameTime += GetFrameTime();
			if (m_CurrentFrameTime >= s_FrameDuration)
			{
				m_CurrentFrameTime -= s_FrameDuration;
				SetNextAnimationFrame();
			}
		}
	}

	auto Character::LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		if (m_Collided)
		{
			m_CurrentPosition = m_PreviousPosition;
			m_Collided = false;
		}

		if (m_Oxygen > 0)
			m_Oxygen -= GetFrameTime();
		else if (m_Health > 0)
			m_Health -= GetFrameTime();
		else
		{
			// Delete character
			for (auto it = layer.Objects.begin(); it != layer.Objects.end(); ++it)
			{
				if (it->second.get() == this)
				{
					layer.Objects.erase(it);
					break;
				}
			}
		}

		scene->Camera.target = m_CurrentPosition;
		scene->Camera.offset.x = GetScreenWidth() / 2;
		scene->Camera.offset.y = GetScreenHeight() / 2;
	}

	auto Character::Render() const -> void
	{
		m_Animations.DrawTile(m_CurrentFrame, static_cast<uint16_t>(m_Animation),
			Vector2Add(m_CurrentPosition, GetTextureOffset()));

		BeginBlendMode(BLEND_MULTIPLIED);
		DrawCircle(m_CurrentPosition.x, m_CurrentPosition.y, 75, Color{255, 255, 255, 75});
		EndBlendMode();
	}

	constexpr auto elementPadding = 10;

	auto Character::RenderUI() const -> void
	{
		// Health bar

		constexpr auto healthBarPos = Vector2{20, 20};
		constexpr auto healthBarScale = 3;

		m_HealthBar.DrawTileScaled(0, 2, healthBarPos, healthBarScale);

		const auto healthPercent = m_Health / m_MaxHealth;
		const auto healthPart = Vector2{
			static_cast<float>(m_HealthBar.GetTileWidth()) * healthPercent,
			static_cast<float>(m_HealthBar.GetTileHeight()),
		};
		m_HealthBar.DrawTilePartScaled(0, 1, healthBarPos, healthPart, healthBarScale);

		const auto oxygenPercent = m_Oxygen / m_MaxOxygen;
		const auto oxygenPart = Vector2{
			static_cast<float>(m_HealthBar.GetTileWidth()) * oxygenPercent,
			static_cast<float>(m_HealthBar.GetTileHeight()),
		};
		m_HealthBar.DrawTilePartScaled(0, 0, healthBarPos, oxygenPart, healthBarScale);

		// Crystal count

		auto crystalIconPos = Vector2{static_cast<float>(GetScreenWidth() - 20), 20};
		constexpr auto crystalIconScale = 4;

		crystalIconPos.x -= m_CrystalIcon.GetTileWidth() * crystalIconScale;
		m_CrystalIcon.DrawTileScaled(0, 0, crystalIconPos, crystalIconScale);

		auto crystalCountPos = Vector2{crystalIconPos.x - elementPadding, crystalIconPos.y};
		constexpr int crystalCountSize = 50;

		const auto crystalCount = std::to_string(m_CrystalCount);
		crystalCountPos.x -= MeasureText(crystalCount.c_str(), 50);
		crystalCountPos.y += m_CrystalIcon.GetTileHeight() * crystalIconScale / 2;
		crystalCountPos.y -= crystalCountSize / 2;
		DrawText(crystalCount.c_str(), crystalCountPos.x, crystalCountPos.y, crystalCountSize, WHITE);

		// Inventory items

		auto inventoryPos = Vector2{
			static_cast<float>(GetScreenWidth() - 20),
			static_cast<float>(GetScreenHeight() - 20),
		};
		const auto inventoryScale = 4;

		inventoryPos.y -= m_InventoryIcon.GetTileHeight() * inventoryScale;
		for (const auto& item : m_Items)
		{
			inventoryPos.x -= m_InventoryIcon.GetTileWidth() * inventoryScale;
			m_InventoryIcon.DrawTileScaled(0, 0, inventoryPos, inventoryScale);
			inventoryPos.x -= elementPadding;
		}

		// Weapon slots

		auto weaponPos = Vector2{20, static_cast<float>(GetScreenHeight() - 20)};
		auto weaponScale = 3;

		weaponPos.y -= m_WeaponSlots.GetTileHeight() * weaponScale;

		if (!m_PrimaryWeaponSelected)
		{
			// HACK: Invert image
			weaponPos.x += m_WeaponSlots.GetTileWidth() * weaponScale;
			weaponPos.y += m_WeaponSlots.GetTileHeight() * weaponScale;
			weaponScale *= -1;
		}

		m_WeaponSlots.DrawTileScaled(0, 0, weaponPos, weaponScale);
	}

	auto Character::OnCollision(Tiled::Object& other) -> void
	{
		m_Collided = true;
	}

	auto Character::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(GetHitBox());
	}

	auto Character::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionRecs(rect, GetHitBox());
	}

	auto Character::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircleRec(center, radius, GetHitBox());
	}

	auto Character::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointRec(point, GetHitBox());
	}

	auto Character::GetPosition() const -> Vector2
	{
		return Vector2(m_CurrentPosition);
	}

	auto Character::SetNextAnimationFrame() -> void
	{
		++m_CurrentFrame;
		if (m_CurrentFrame >= m_Animations.GetTileCountX())
			m_CurrentFrame = 1;
	}

	auto Character::GetHitBox() const -> Rectangle
	{
		auto offset = GetTextureOffset();

		float width = m_Animations.GetTileWidth() * 0.8;
		float height = m_Animations.GetTileHeight() + offset.y;

		float posX = m_CurrentPosition.x - width / 2;
		float posY = m_CurrentPosition.y;

		return Rectangle{posX, posY, width, height};
	}

	auto Character::GetTextureOffset() const -> Vector2
	{
		return Vector2{
			static_cast<float>(-m_Animations.GetTileWidth()) / 2,
			static_cast<float>(-m_Animations.GetTileHeight()) / 2,
		};
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Character>::from_json(const json& json) -> Redge::Character
{
	assert(json["point"].get<bool>());

	auto speed = 100.f;
	auto health = 100.f;
	auto oxygen = 100.f;

	if (const auto properties = json.find("properties"); properties != json.end())
	{
		const auto propertyMap = properties->get<Tiled::PropertyMap>();
		if (const auto speedEntry = propertyMap.find("Speed"); speedEntry != propertyMap.end())
			speed = std::get<float>(speedEntry->second);

		if (const auto healthEntry = propertyMap.find("health"); healthEntry != propertyMap.end())
			health = std::get<float>(healthEntry->second);

		if (const auto oxygenEntry = propertyMap.find("oxygen"); oxygenEntry != propertyMap.end())
			oxygen = std::get<float>(oxygenEntry->second);
	}

	const auto pos = Vector2{
		json["x"].get<float>(),
		json["y"].get<float>(),
	};

	return Redge::Character(pos, speed, health, oxygen);
}
