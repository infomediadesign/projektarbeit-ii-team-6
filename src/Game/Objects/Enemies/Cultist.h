#pragma once

#include "Enemy.h"
#include "Game/Objects/Character.h"
#include "raylib.h"
#include "Raylib/Tileset.h"
#include "raymath.h"
#include "Tiled/Object.h"

namespace Redge
{

	class Cultist final : public Enemy
	{
	public:
		Cultist(Vector2 position);
		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;

		auto OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType)
			-> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto IsColliding(const Rectangle& rect) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& center, float radius) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& point) const -> bool override;

		auto DrawSprite(Rectangle destination) const -> void override;

	private:
		std::shared_ptr<Character> character;
		float s_Speed = 35;
		Animation m_Direction = Animation::Down;
		Raylib::Tileset m_Animation = Raylib::Tileset("assets/Entities/Cultist.png", 4, 4);
		Raylib::Tileset m_BattleAnimation = Raylib::Tileset("assets/UI/Combat/idle/cultistIdle.png", 2, 1);
		uint16_t m_AnimationFrame = 0;
		static constexpr float s_FrameDuration = 0.3;
		float m_Frametime = 0;

		mutable uint16_t m_BattleAnimationFrame = 0;
		static constexpr float s_BattleFrameDuration = 0.3;
		mutable float m_BattleFrametime = 0;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Cultist>
{
	static auto from_json(const json& json) -> Redge::Cultist;
};
