#include "Game.h"

#include "raylib.h"

#include <cassert>
#include <string>

namespace Redge
{
	Game::Game(const uint16_t width, const uint16_t height)
	{
		InitWindow(width, height, "Crimson Mine");
		InitAudioDevice();

		SetWindowState(FLAG_WINDOW_RESIZABLE);
		SetWindowState(FLAG_VSYNC_HINT);
		SetExitKey(KEY_NULL); // Disable esc to exit

		// Application icon
		auto icon = LoadImage("assets/Icon.png");
		SetWindowIcon(icon);
		UnloadImage(icon);
	}

	Game::~Game()
	{
		m_Scene = nullptr;
		CloseAudioDevice();
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
			ClearBackground(Color{18, 4, 11, 255});

			BeginMode2D(scene->Camera);
			scene->RenderWorld();
			EndMode2D();

			scene->RenderUI();
			EndDrawing();
		}
	}

	auto Game::GetVolume() const -> float
	{
		return m_Volume;
	}

	auto Game::SetVolume(float volumen) -> void
	{
		assert(0 <= volumen && volumen <= 1);
		m_Volume = volumen;
	}
} // namespace Redge
