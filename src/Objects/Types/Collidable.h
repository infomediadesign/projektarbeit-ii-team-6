#pragma once

#include "Tiled/Object.h"

#include <raylib.h>

namespace Redge
{
	class ICollidable
	{
	public:
		virtual ~ICollidable() = default;

		virtual auto OnCollision(Tiled::Object& other) -> void = 0;
		virtual auto CheckCollision(ICollidable* other) const -> bool = 0;

		virtual auto IsColliding(const Rectangle& rect) const -> bool = 0;
		virtual auto IsColliding(const Vector2& center, float radius) const -> bool = 0;
		virtual auto IsColliding(const Vector2& point) const -> bool = 0;
	};
} // namespace Redge
