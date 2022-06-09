#include "DebugScene.h"

#include "Entities/Character.h"

#include <raymath.h>

namespace Redge
{
	DebugScene::DebugScene(Game* host) :
		Scene(host), m_Tilemap(Tilemap::FromTiled("assets/Tilemaps/Debugmap_without_chunks.json"))
	{
		Camera.zoom = 4;
	}

	auto DebugScene::Update() -> void
	{
		m_Tilemap.Update(Camera);
	}

	auto DebugScene::RenderWorld() const -> void
	{
		m_Tilemap.Render();
	}

	auto DebugScene::RenderUI() const -> void
	{
		m_Tilemap.RenderUI();
		DrawText("Debug Scene", 10, 10, 50, WHITE);
	}
} // namespace Redge
