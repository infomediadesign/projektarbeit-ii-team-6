#include "MainMenu.h"

#include "Game/Game.h"
#include "Game/Scenes/TiledScene.h"

namespace Redge
{
	MainMenu::MainMenu(Game* host) :
		Scene(host), m_Play("assets/Buttons/Play.png", "assets/Buttons/MenuButton.png", Rectangle{}),
		m_Settings("assets/Buttons/Settings.png", "assets/Buttons/MenuButton.png", Rectangle{}),
		m_Exit("assets/Buttons/Exit.png", "assets/Buttons/MenuButton.png", Rectangle{})
	{
	}

	auto MainMenu::Update() -> void
	{
		Rectangle buttonArea{};
		buttonArea.width = 500;
		buttonArea.height = 100;
		buttonArea.x = GetScreenWidth() / 2 - buttonArea.width / 2;
		buttonArea.y = GetScreenHeight() / 2 - 200;

		m_Play.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_Play.Update())
			Host->SetScene(std::make_shared<TiledScene>(Host, "assets/Tilemaps/Level1.tmj"));

		m_Settings.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_Settings.Update())
			(void)0; // TODO: add a settings menu

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

		m_Play.Render();
		m_Settings.Render();
		m_Exit.Render();
	}
} // namespace Redge
