#include "UpgradeStation.h"

#include "raymath.h"

namespace Redge
{
	UpgradeStation::UpgradeStation(Vector2 position) :
		Tiled::Object(position), m_AnimationColor(GetRandomValue(0, m_Ghosts.GetTileCountY() - 1))
	{
	}

	auto UpgradeStation::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		m_FrameTime += GetFrameTime();
		if (m_FrameTime >= s_FrameDuration)
		{
			m_FrameTime -= s_FrameDuration;
			++m_AnimationFrame %= m_Ghosts.GetTileCountX();
		}
	}

	auto UpgradeStation::Render() const -> void
	{
		auto offset = Vector2{
			static_cast<float>(-m_Column.GetTileWidth()) / 2,
			static_cast<float>(-m_Column.GetTileHeight()) / 2,
		};

		auto position = Vector2Add(Position, offset);
		m_Column.DrawTile(0, 0, position);

		position.y -= m_Ghosts.GetTileHeight();
		m_Ghosts.DrawTile(m_AnimationFrame, m_AnimationColor, position);
	}

	auto UpgradeStation::OnCollision(Tiled::Object& other, CollisionType collisionType) -> void
	{
	}

	auto UpgradeStation::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(GetHitBox());
	}

	auto UpgradeStation::GetCollisionType() const -> CollisionType
	{
		return CollisionTypeSolid;
	}

	auto UpgradeStation::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionRecs(rect, GetHitBox());
	}

	auto UpgradeStation::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircleRec(center, radius, GetHitBox());
	}

	auto UpgradeStation::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointRec(point, GetHitBox());
	}

	auto UpgradeStation::GetHitBox() const -> Rectangle
	{
		auto offset = Vector2{
			static_cast<float>(-m_Column.GetTileWidth()) / 2,
			static_cast<float>(-m_Column.GetTileHeight()) / 2,
		};

		return Rectangle{
			Position.x + offset.x,
			Position.y + offset.y,
			static_cast<float>(m_Column.GetTileWidth()),
			static_cast<float>(m_Column.GetTileHeight()),
		};
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::UpgradeStation>::from_json(const json& json) -> Redge::UpgradeStation
{
	assert(json["point"].get<bool>());

	return Redge::UpgradeStation(Vector2{
		json["x"].get<float>(),
		json["y"].get<float>(),
	});
}
