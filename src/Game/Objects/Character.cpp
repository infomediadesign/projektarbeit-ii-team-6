#include "Character.h"

#include "Game/Game.h"
#include "Game/Scenes/CombatScene.h"
#include "Game/Scenes/MainMenu.h"
#include "raymath.h"
#include "Tiled/Layer.h"
#include "Tiled/Property.h"

namespace Redge
{
	auto Character::Create(Vector2 position, float speed, float maxHealth, float maxOxygen)
		-> std::shared_ptr<Character>
	{
		return std::shared_ptr<Character>(new Character(position, speed, maxHealth, maxOxygen));
	}

	Character::Character(Vector2 position, float speed, float maxHealth, float maxOxygen) :
		Tiled::Object(position), m_PreviousPosition(position), m_CharacterSpeed(speed), m_Health(maxHealth),
		m_MaxHealth(maxHealth), m_Oxygen(maxOxygen), m_MaxOxygen(maxOxygen)
	{
	}

	auto Character::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
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

			m_PreviousPosition = Position;
			Position = Vector2Add(Position, movement);

			m_CurrentFrameTime += GetFrameTime();
			if (m_CurrentFrameTime >= s_FrameDuration)
			{
				m_CurrentFrameTime -= s_FrameDuration;
				SetNextAnimationFrame();
			}
		}

		// NOTE: this will possibly be set in OnCollision
		m_WasTakeSpikeDamage = m_IsCollidingSpikes;
		m_IsCollidingSpikes = false;
	}

	auto Character::LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		if (m_DontMove)
		{
			Position = m_PreviousPosition;
			m_DontMove = false;
		}

		if (m_SlowMove)
		{
			auto delta = Vector2Subtract(Position, m_PreviousPosition);
			delta = Vector2Scale(delta, 0.5);
			Position = Vector2Add(m_PreviousPosition, delta);
			m_SlowMove = false;
		}

		if (m_Enemy)
		{
			auto combatScene = std::make_shared<CombatScene>(scene->Host);
			combatScene->SetBackScene(scene->Host->SetScene(combatScene));

			combatScene->SetCharacter(shared_from_this());
			combatScene->SetEnemy(m_Enemy);

			// NOTE: Possibly do this when exiting combat?
			layer.Objects.erase(m_EnemyId);

			m_EnemyId = 0;
			m_Enemy = nullptr;
		}

		if (!m_WasTakeSpikeDamage && m_IsCollidingSpikes)
			m_Health -= 5;

		if (scene->IsToxic())
		{
			if (m_Oxygen > 0)
				m_Oxygen -= GetFrameTime() / 3;
			else if (m_Health > 0)
				m_Health -= GetFrameTime() / 3;
			else
			{
				// TODO: replace with death scene
				scene->Host->SetScene(std::make_shared<MainMenu>(scene->Host));
			}
		}

		scene->Camera.target = Position;
		scene->Camera.offset.x = GetScreenWidth() / 2;
		scene->Camera.offset.y = GetScreenHeight() / 2;
	}

	auto Character::Render() const -> void
	{
		m_Animations.DrawTile(m_CurrentFrame, static_cast<uint16_t>(m_Animation),
			Vector2Add(Position, GetTextureOffset()));
	}

	auto Character::RenderBelow() const -> void
	{
		BeginBlendMode(BLEND_ADDITIVE);
		DrawTexture(m_Mask, Position.x - m_Mask.width / 2, Position.y - m_Mask.height / 2, Color{242, 211, 161, 30});
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
	}

	auto Character::OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType)
		-> void
	{
		if ((collisionType & CollisionTypeSolid) == CollisionTypeSolid)
			m_DontMove = true;

		if ((collisionType & CollisionTypeSlow) == CollisionTypeSlow)
			m_SlowMove = true;

		if ((collisionType & CollisionTypeEnemy) == CollisionTypeEnemy)
		{
			m_EnemyId = id;
			m_Enemy = std::dynamic_pointer_cast<Enemy>(other);
			assert(m_Enemy != nullptr);
		}

		if ((collisionType & CollisionTypeSpikes) == CollisionTypeSpikes)
			m_IsCollidingSpikes = true;
	}

	auto Character::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(GetHitBox());
	}

	auto Character::GetCollisionType() const -> CollisionType
	{
		return CollisionTypeCharacter;
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

	auto Character::SetNextAnimationFrame() -> void
	{
		++m_CurrentFrame;
		if (m_CurrentFrame >= m_Animations.GetTileCountX())
			m_CurrentFrame = 1;
	}

	auto Character::GetHitBox() const -> Rectangle
	{
		auto offset = GetTextureOffset();

		Rectangle hitbox{};

		hitbox.width = m_Animations.GetTileWidth() * 0.8;
		hitbox.height = m_Animations.GetTileHeight() / 2;

		hitbox.x = Position.x - hitbox.width / 2;
		hitbox.y = Position.y - hitbox.height;

		return hitbox;
	}

	auto Character::GetTextureOffset() const -> Vector2
	{
		return Vector2{
			static_cast<float>(-m_Animations.GetTileWidth()) / 2,
			static_cast<float>(-m_Animations.GetTileHeight()),
		};
	}
	auto Character::GetMaxHealth() const -> float
	{
		return m_MaxHealth;
	}
	auto Character::GetMaxOxygen() const -> float
	{
		return m_MaxOxygen;
	}
	auto Character::GetHealth() const -> float
	{
		return m_Health;
	}
	auto Character::GetOxygen() const -> float
	{
		return m_Oxygen;
	}
	auto Character::SetHealth(float health) -> void
	{
		m_Health = health;
	}
	auto Character::SetOxygen(float oxygen) -> void
	{
		m_Oxygen = oxygen;
	}
	auto Character::GetInitiative() const -> float
	{
		return m_Initiative;
	}
	auto Character::GetStatuseffects() -> Statuseffects&
	{
		return m_Statuseffects;
	}
	auto Character::DrawSprite(Rectangle area) const -> void
	{
		m_Animations.DrawTileTo(0, 1, area);
	}
	auto Character::GetWeapon(uint8_t index) -> std::shared_ptr<Weapon>
	{
		return m_Weapons.at(index);
	}
} // namespace Redge

auto nlohmann::adl_serializer<std::shared_ptr<Redge::Character>>::from_json(const json& json)
	-> std::shared_ptr<Redge::Character>
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

	return Redge::Character::Create(pos, speed, health, oxygen);
}
