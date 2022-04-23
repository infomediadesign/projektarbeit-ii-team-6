#pragma once

#include "Scene.h"
#include "Graphics/Tileset.h"

namespace Redge
{
	class MainMenu final : public Scene
	{
	public:
		explicit MainMenu(Game* host);

		auto Update() -> void override;

		auto RenderWorld() const -> void override;
		auto RenderForeground() const -> void override;
		auto RenderUI() const -> void override;

	private:
		Tileset m_FloorTiles;
	};
} // namespace Redge
