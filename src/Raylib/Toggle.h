#pragma once

#include "Raylib/Tileset.h"

namespace Raylib
{
	class Toggle
	{
	public:
		[[nodiscard]] auto GetArea() const -> Rectangle;
		auto SetArea(Rectangle area) -> void;

		[[nodiscard]] auto GetState() const -> bool;
		auto SetState(bool state) -> void;

		auto Update() -> bool;
		auto Render() const -> void;

	private:
		Tileset m_Toggle = Tileset("assets/Buttons/Toggle.png", 2, 1);
		bool m_State = false;
		Rectangle m_Area{};
	};
} // namespace Raylib
