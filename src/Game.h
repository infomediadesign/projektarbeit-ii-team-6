#pragma once

#include "Scene.h"

#include <cstdint>
#include <memory>

namespace Redge
{
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

		auto SetScene(std::unique_ptr<Scene> newScene) -> std::unique_ptr<Scene>;

		auto Update() -> void;
		auto Render() const -> void;

	private:
		std::unique_ptr<Scene> m_Scene;
	};
} // namespace Redge
