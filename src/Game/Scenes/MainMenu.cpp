#include "MainMenu.h"

namespace Redge
{
	MainMenu::MainMenu(Game* host) : Scene(host)
	{
	}

	auto MainMenu::Update() -> void
	{
	}

	auto MainMenu::RenderWorld() const -> void
	{
	}

	auto MainMenu::RenderUI() const -> void
	{
		auto scaleWidth = static_cast<float>(GetScreenWidth()) / m_Background.GetTileWidth();
		auto scaleHeight = static_cast<float>(GetScreenHeight()) / m_Background.GetTileHeight();
		auto scale = std::max(scaleWidth, scaleHeight) * 1.01f;
		m_Background.DrawTileScaled(0, 0, {}, scale);
	}
} // namespace Redge
