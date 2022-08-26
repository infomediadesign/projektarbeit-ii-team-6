#include "Toggle.h"

namespace Raylib
{
	auto Toggle::GetArea() const -> Rectangle
	{
		return m_Area;
	}

	auto Toggle::SetArea(Rectangle area) -> void
	{
		m_Area = area;
	}

	auto Toggle::GetState() const -> bool
	{
		return m_State;
	}

	auto Toggle::SetState(bool state) -> void
	{
		m_State = state;
	}

	auto Toggle::Update() -> bool
	{
		if (CheckCollisionPointRec(GetMousePosition(), GetArea()) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			m_State = !m_State;
			return true;
		}
		return false;
	}

	auto Toggle::Render() const -> void
	{
		m_Toggle.DrawTileTo(static_cast<int>(GetState()), 0, GetArea());
	}
} // namespace Raylib
