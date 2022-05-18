#pragma once

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

	class Character
	{
	public:
		auto Draw() const -> void;
		auto DrawScaled(float scale) const -> void;

		auto NextFrame() -> void;
		auto ResetFrame() -> void;

		[[nodiscard]] auto GetPosition() const -> Vector2;
		[[nodiscard]] auto GetDirection() const -> Orientation;
		[[nodiscard]] auto GetSize() const -> Vector2;

		auto SetPosition(Vector2 pos) -> void;
		auto SetDirection(Orientation dir) -> void;

	private:
		Tileset m_Character = Tileset("assets/Characters/Character.png", 16, 32);
		Vector2 m_Position = Vector2{64, 48};

		Orientation m_Direction = Orientation::Down;
		uint16_t m_CurrentFrame = 0;
	};
} // namespace Redge
