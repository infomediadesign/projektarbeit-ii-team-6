#pragma once

#include "Game/Scene.h"
#include "Tiled/Map.h"

namespace Redge
{
	class TiledScene final : public Scene
	{
	public:
		explicit TiledScene(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

	private:
		Tiled::Map m_Level;
	};
} // namespace Redge
