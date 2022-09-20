#pragma once

#include "Enemy.h"
#include "Game/Objects/Character.h"
#include "raylib.h"
#include "Raylib/Tileset.h"
#include "raymath.h"
#include "Tiled/Object.h"

namespace Redge
{

	class Slime final : public Enemy
	{
	public:
		Slime(Vector2 position);
		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;

		auto OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto IsColliding(const Rectangle& rect) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& center, float radius) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& point) const -> bool override;

		auto DrawSprite(Rectangle destination) const -> void override;

	private:
		std::shared_ptr<Character> character;
		float s_Speed = 60;
		Raylib::Tileset m_Animation = Raylib::Tileset("assets/Entities/Slime.png", 8, 1);
		mutable uint16_t m_AnimationFrame = 0;
		static constexpr float s_FrameDuration = 0.15;
		mutable float m_Frametime = 0;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Slime>
{
	static auto from_json(const json& json) -> Redge::Slime;
};
