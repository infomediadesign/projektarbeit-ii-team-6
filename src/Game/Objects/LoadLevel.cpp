#include "LoadLevel.h"

#include "Game/Game.h"
#include "Game/Scenes/TiledScene.h"

namespace Redge
{
	LoadLevel::LoadLevel(Vector2 position, std::string level) : Tiled::Object(position), m_Level(std::move(level))
	{
	}

	auto LoadLevel::LateUpdate(Redge::Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		if (m_LoadLevel)
		{
			scene->Host->SetScene(std::make_unique<TiledScene>(scene->Host, m_Level.c_str()));
			m_LoadLevel = false;
		}
	}
	auto LoadLevel::OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType)
		-> void
	{
		if ((collisionType & CollisionTypeCharacter) == CollisionTypeCharacter)
			m_LoadLevel = true;
	}
	auto LoadLevel::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(Position);
	}
	auto LoadLevel::GetCollisionType() const -> CollisionType
	{
		return CollisionTypeNone;
	}
	auto LoadLevel::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionPointRec(Position, rect);
	}
	auto LoadLevel::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionPointCircle(Position, center, radius);
	}
	auto LoadLevel::IsColliding(const Vector2& point) const -> bool
	{
		return Position.x == point.x && Position.y == point.y;
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::LoadLevel>::from_json(const json& json) -> Redge::LoadLevel
{
	auto properties = json["properties"].get<Tiled::PropertyMap>();
	auto level = std::get<std::string>(properties.at("level"));

	return Redge::LoadLevel(
		Vector2{
			json["x"].get<float>(),
			json["y"].get<float>(),
		},
		level);
}
