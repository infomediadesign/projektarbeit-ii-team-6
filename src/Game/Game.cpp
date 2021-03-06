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

	auto Game::IsRunning() const -> bool
	{
		return m_Scene && !WindowShouldClose();
	}

	auto Game::SetScene(std::unique_ptr<Scene> newScene) -> std::unique_ptr<Scene>
	{
		auto oldScene = std::move(m_Scene);
		m_Scene = std::move(newScene);
		return oldScene;
	}

	auto Game::Update() -> void
	{
		if (!m_Scene)
			return;

		m_Scene->Update();
	}

	auto Game::Render() const -> void
	{
		if (!m_Scene)
			return;

		BeginDrawing();
		ClearBackground(PINK);

		BeginMode2D(m_Scene->Camera);
		m_Scene->RenderWorld();
		EndMode2D();

		m_Scene->RenderUI();

		EndDrawing();
	}
} // namespace Redge
