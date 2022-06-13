#pragma once

#include "Graphics/Tileset.h"
#include "Tiled/Object.h"

namespace Redge
{
	enum class Animation
	{
		Down,
		Up,
		Right,
		Left,
	};

	class Character final : public Tiled::Object
	{
	public:
		Character(Vector2 position, float speed);

		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;

	private:
		auto HandleMovement() -> void;

		auto SetAnimation(Animation animation) -> void;
		auto SetNextAnimationFrame() -> void;

		auto GetTextureOffset() const -> Vector2;

		Tileset m_Animations = Tileset("assets/Entities/Character.png", 16, 24);
		Animation m_Animation = Animation::Down;

		uint16_t m_CurrentFrame = 0;
		constexpr static float s_FrameDuration = 0.2;
		float m_CurrentFrameTime = 0;

		Vector2 m_Position;

		float m_CharacterSpeed;
		float m_SpeedMultiplier = 1;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Character>
{
	static auto from_json(const json& json) -> Redge::Character;
};
