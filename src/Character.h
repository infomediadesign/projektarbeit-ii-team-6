#pragma once

#include "Graphics/Tileset.h"

namespace Redge
{
	enum class Orientation
	{
		Left,
		Up,
		Down,
		Right
	};

	class Character
	{
	public:
		auto Draw() const -> void;
		auto DrawScaled(float scale) const -> void;

		Vector2 Position = Vector2{0, 0};
		Orientation Direction = Orientation::Down;

	private:
		Tileset m_Character = Tileset("assets/dude2.png", 16, 32);
	};
} // namespace Redge
