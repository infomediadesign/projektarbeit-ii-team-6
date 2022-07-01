#pragma once

#include "Graphics/Tileset.h"
#include "Objects/Items/Item.h"
#include "Objects/Types/Collidable.h"
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

	class Character final : public Tiled::Object, public ICollidable
	{
	public:
		Character(Vector2 position, float speed, float maxHealth, float maxOxygen);

		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;

		auto OnCollision(Tiled::Object& other) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		auto IsColliding(const Rectangle& rect) const -> bool override;
		auto IsColliding(const Vector2& center, float radius) const -> bool override;
		auto IsColliding(const Vector2& point) const -> bool override;

		auto GetPosition() const -> Vector2;

	private:
		auto SetNextAnimationFrame() -> void;

		auto GetHitBox() const -> Rectangle;
		auto GetTextureOffset() const -> Vector2;

		Tileset m_Animations = Tileset("assets/Entities/Character.png", 16, 24);
		Animation m_Animation = Animation::Down;

		uint16_t m_CurrentFrame = 0;
		constexpr static float s_FrameDuration = 0.2;
		float m_CurrentFrameTime = 0;

		Vector2 m_CurrentPosition;
		Vector2 m_PreviousPosition;
		bool m_Collided = false;

		float m_CharacterSpeed;
		float m_SpeedMultiplier = 1;

		Tileset m_HealthBar = Tileset("assets/UI/HealthBar.png", 189, 19);
		float m_MaxHealth;
		float m_Health;
		float m_MaxOxygen;
		float m_Oxygen;

		Tileset m_CrystalIcon = Tileset("assets/UI/CrystalIcon.png", 13, 13);
		uint32_t m_CrystalCount = 0;

		Tileset m_InventoryIcon = Tileset("assets/UI/InventoryItem.png", 16, 17);
		std::array<std::unique_ptr<Item>, 5> m_Items{};

		Tileset m_WeaponSlots = Tileset("assets/UI/WeaponSlots.png", 58, 26);
		bool m_PrimaryWeaponSelected = false;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Character>
{
	static auto from_json(const json& json) -> Redge::Character;
};
