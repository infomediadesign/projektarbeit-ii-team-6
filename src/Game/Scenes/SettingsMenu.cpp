#include "SettingsMenu.h"

#include "Game/Game.h"

#include <string>

namespace Redge
{
	SettingsMenu::SettingsMenu(Game* host) : Scene(host)
	{
	}

	auto SettingsMenu::Update() -> void
	{
		if (IsKeyPressed(KEY_ESCAPE))
			Host->SetScene(m_BackScene);

		Rectangle settingArea{};
		settingArea.width = 800;
		settingArea.height = 45;
		settingArea.x = static_cast<float>(GetScreenWidth() / 2 - settingArea.width / 2);
		settingArea.y = 400;

		m_FullscreenArea = settingArea;
		settingArea.y += settingArea.height + 50;
		m_VerticalSyncArea = settingArea;
		settingArea.y += settingArea.height + 50;
		m_VolumeArea = settingArea;

		m_Fullscreen.SetArea(Rectangle{
			.x = m_FullscreenArea.x + m_FullscreenArea.width - m_FullscreenArea.height,
			.y = m_FullscreenArea.y,
			.width = m_FullscreenArea.height,
			.height = m_FullscreenArea.height,
		});
		m_Fullscreen.SetState(IsWindowFullscreen());
		if (m_Fullscreen.Update())
		{
			if (m_Fullscreen.GetState())
			{
				SetWindowState(FLAG_FULLSCREEN_MODE);
			}
			else
			{
				ClearWindowState(FLAG_FULLSCREEN_MODE);
			}
		}

		m_VerticalSync.SetArea(Rectangle{
			.x = m_VerticalSyncArea.x + m_VerticalSyncArea.width - m_VerticalSyncArea.height,
			.y = m_VerticalSyncArea.y,
			.width = m_VerticalSyncArea.height,
			.height = m_VerticalSyncArea.height,
		});
		m_VerticalSync.SetState(IsWindowState(FLAG_VSYNC_HINT));
		if (m_VerticalSync.Update())
		{
			if (m_VerticalSync.GetState())
			{
				SetWindowState(FLAG_VSYNC_HINT);
			}
			else
			{
				ClearWindowState(FLAG_VSYNC_HINT);
			}
		}

		Rectangle volumeArea{};
		volumeArea.height = m_VolumeArea.height / 2;
		volumeArea.width = m_Volume.GetIdealWidth(volumeArea.height);
		volumeArea.x = m_VolumeArea.x + m_VolumeArea.width - volumeArea.width;
		volumeArea.y = m_VolumeArea.y + volumeArea.height / 2,
		m_Volume.SetArea(volumeArea);
		m_Volume.SetPercentage(Host->GetVolume());
		if (m_Volume.Update())
			Host->SetVolume(m_Volume.GetPercentage());
	}

	auto SettingsMenu::RenderWorld() const -> void
	{
	}

	auto SettingsMenu::RenderUI() const -> void
	{
		auto scaleWidth = static_cast<float>(GetScreenWidth()) / m_Background.GetTileWidth();
		auto scaleHeight = static_cast<float>(GetScreenHeight()) / m_Background.GetTileHeight();
		auto scale = std::max(scaleWidth, scaleHeight) * 1.01F;
		m_Background.DrawTileScaled(0, 0, {}, scale);

		const char* settingsText = "Settings";
		static constexpr auto s_TitleSize = 100;

		DrawText("[ESC] to go back", 30, 30, 25, GRAY);

		auto titleWidth = MeasureText(settingsText, s_TitleSize);
		DrawText(settingsText, GetScreenWidth() / 2 - titleWidth / 2, 150, s_TitleSize, WHITE);

		DrawText("Fullscreen: ", m_FullscreenArea.x, m_FullscreenArea.y, m_FullscreenArea.height, WHITE);
		m_Fullscreen.Render();

		DrawText("Vertical Sync: ", m_VerticalSyncArea.x, m_VerticalSyncArea.y, m_VerticalSyncArea.height, WHITE);
		m_VerticalSync.Render();

		DrawText("Volume: ", m_VolumeArea.x, m_VolumeArea.y, m_VolumeArea.height, WHITE);
		m_Volume.Render();
	}

	auto SettingsMenu::SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>
	{
		m_BackScene.swap(scene);
		return scene;
	}
} // namespace Redge
