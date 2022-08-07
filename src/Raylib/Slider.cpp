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
		area.x = std::clamp(area.x, GetArea().x + 5, GetArea().x + GetArea().width - 5);
		area.x -= m_Crystal.GetTileWidth() * scale / 2;
		m_Crystal.DrawTileScaled(0, 0, area, scale);
	}

	auto Slider::GetIdealWidth(float height) const -> float
	{
		return height / m_Slider.GetTileHeight() * m_Slider.GetTileWidth();
	}

	auto Slider::GetIdealHeight(float width) const -> float
	{
		return width / m_Slider.GetTileWidth() * m_Slider.GetTileHeight();
	}
} // namespace Raylib
