#include "TiledScene.h"

#include "Game/Game.h"
#include "PauseScene.h"
#include "raymath.h"

#include <string>

namespace Redge
{
	TiledScene::TiledScene(Game* host, const char* levelFile) : Scene(host), m_Level(Tiled::Map::FromFile(levelFile))
	{
		Camera.zoom = 4;
	}

	auto TiledScene::Update() -> void
	{
		m_Level.Update(this);

		if (IsKeyPressed(KEY_ESCAPE))
		{
			auto pauseScene = std::make_shared<PauseScene>(Host);
			pauseScene->SetBackScene(Host->SetScene(pauseScene));
		}
	}

	auto TiledScene::RenderWorld() const -> void
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

	auto TiledScene::RenderUI() const -> void
	{
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
