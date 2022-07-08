#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "raylib.h"
#include "Tiled/Object.h"

namespace Redge
{
	class Wall final : public Tiled::Object, public ICollidable
	{
	public:
		explicit Wall(Vector2 position, Vector2 dimensions);

		auto OnCollision(Tiled::Object& other) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		[[nodiscard]] auto IsColliding(const Rectangle& rect) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& center, float radius) const -> bool override;
		[[nodiscard]] auto IsColliding(const Vector2& point) const -> bool override;

	private:
		auto GetHitbox() const -> Rectangle;

		Vector2 m_Dimensions;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Wall>
{
	static auto from_json(const json& json) -> Redge::Wall;
};
