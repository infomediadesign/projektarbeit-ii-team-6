#include "Wall.h"

namespace Redge
{
	Wall::Wall(Rectangle area) : m_Area(area)
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
		return other->IsColliding(m_Area);
	}

	auto Wall::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionRecs(rect, m_Area);
	}

	auto Wall::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircleRec(center, radius, m_Area);
	}

	auto Wall::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointRec(point, m_Area);
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Wall>::from_json(const json& json) -> Redge::Wall
{
	return Redge::Wall(Rectangle{
		json["x"].get<float>(),
		json["y"].get<float>(),
		json["width"].get<float>(),
		json["height"].get<float>(),
	});
}
