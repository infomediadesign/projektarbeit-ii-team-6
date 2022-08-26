#pragma once

#include "Game/Scene.h"
#include "Raylib/Slider.h"
#include "Raylib/Tileset.h"
#include "Raylib/Toggle.h"

#include <memory>

namespace Redge
{
	class SettingsMenu final : public Scene
	{
	public:
		explicit SettingsMenu(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

		auto SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>;

	private:
		std::shared_ptr<Scene> m_BackScene{};

		Raylib::Tileset m_Background = Raylib::Tileset("assets/Background/CrimsonMenu.png", 1, 1);

		Rectangle m_FullscreenArea{};
		Raylib::Toggle m_Fullscreen;

		Rectangle m_VerticalSyncArea{};
		Raylib::Toggle m_VerticalSync;

		Rectangle m_VolumeArea{};
		Raylib::Slider m_Volume;
	};
} // namespace Redge
