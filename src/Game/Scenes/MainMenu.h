#pragma once

#include "Game/Scene.h"
#include "Raylib/Button.h"
#include "Raylib/Tileset.h"

namespace Redge
{
	class MainMenu final : public Scene
	{
	public:
		explicit MainMenu(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

	private:
		Raylib::Tileset m_Background = Raylib::Tileset("assets/Background/CrimsonMenu.png", 1, 1);
		Raylib::Tileset m_Logo = Raylib::Tileset("assets/Logo.png", 1, 1);

		Raylib::Button m_Play{"assets/Buttons/Play.png", "assets/Buttons/MenuButton.png", Rectangle{}};
		Raylib::Button m_Settings{"assets/Buttons/Settings.png", "assets/Buttons/MenuButton.png", Rectangle{}};
		Raylib::Button m_Exit{"assets/Buttons/Exit.png", "assets/Buttons/MenuButton.png", Rectangle{}};
	};
} // namespace Redge
