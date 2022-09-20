#include "Slime.h"

#include "Tiled/Layer.h"

namespace Redge
{
	Slime::Slime(Vector2 position) : Enemy(position, 75, 5, 10)
	{
	}

	auto Slime::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
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
	}

	auto Slime::Render() const -> void
	{
		m_Animation.DrawTile(m_AnimationFrame, 0,
			Vector2Add(Position,
				Vector2{
					static_cast<float>(-m_Animation.GetTileWidth()) / 2,
					static_cast<float>(-m_Animation.GetTileHeight()) / 2,
				}));
	}
	static float Size = 6;
	auto Slime::OnCollision(uint16_t id, const std::shared_ptr<Tiled::Object>& other, CollisionType collisionType)
		-> void
	{
	}

	auto Slime::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(Position, Size);
	}

	auto Slime::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionCircleRec(Position, Size, rect);
	}

	auto Slime::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircles(center, radius, Position, Size);
	}

	auto Slime::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointCircle(point, Position, Size);
	}

	auto Slime::DrawSprite(Rectangle destination) const -> void
	{
		m_Animation.DrawTileTo(m_AnimationFrame, 0, destination);

		// HACK: This is a terrible hack that doesn't need to be (with use of mutable)
		m_Frametime += GetFrameTime();
		if (m_Frametime >= s_FrameDuration)
		{
			m_Frametime -= s_FrameDuration;
			++m_AnimationFrame %= m_Animation.GetTileCountX();
		}
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Slime>::from_json(const json& json) -> Redge::Slime
{
	assert(json["point"].get<bool>());
	return Redge::Slime(Vector2{json["x"].get<float>(), json["y"].get<float>()});
}
