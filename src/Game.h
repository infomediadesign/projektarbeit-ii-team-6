#pragma once

#include "Graphics/Tileset.h"

#include <cstdint>

namespace Redge
{
	class Time;

	class Game final
	{
	public:
		Game(uint16_t width, uint16_t height);
		~Game();

		Game(const Game&) = delete;
		Game(Game&&) = delete;

		auto operator=(const Game&) -> Game& = delete;
		auto operator=(Game&&) -> Game& = delete;

		[[nodiscard]] auto IsRunning() const -> bool;

		auto Update() -> void;
		auto Render() const -> void;

	private:
		auto RenderWorld() const -> void;
		auto RenderForeground() const -> void;
		auto RenderUI() const -> void;

		Tileset m_Tileset;
	};
} // namespace Redge
