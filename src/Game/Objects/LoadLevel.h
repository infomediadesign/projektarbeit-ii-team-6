#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "raylib.h"
#include "Tiled/Object.h"

namespace Redge
{
	class LoadLevel : public Tiled::Object, public ICollidable
	{
	public:
		LoadLevel(Vector2 position, std::string level);

		auto LateUpdate(Redge::Scene *scene, Tiled::ObjectLayer &layer) -> void override;

		auto OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto GetCollisionType() const -> CollisionType override;

		[[nodiscard]] auto IsColliding(const Rectangle& rect) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& center, float radius) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& point) const -> bool override;

	private:
		bool m_LoadLevel = false;
		std::string m_Level;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::LoadLevel>
{
	static auto from_json(const json& json) -> Redge::LoadLevel;
};
