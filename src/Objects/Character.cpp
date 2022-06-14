#include "Character.h"

#include "Tiled/Layer.h"
#include "Tiled/Property.h"

#include <raymath.h>

namespace Redge
{
	Character::Character(Vector2 position, float speed) :
		m_CurrentPosition(position), m_PreviousPosition(position), m_CharacterSpeed(speed)
	{
	}

	auto Character::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		Vector2 movement{};
		movement.x -= static_cast<float>(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
		movement.x += static_cast<float>(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT));
		movement.y -= static_cast<float>(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
		movement.y += static_cast<float>(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN));

		if (movement.y < 0)
			SetAnimation(Animation::Up);
		else if (movement.y > 0)
			SetAnimation(Animation::Down);
		else if (movement.x < 0)
			SetAnimation(Animation::Left);
		else if (movement.x > 0)
			SetAnimation(Animation::Right);

		if (Vector2Length(movement) == 0)
		{
			m_CurrentFrame = 0;
			m_CurrentFrameTime = 0;
			return;
		}
		else
		{
			movement = Vector2Normalize(movement);
			movement = Vector2Scale(movement, m_CharacterSpeed * m_SpeedMultiplier * GetFrameTime());

			m_PreviousPosition = m_CurrentPosition;
			m_CurrentPosition = Vector2Add(m_CurrentPosition, movement);

			m_CurrentFrameTime += GetFrameTime();
			if (m_CurrentFrameTime >= s_FrameDuration)
			{
				m_CurrentFrameTime -= s_FrameDuration;
				SetNextAnimationFrame();
			}
		}
	}

	auto Character::LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		if (m_Collided)
		{
			m_CurrentPosition = m_PreviousPosition;
			m_Collided = false;
		}

		scene->Camera.target = m_CurrentPosition;
		scene->Camera.offset.x = GetScreenWidth() / 2;
		scene->Camera.offset.y = GetScreenHeight() / 2;
	}

	auto Character::Render() const -> void
	{
		const auto position = Vector2Add(m_CurrentPosition, GetTextureOffset());
		m_Animations.DrawTile(m_CurrentFrame, static_cast<uint16_t>(m_Animation), position);
	}

	auto Character::RenderUI() const -> void
	{
	}

	auto Character::OnCollision(Tiled::Object& other) -> void
	{
		m_Collided = true;
	}

	auto Character::CheckCollision(ICollidable* other) const -> bool
	{
		return other->IsColliding(GetHitBox());
	}

	auto Character::IsColliding(const Rectangle& rect) const -> bool
	{
		return CheckCollisionRecs(rect, GetHitBox());
	}

	auto Character::IsColliding(const Vector2& center, float radius) const -> bool
	{
		return CheckCollisionCircleRec(center, radius, GetHitBox());
	}

	auto Character::IsColliding(const Vector2& point) const -> bool
	{
		return CheckCollisionPointRec(point, GetHitBox());
	}

	auto Character::SetAnimation(Animation animation) -> void
	{
		if (m_Animation == animation)
			return;

		m_Animation = animation;

		m_CurrentFrame = 0;
		m_CurrentFrameTime = 0;
	}

	auto Character::SetNextAnimationFrame() -> void
	{
		++m_CurrentFrame;
		if (m_CurrentFrame >= m_Animations.GetTileCountX())
			m_CurrentFrame = 0;
	}

	auto Character::GetHitBox() const -> Rectangle
	{
		auto offset = GetTextureOffset();

		return Rectangle{
			m_CurrentPosition.x + offset.x,
			m_CurrentPosition.y + offset.y,
			static_cast<float>(m_Animations.GetTileWidth()),
			static_cast<float>(m_Animations.GetTileHeight()),
		};
	}

	auto Character::GetTextureOffset() const -> Vector2
	{
		return Vector2{
			static_cast<float>(-m_Animations.GetTileWidth()) / 2,
			static_cast<float>(-m_Animations.GetTileHeight()) / 2,
		};
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Character>::from_json(const json& json) -> Redge::Character
{
	assert(json["point"].get<bool>());

	auto speed = 100.f;

	if (const auto properties = json.find("properties"); properties != json.end())
	{
		const auto propertyMap = properties->get<Tiled::PropertyMap>();
		if (const auto speedEntry = propertyMap.find("Speed"); speedEntry != propertyMap.end())
			speed = std::get<float>(speedEntry->second);
	}

	return Redge::Character(
		Vector2{
			json["x"].get<float>(),
			json["y"].get<float>(),
		},
		speed);
}
