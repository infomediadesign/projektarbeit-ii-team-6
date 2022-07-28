#include "SettingsMenu.h"

#include "Game/Game.h"

namespace Redge
{
	SettingsMenu::SettingsMenu(Game* host) : Scene(host)
	{
	}

	auto SettingsMenu::Update() -> void
	{
	}

	auto SettingsMenu::RenderWorld() const -> void
	{
		if (IsKeyPressed(KEY_SPACE))
			Host->SetScene(m_BackScene);
	}

	auto SettingsMenu::RenderUI() const -> void
	{
		auto scaleWidth = static_cast<float>(GetScreenWidth()) / m_Background.GetTileWidth();
		auto scaleHeight = static_cast<float>(GetScreenHeight()) / m_Background.GetTileHeight();
		auto scale = std::max(scaleWidth, scaleHeight) * 1.01f;
		m_Background.DrawTileScaled(0, 0, {}, scale);
	}

	auto SettingsMenu::SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>
	{
		m_BackScene.swap(scene);
		return scene;
	}
} // namespace Redge
