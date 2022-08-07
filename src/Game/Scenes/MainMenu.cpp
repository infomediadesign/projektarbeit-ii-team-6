#include "MainMenu.h"

#include "Game/Game.h"
#include "Game/Scenes/SettingsMenu.h"
#include "Game/Scenes/TiledScene.h"

namespace Redge
{
	MainMenu::MainMenu(Game* host) : Scene(host)
	{
	}

	auto MainMenu::Update() -> void
	{
		Rectangle buttonArea{};
		buttonArea.width = 500;
		buttonArea.height = 100;
		buttonArea.x = GetScreenWidth() / 2 - buttonArea.width / 2;
		buttonArea.y = GetScreenHeight() / 2 - 50;

		m_Play.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_Play.Update())
			Host->SetScene(std::make_shared<TiledScene>(Host, "assets/Tilemaps/Level1.tmj"));

		m_Settings.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_Settings.Update())
		{
			auto settingsScene = std::make_shared<SettingsMenu>(Host);
			settingsScene->SetBackScene(Host->SetScene(settingsScene));
		}

		m_Exit.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_Exit.Update())
			Host->SetScene(nullptr);
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

		Rectangle logoArea{};
		logoArea.height = 120;
		logoArea.width = m_Logo.GetTileWidth() / m_Logo.GetTileHeight() * logoArea.height;
		logoArea.x = GetScreenWidth() / 2 - logoArea.width / 2;
		logoArea.y = 150;

		m_Logo.DrawTileTo(0, 0, logoArea);
		m_Play.Render();
		m_Settings.Render();
		m_Exit.Render();
	}
} // namespace Redge
