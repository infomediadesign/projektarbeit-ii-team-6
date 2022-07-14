#pragma once

#include "Game/Scene.h"
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
	};
} // namespace Redge
