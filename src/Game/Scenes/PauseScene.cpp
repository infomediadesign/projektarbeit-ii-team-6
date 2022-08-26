#include "PauseScene.h"

#include "Game/Game.h"
#include "MainMenu.h"
#include "SettingsMenu.h"

namespace Redge
{
	PauseScene::PauseScene(Game* host) : Scene(host)
	{
	}

	auto PauseScene::Update() -> void
	{
		Rectangle buttonArea{};
		buttonArea.width = 500;
		buttonArea.height = 100;
		buttonArea.x = GetScreenWidth() / 2 - buttonArea.width / 2;
		buttonArea.y = GetScreenHeight() / 2 - 200;

		m_Resume.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_Resume.Update() || IsKeyPressed(KEY_ESCAPE))
			Host->SetScene(m_BackScene);

		m_Settings.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_Settings.Update())
		{
			auto settingsScene = std::make_shared<SettingsMenu>(Host);
			settingsScene->SetBackScene(Host->SetScene(settingsScene));
		}

		m_MainMenu.SetArea(buttonArea);
		buttonArea.y += buttonArea.height + 50;
		if (m_MainMenu.Update())
			Host->SetScene(std::make_shared<MainMenu>(Host));
	}

	auto PauseScene::RenderWorld() const -> void
	{
		if (m_BackScene)
		{
			BeginMode2D(m_BackScene->Camera);
			m_BackScene->RenderWorld();
			BeginMode2D(Camera);
		}
	}

	auto PauseScene::RenderUI() const -> void
	{
		if (m_BackScene)
			m_BackScene->RenderUI();

		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 150});

		m_Resume.Render();
		m_Settings.Render();
		m_MainMenu.Render();
	}
	auto PauseScene::SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>
	{
		m_BackScene.swap(scene);
		return scene;
	}
} // namespace Redge
