#pragma once

#include <memory>

#include "Game/Scene.h"
#include "Raylib/Tileset.h"

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
	};
} // namespace Redge
