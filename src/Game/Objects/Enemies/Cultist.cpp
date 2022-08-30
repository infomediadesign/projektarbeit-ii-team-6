#include "Cultist.h"

#include "Tiled/Layer.h"

namespace Redge
{
	Cultist::Cultist(Vector2 position) : Object(position)
	{
	}

	auto Cultist::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		if (character == nullptr)
		{
			for (const auto& [number, object] : layer.Objects)
			{
				if (auto player = std::dynamic_pointer_cast<Character>(object))
				{
					character = player;
					break;
				}
			}
		}

		if (character != nullptr)
		{
			if (Vector2Distance(Position, character->GetPosition()) < 75)
			{
				Position = Vector2Add(Position,
					Vector2Scale(Vector2Normalize(Vector2Subtract(character->GetPosition(), Position)),
						s_Speed * GetFrameTime()));
				m_Frametime += GetFrameTime();
			}
		}

		if (m_Frametime >= s_FrameDuration)
		{
			m_Frametime -= s_FrameDuration;
			++m_AnimationFrame %= m_Animation.GetTileCountX();
		}

		float vertical = Position.y - PreviousPosition.y;
		float horizontal  = Position.x - PreviousPosition.x;

		if(abs(vertical) > abs(horizontal))
		{
			if(vertical > 0)  m_Direction = Animation::Down;
			else m_Direction = Animation::Up;
		}
		else if(abs(vertical) < abs(horizontal))
		{
			if(horizontal > 0) m_Direction = Animation::Right;
			else m_Direction = Animation::Left;
		}
		else {m_Direction = Animation::Down; m_AnimationFrame = 0;}

		PreviousPosition = Position;
	}

	auto Cultist::Render() const -> void
	{
		m_Animation.DrawTile(m_AnimationFrame, static_cast<uint16_t>(m_Direction),
			Vector2Add(Position,
				Vector2{
					static_cast<float>(-m_Animation.GetTileWidth()) / 2,
					static_cast<float>(-m_Animation.GetTileHeight()) / 2,
				}));
	}
	static float Size = 6;
	auto Cultist::OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType) -> void
	{
	}

	auto Cultist::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(Position, Size);
	}

	auto Cultist::GetCollisionType() const -> CollisionType
	{
		return CollisionTypeEnemy;
	}

	auto Cultist::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionCircleRec(Position, Size,rect);
	}

	auto Cultist::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircles(center, radius, Position, Size);
	}

	auto Cultist::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointCircle(point, Position, Size);
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Cultist>::from_json(const json& json) -> Redge::Cultist
{
	assert(json["point"].get<bool>());
	return Redge::Cultist(Vector2{json["x"].get<float>(), json["y"].get<float>()});
}
