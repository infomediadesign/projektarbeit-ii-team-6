#pragma once

#include "memory"
#include "raylib.h"

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

		[[nodiscard]] virtual auto IsToxic() const -> bool
		{
			return false;
		}

		Game* const Host;
		Camera2D Camera{};

	protected:
		explicit Scene(Game* host);
	};
} // namespace Redge
