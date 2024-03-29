#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "raylib.h"
#include "Raylib/Tileset.h"
#include "Tiled/Object.h"

namespace Redge
{
	class Spikes final : public Tiled::Object, public ICollidable
	{
	public:
		explicit Spikes(Vector2 position);

		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto RenderBelow() const -> void override;

		auto OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto GetCollisionType() const -> CollisionType override;

		[[nodiscard]] auto IsColliding(const Rectangle& rect) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& center, float radius) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& point) const -> bool override;

	private:
		auto GetHitbox() const -> Rectangle;

		static constexpr float s_LoopDuration = 5;
		static constexpr float s_HiddenDuration = 2;
		static constexpr float s_TransitionDuration = 0.2;
		float m_LoopTime = 0;

		uint8_t m_AnimationFrame = 0;
		Raylib::Tileset m_Spikes = Raylib::Tileset("assets/Tilesets/Objects/Spikes.png", 3, 1);
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Spikes>
{
	static auto from_json(const json& json) -> Redge::Spikes;
};
