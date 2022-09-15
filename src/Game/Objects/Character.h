#pragma once

#include "Game/Objects/Enemies/Enemy.h"
#include "Game/Objects/Items/Item.h"
#include "Game/Objects/Types/Collidable.h"
#include "Game/Objects/Weapons/Weapon.h"
#include "Raylib/Tileset.h"
#include "Tiled/Object.h"

namespace Redge
{
	enum class Animation
	{
		Down,
		Up,
		Right,
		Left,
	};

	class Character final : public Tiled::Object, public ICollidable, public std::enable_shared_from_this<Character>
	{
	public:
		static auto Create(Vector2 position, float speed, float maxHealth, float maxOxygen)
			-> std::shared_ptr<Character>;

		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;
		auto RenderBelow() const -> void override;
		auto RenderUI() const -> void override;

		auto OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType)
			-> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto GetCollisionType() const -> CollisionType override;

		auto IsColliding(const Rectangle& rect) const -> bool override;
		auto IsColliding(const Vector2& center, float radius) const -> bool override;
		auto IsColliding(const Vector2& point) const -> bool override;

		//Combat Getter-Functions
		auto GetMaxHealth() const -> float;
		auto GetMaxOxygen() const -> float;
		auto GetHealth() const -> float;
		auto GetOxygen() const -> float;
		auto GetInitiative() const -> float;
		auto GetStatuseffects() -> Statuseffects&;

		//Combat Setter-Functions
		auto SetHealth(float health) -> void;
		auto SetOxygen(float oxygen) -> void;


	private:
		Character(Vector2 position, float speed, float maxHealth, float maxOxygen);

		Statuseffects m_Statuseffects;

		auto SetNextAnimationFrame() -> void;

		auto GetHitBox() const -> Rectangle;
		auto GetTextureOffset() const -> Vector2;

		Raylib::Tileset m_Animations = Raylib::Tileset("assets/Entities/Character.png", 5, 4);
		Texture2D m_Mask = LoadTexture("assets/Lighting/player_mask.png");
		Animation m_Animation = Animation::Down;

		uint16_t m_CurrentFrame = 0;
		constexpr static float s_FrameDuration = 0.2;
		float m_CurrentFrameTime = 0;

		Vector2 m_PreviousPosition;
		bool m_DontMove = false;
		bool m_SlowMove = false;

		uint16_t m_EnemyId{};
		std::shared_ptr<Enemy> m_Enemy{};

		float m_CharacterSpeed;
		float m_SpeedMultiplier = 1;

		Raylib::Tileset m_HealthBar = Raylib::Tileset("assets/UI/HealthBar.png", 1, 3);
		float m_MaxHealth;
		float m_Health;
		float m_MaxOxygen;
		float m_Oxygen;
		float m_Initiative;

		Raylib::Tileset m_CrystalIcon = Raylib::Tileset("assets/UI/CrystalIcon.png", 1, 1);
		uint32_t m_CrystalCount = 0;

		Raylib::Tileset m_InventoryIcon = Raylib::Tileset("assets/UI/InventoryItem.png", 1, 1);
		std::array<std::unique_ptr<Item>, 5> m_Items{};

		std::array<std::unique_ptr<Weapon>, 3> m_Weapons{};

		bool m_IsCollidingSpikes = false;
		bool m_WasTakeSpikeDamage = false;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<std::shared_ptr<Redge::Character>>
{
	static auto from_json(const json& json) -> std::shared_ptr<Redge::Character>;
};
