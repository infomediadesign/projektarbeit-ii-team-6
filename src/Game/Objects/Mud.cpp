#include "Mud.h"

namespace Redge
{
	Mud::Mud(Vector2 position, Vector2 dimensions) :
		Tiled::Object(position), m_Dimensions(dimensions)
	{
	}

	auto Mud::OnCollision(Tiled::Object& other, CollisionType collisionType) -> void
	{
	}

	auto Mud::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(GetHitbox());
	}

	auto Mud::GetCollisionType() const -> CollisionType
	{
		return CollisionTypeSlow;
	}

	auto Mud::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionRecs(rect, GetHitbox());
	}

	auto Mud::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircleRec(center, radius, GetHitbox());
	}

	auto Mud::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointRec(point, GetHitbox());
	}
	auto Mud::GetHitbox() const -> Rectangle
	{
		return Rectangle{
			Position.x,
			Position.y,
			m_Dimensions.x,
			m_Dimensions.y,
		};
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Mud>::from_json(const json& json) -> Redge::Mud
{
	return Redge::Mud(
		Vector2{
			json["x"].get<float>(),
			json["y"].get<float>(),
		},
		Vector2{
			json["width"].get<float>(),
			json["height"].get<float>(),
		});
}
