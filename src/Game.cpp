#include "Game.h"

#include <string>

#include <raylib.h>

namespace Redge
{
	Game::Game(const uint16_t width, const uint16_t height)
	{
		InitWindow(width, height, "Codename: Redge");
	}

	Game::~Game()
	{
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

		m_Scene->RenderWorld();
		m_Scene->RenderForeground();
		m_Scene->RenderUI();

		EndDrawing();
	}
} // namespace Redge
