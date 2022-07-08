#include "Wall.h"

namespace Redge
{
	Wall::Wall(Vector2 position, Vector2 dimensions) :
		Tiled::Object(position), m_Dimensions(dimensions)
	{
	}

	auto Wall::Update(Redge::Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
	}

	auto Wall::LateUpdate(Redge::Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
	}

	auto Wall::Render() const -> void
	{
	}

	auto Wall::RenderUI() const -> void
	{
	}

	auto Wall::OnCollision(Tiled::Object& other) -> void
	{
	}

	auto Wall::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(GetHitbox());
	}

	auto Wall::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionRecs(rect, GetHitbox());
	}

	auto Wall::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircleRec(center, radius, GetHitbox());
	}

	auto Wall::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointRec(point, GetHitbox());
	}
	auto Wall::GetHitbox() const -> Rectangle
	{
		return Rectangle{
			Position.x,
			Position.y,
			m_Dimensions.x,
			m_Dimensions.y,
		};
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Wall>::from_json(const json& json) -> Redge::Wall
{
	return Redge::Wall(
		Vector2{
			json["x"].get<float>(),
			json["y"].get<float>(),
		},
		Vector2{
			json["width"].get<float>(),
			json["height"].get<float>(),
		});
}
