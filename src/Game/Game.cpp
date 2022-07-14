#include "Game.h"

#include "raylib.h"

#include <string>

namespace Redge
{
	Game::Game(const uint16_t width, const uint16_t height)
	{
		InitWindow(width, height, "Crimson Mine");
		SetWindowState(FLAG_WINDOW_RESIZABLE);

		// Applicatino icon
		auto icon = LoadImage("assets/Icon.png");
		SetWindowIcon(icon);
		UnloadImage(icon);
	}

	Game::~Game()
	{
		m_Scene = nullptr;
		CloseWindow();
	}

	auto Game::SetScene(std::shared_ptr<Scene> newScene) -> std::shared_ptr<Scene>
	{
		m_Scene.swap(newScene);
		return newScene;
	}

	auto Game::Run() -> void
	{
		while (!WindowShouldClose())
		{
			auto scene = m_Scene;
			if (!scene)
				break;

			scene->Update();

			BeginDrawing();
			ClearBackground(PINK);

			BeginMode2D(scene->Camera);
			scene->RenderWorld();
			EndMode2D();

			scene->RenderUI();
			EndDrawing();
		}
	}
} // namespace Redge
