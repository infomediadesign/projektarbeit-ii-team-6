#pragma once

#include "Graphics/Tilemap.h"
#include "Scene.h"

namespace Redge
{
	class DebugScene final : public Scene
	{
	public:
		explicit DebugScene(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

	private:
		Tilemap m_Tilemap;
	};
} // namespace Redge
