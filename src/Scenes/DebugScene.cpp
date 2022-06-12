#include "DebugScene.h"

#include "Entities/Character.h"

#include <string>

#include <raymath.h>

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host), m_Tilemap(Tilemap::FromTiled("assets/Tilemaps/level1.tmj"))
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
		constexpr auto fontSize = 50;

		m_Tilemap.RenderUI();
		DrawText("Debug Scene", 10, 10, fontSize, WHITE);

		auto topLeft = Vector2{
			static_cast<float>(GetScreenWidth() - 10),
			10,
		};

		auto fps = std::to_string(GetFrameTime()) + "s";
		topLeft.x -= MeasureText(fps.c_str(), fontSize);

		DrawText(fps.c_str(), topLeft.x, topLeft.y, fontSize, WHITE);
	}
} // namespace Redge
