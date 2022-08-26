#pragma once
#include "Game/Scene.h"

namespace Redge
{
	class CombatScene final : public Scene
	{
	public:
		CombatScene(Game* Host);
		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

		auto SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>;

	private:
		std::shared_ptr<Scene> m_BackScene{};
	};
} // namespace Redge