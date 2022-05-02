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
		short currentframe = 0;
		auto NextFrame() -> void;
		auto Draw() const -> void;
		auto DrawScaled(float scale) const -> void;

		Vector2 Position = Vector2{0, 0};
		Orientation Direction = Orientation::Down;

	private:
		Tileset m_Character = Tileset("assets/Smallerdudall-Sheet.png", 16, 32);
	};
} // namespace Redge
