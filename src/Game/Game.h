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

		auto SetScene(std::shared_ptr<Scene> newScene) -> std::shared_ptr<Scene>;

		auto Run() -> void;

	private:
		std::shared_ptr<Scene> m_Scene;
	};
} // namespace Redge
