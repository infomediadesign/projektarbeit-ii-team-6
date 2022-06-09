#pragma once

#include "Entity.h"
#include "Graphics/Tileset.h"

namespace Redge
{
	enum class Orientation
	{
		Down,
		Up,
		Right,
		Left
	};

	class Character : public Entity
	{
	public:
		Character(Vector2 position);

		auto Update(Tiled::Layer& layer) -> void override;

		auto Render() const -> void override;
		auto RenderUI() const -> void override;

		auto SetCameraTarget(Camera2D& camera) const -> void;

	private:
		auto NextFrame() -> void;
		auto ResetFrame() -> void;

		auto UpdateDirection(Orientation dir) -> void;

		Tileset m_Character = Tileset("assets/Entities/Character.png", 16, 24);
		Vector2 m_Position = Vector2{0, 0};

		Orientation m_Direction = Orientation::Down;
		uint16_t m_CurrentFrame = 0;

		float m_TimeSinceLastStep = 0;
		float m_TimeSinceLastFrame = 0;
	};
} // namespace Redge
