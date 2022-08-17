#pragma once

#include "Game/Scene.h"
#include "Raylib/Button.h"

#include <memory>

namespace Redge
{
	class PauseScene final : public Scene
	{
	public:
		explicit PauseScene(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

		auto SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>;

	private:
		std::shared_ptr<Scene> m_BackScene{};

		// TODO: replace button text with correct text once available
		Raylib::Button m_Resume{"assets/Buttons/Play.png", "assets/Buttons/MenuButton.png", Rectangle{}};
		Raylib::Button m_Settings{"assets/Buttons/Settings.png", "assets/Buttons/MenuButton.png", Rectangle{}};
		Raylib::Button m_MainMenu{"assets/Buttons/Exit.png", "assets/Buttons/MenuButton.png", Rectangle{}};
	};
} // namespace Redge
