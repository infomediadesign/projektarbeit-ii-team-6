#pragma once

#include "Scene.h"

namespace Redge
{
	class MainMenu final : public Scene
	{
	public:
		explicit MainMenu(Game* host);

		virtual auto Update() -> void;

		virtual auto RenderWorld() const -> void;
		virtual auto RenderForeground() const -> void;
		virtual auto RenderUI() const -> void;
	};
} // namespace Redge
