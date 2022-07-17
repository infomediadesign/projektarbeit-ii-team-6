#pragma once

#include "Raylib/Tileset.h"

#include <vector>

#include <raylib.h>

namespace Raylib
{
	enum class ButtonState
	{
		Default,
		Hovered,
		Pressed,
	};

	class Button
	{
	public:
		Button(const char* background, const char* foreground, Rectangle area);

		[[nodiscard]] auto GetArea() const -> Rectangle;
		auto SetArea(Rectangle rectangle) -> void;

		[[nodiscard]] auto GetState() const -> ButtonState;

		[[nodiscard]] auto Update() -> bool;
		auto Render() const -> void;

	private:
		Tileset m_Background;
		Tileset m_Foreground;
		Rectangle m_Area{};
		ButtonState m_State = ButtonState::Default;
	};
} // namespace Raylib
