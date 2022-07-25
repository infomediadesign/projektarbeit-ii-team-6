#pragma once

#include <memory>

#include "Game/Scene.h"

namespace Redge
{
	class SettingsMenu final : public Scene
	{
	public:
		explicit SettingsMenu(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

		auto SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>;

	private:
		std::shared_ptr<Scene> m_BackScene{};
	};
} // namespace Redge
