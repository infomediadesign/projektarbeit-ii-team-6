#pragma once

#include "raylib.h"
#include "Tiled/Object.h"

namespace Redge
{
	constexpr auto bit(uint8_t index) -> int
	{
		return 1 << index;
	}

	enum CollisionType
	{
		CollisionTypeNone = 0,
		CollisionTypeSolid = bit(0),
		CollisionTypeSlow = bit(1),
		CollisionTypeEnemy = bit(2),
		CollisionTypeCharacter = bit(3),
		CollisionTypeSpikes = bit(3),
	};

	class ICollidable
	{
	public:
		virtual ~ICollidable() = default;

		virtual auto OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType) -> void = 0;
		virtual auto CheckCollision(ICollidable* other) const -> bool = 0;

		[[nodiscard]] virtual auto GetCollisionType() const -> CollisionType = 0;

		[[nodiscard]] virtual auto IsColliding(const Rectangle& rect) const -> bool = 0;
		[[nodiscard]] virtual auto IsColliding(const Vector2& center, float radius) const -> bool = 0;
		[[nodiscard]] virtual auto IsColliding(const Vector2& point) const -> bool = 0;
	};
} // namespace Redge
