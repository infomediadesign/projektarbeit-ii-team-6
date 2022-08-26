#pragma once

#include "raylib.h"
#include "memory"

namespace Redge
{
	class Game;

	class Scene
	{
	public:
		virtual ~Scene() = default;

		virtual auto Update() -> void = 0;

		virtual auto RenderWorld() const -> void = 0;
		virtual auto RenderUI() const -> void = 0;

		Game* const Host;
		Camera2D Camera{};

	protected:
		explicit Scene(Game* host);
	};
} // namespace Redge
