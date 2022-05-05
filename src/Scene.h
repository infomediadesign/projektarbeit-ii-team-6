#pragma once

#include <raylib.h>

namespace Redge
{
	class Game;

	class Scene
	{
	public:
		virtual ~Scene() = default;

		[[nodiscard]] auto GetCamera() const -> Camera2D;

		virtual auto Update() -> void = 0;

		virtual auto RenderWorld() const -> void = 0;
		virtual auto RenderForeground() const -> void = 0;
		virtual auto RenderUI() const -> void = 0;

	protected:
		explicit Scene(Game* host);

		Game* Host;
		Camera2D Camera{};
	};
} // namespace Redge
