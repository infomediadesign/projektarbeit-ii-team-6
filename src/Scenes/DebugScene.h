#pragma once

#include "Entities/Character.h"
#include "Graphics/Tileset.h"
#include "Scene.h"

namespace Redge
{
	class DebugScene final : public Scene
	{
	public:
		explicit DebugScene(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderForeground() const -> void override;
		auto RenderUI() const -> void override;

	private:
		Tileset m_FloorTiles;
		Character m_Character;

		bool m_CanMove = true;
		float m_TimeSinceLastStep = 0;
		float m_TimeSinceLastFrame = 0;
	};
} // namespace Redge
