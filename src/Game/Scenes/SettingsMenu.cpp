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
	}

	auto SettingsMenu::SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>
	{
		m_BackScene.swap(scene);
		return scene;
	}
} // namespace Redge
