#include "Spikes.h"

#include "raymath.h"

namespace Redge
{
	Spikes::Spikes(Vector2 position) : Tiled::Object(position)
	{
	}

	auto Spikes::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		m_LoopTime += GetFrameTime();
		if (m_LoopTime >= s_LoopDuration)
			m_LoopTime -= s_LoopDuration;

		if (m_LoopTime < s_HiddenDuration)
			m_AnimationFrame = 0;
		else if (m_LoopTime >= s_HiddenDuration + s_TransitionDuration &&
			m_LoopTime <= s_LoopDuration - s_TransitionDuration)
			m_AnimationFrame = 2;
		else
			m_AnimationFrame = 1;
	}

	auto Spikes::RenderBelow() const -> void
	{
		auto offset = Vector2{
			static_cast<float>(-m_Spikes.GetTileWidth()) / 2,
			static_cast<float>(-m_Spikes.GetTileHeight()) / 2,
		};

		m_Spikes.DrawTile(m_AnimationFrame, 0, Vector2Add(Position, offset));
	}

	auto Spikes::OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType)
		-> void
	{
	}

	auto Spikes::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(GetHitbox());
	}

	auto Spikes::GetCollisionType() const -> CollisionType
	{
		return m_AnimationFrame == m_Spikes.GetTileCountX() - 1 ? CollisionTypeSpikes : CollisionTypeNone;
	}

	auto Spikes::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionRecs(GetHitbox(), rect);
	}

	auto Spikes::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircleRec(center, radius, GetHitbox());
	}

	auto Spikes::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointRec(point, GetHitbox());
	}

	auto Spikes::GetHitbox() const -> Rectangle
	{
		auto offset = Vector2{
			static_cast<float>(-m_Spikes.GetTileWidth()) / 2,
			static_cast<float>(-m_Spikes.GetTileHeight()) / 2,
		};

		return Rectangle{
			Position.x + offset.x,
			Position.y + offset.y,
			static_cast<float>(m_Spikes.GetTileWidth()),
			static_cast<float>(m_Spikes.GetTileHeight()),
		};
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Spikes>::from_json(const json& json) -> Redge::Spikes
{
	assert(json["point"].get<bool>());

	return Redge::Spikes(Vector2{
		json["x"].get<float>(),
		json["y"].get<float>(),
	});
}
