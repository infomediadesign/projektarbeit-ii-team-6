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
		Button(const char* foreground, const char* background, Rectangle area);

		[[nodiscard]] auto GetArea() const -> Rectangle;
		auto SetArea(Rectangle rectangle) -> void;

		[[nodiscard]] auto GetState() const -> ButtonState;

		[[nodiscard]] auto Update() -> bool;
		auto Render() const -> void;

	private:
		Tileset m_Foreground;
		Tileset m_Background;
		Rectangle m_Area{};
		ButtonState m_State = ButtonState::Default;
	};
} // namespace Raylib
