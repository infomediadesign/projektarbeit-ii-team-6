#pragma once

#include "raylib.h"
#include "memory"
#include "Game/Game.h"

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
		auto SetScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>;

		Camera2D Camera{};

	protected:
		explicit Scene(Game* host);

		Game* Host;
	};
} // namespace Redge
