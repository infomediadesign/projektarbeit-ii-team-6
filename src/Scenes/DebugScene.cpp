#include "DebugScene.h"

#include <string>

#include <raymath.h>

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host),
		m_Level(Tiled::Map::FromFile("assets/Tilemaps/level1.tmj"))
	{
		Camera.zoom = 4;
	}

	auto DebugScene::Update() -> void
	{
		m_Level.Update(this);
	}

	auto DebugScene::RenderWorld() const -> void
	{
		m_Level.Render(Rectangle{
			Camera.target.x + Camera.offset.x,
			Camera.target.y + Camera.offset.y,
			GetScreenWidth() / Camera.zoom,
			GetScreenHeight() / Camera.zoom,
		});
	}

	auto DebugScene::RenderUI() const -> void
	{
		m_Level.RenderUI();

		constexpr auto fontSize = 50;
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
