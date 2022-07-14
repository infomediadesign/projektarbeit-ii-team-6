#pragma once

#include "Game/Scene.h"

namespace Redge
{
	class MainMenu final : public Scene
	{
	public:
		explicit MainMenu(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;
	};
} // namespace Redge
