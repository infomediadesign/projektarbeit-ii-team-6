#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "raylib.h"
#include "Raylib/Tileset.h"
#include "Tiled/Object.h"

namespace Redge
{
	class UpgradeStation final : public Tiled::Object, public ICollidable
	{
	public:
		explicit UpgradeStation(Vector2 position);

		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;

		auto OnCollision(Tiled::Object& other, CollisionType collisionType) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto GetCollisionType() const -> CollisionType override;

		auto IsColliding(const Rectangle& rect) const -> bool override;
		auto IsColliding(const Vector2& center, float radius) const -> bool override;
		auto IsColliding(const Vector2& point) const -> bool override;

	private:
		auto GetHitBox() const -> Rectangle;

		static constexpr float s_FrameDuration = 0.2;
		float m_FrameTime = 0;

		Raylib::Tileset m_Column = Raylib::Tileset("assets/Tilesets/Objects/UpgradeStand.png", 1, 1);
		Raylib::Tileset m_Ghosts = Raylib::Tileset("assets/Tilesets/Objects/UpgradeGhosts.png", 4, 5);
		uint8_t m_AnimationFrame = 0;
		uint8_t m_AnimationColor;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::UpgradeStation>
{
	static auto from_json(const json& json) -> Redge::UpgradeStation;
};
