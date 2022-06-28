#include "DebugScene.h"

#include <string>

#include <raymath.h>

namespace Redge
{
	DebugScene::DebugScene(Game* host) : Scene(host), m_Level(Tiled::Map::FromFile("assets/Tilemaps/hub_test.tmj"))
	{
		Camera.zoom = 4;
	}

	auto DebugScene::Update() -> void
	{
		m_Level.Update(this);
	}

	auto DebugScene::RenderWorld() const -> void
	{
		auto topLeft = GetScreenToWorld2D(Vector2{0, 0}, Camera);
		auto bottomRight = GetScreenToWorld2D(
			Vector2{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}, Camera);

		m_Level.Render(Rectangle{
			topLeft.x,
			topLeft.y,
			bottomRight.x - topLeft.x,
			bottomRight.y - topLeft.y,
		});
	}

	auto DebugScene::RenderUI() const -> void
	{
	//	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 128});
		m_Level.RenderUI();
		return; // NOTE: remove for debug info

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
