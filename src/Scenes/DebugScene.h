#pragma once

#include "Character.h"
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
		Vector2 m_CharacterPos{};
	};
} // namespace Redge
