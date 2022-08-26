#pragma once

#include "Game/Objects/Character.h"
#include "raylib.h"
#include "Raylib/Tileset.h"
#include "raymath.h"
#include "Tiled/Object.h"


namespace Redge
{

	class Bat final : public Tiled::Object, public ICollidable
	{
	public:
		Bat(Vector2 position);
		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;

		auto OnCollision(Tiled::Object& other, CollisionType collisionType) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto GetCollisionType() const -> CollisionType override;

		auto IsColliding(const Rectangle& rect) const -> bool override;
		auto IsColliding(const Vector2& center, float radius) const -> bool override;
		auto IsColliding(const Vector2& point) const -> bool override;

	private:
		std::shared_ptr<Character> character;
		float s_Speed = 120;
		Raylib::Tileset m_Animation = Raylib::Tileset("assets/Entities/Bat.png", 6, 1);
		uint16_t m_AnimationFrame = 0;
		static constexpr float s_FrameDuration = 0.07;
		float m_Frametime = 0;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Bat>
{
	static auto from_json(const json& json) -> Redge::Bat;
};
