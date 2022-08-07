#pragma once

#include "Raylib/Tileset.h"

namespace Raylib
{
	class Slider
	{
	public:
		[[nodiscard]] auto GetArea() const -> Rectangle;
		auto SetArea(Rectangle area) -> void;

		[[nodiscard]] auto GetPercentage() const -> float;
		auto SetPercentage(float percentage) -> void;

		auto Update() -> bool;
		auto Render() const -> void;

	private:
		Tileset m_Slider = Tileset("assets/Buttons/Slider.png", 1, 2);
		Tileset m_Crystal = Tileset("assets/Buttons/SliderCrystal.png", 1, 1);
		float m_Percentage{};
		Rectangle m_Area{};
	};
} // namespace Raylib
