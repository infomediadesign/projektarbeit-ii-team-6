#include "Slider.h"

#include <cassert>

namespace Raylib
{
	auto Slider::GetArea() const -> Rectangle
	{
		return m_Area;
	}

	auto Slider::SetArea(Rectangle area) -> void
	{
		m_Area = area;
	}

	auto Slider::GetPercentage() const -> float
	{
		return m_Percentage;
	}

	auto Slider::SetPercentage(float percentage) -> void
	{
		assert(0 <= percentage && percentage <= 1);
		m_Percentage = percentage;
	}

	auto Slider::Update() -> bool
	{
		if (CheckCollisionPointRec(GetMousePosition(), GetArea()) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			m_Percentage = (GetMousePosition().x - GetArea().x) / GetArea().width;
			return true;
		}
		return false;
	}

	auto Slider::Render() const -> void
	{
		m_Slider.DrawTileTo(0, 1, GetArea());
		auto partArea = GetArea();
		partArea.width *= m_Percentage;
		m_Slider.DrawTilePartTo(0, 0, partArea,
			Vector2{m_Slider.GetTileWidth() * m_Percentage, static_cast<float>(m_Slider.GetTileHeight())});

		auto targetHeight = GetArea().height * 2;
		auto scale = targetHeight / m_Crystal.GetTileHeight();

		Vector2 area{};
		area.y = GetArea().y + GetArea().height / 2;
		area.y -= targetHeight / 2;
		area.x = partArea.x + partArea.width;
		area.x -= m_Crystal.GetTileWidth() * scale / 2;
		m_Crystal.DrawTileScaled(0, 0, area, scale);
	}
} // namespace Raylib
