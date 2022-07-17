#include "Button.h"

namespace Raylib
{
	Button::Button(const char* background, const char* foreground, Rectangle area) :
		m_Background(background, 1, 3), m_Foreground(foreground, 1, 3), m_Area(area)
	{
	}

	auto Button::GetArea() const -> Rectangle
	{
		return m_Area;
	}

	auto Button::SetArea(Rectangle rectangle) -> void
	{
		m_Area = rectangle;
	}

	auto Button::GetState() const -> ButtonState
	{
		return m_State;
	}

	auto Button::Update() -> void
	{
		m_State = ButtonState::Default;

		if (CheckCollisionPointRec(GetMousePosition(), GetArea()))
			m_State = ButtonState::Hovered;

		if (GetState() == ButtonState::Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			m_State = ButtonState::Pressed;
	}

	auto Button::Render() const -> void
	{
		m_Background.DrawTileTo(0, static_cast<int>(GetState()), GetArea());
		m_Foreground.DrawTileTo(0, static_cast<int>(GetState()), GetArea());
	}
} // namespace Raylib
