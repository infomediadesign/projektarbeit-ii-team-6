#include "CombatScene.h"

Redge::CombatScene::CombatScene(Redge::Game* Host) : Scene(Host)
{
}
auto Redge::CombatScene::Update() -> void
{
}
auto Redge::CombatScene::RenderWorld() const -> void
{
}
auto Redge::CombatScene::RenderUI() const -> void
{
}
auto Redge::CombatScene::SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>
{
	m_BackScene.swap(scene);
	return scene;
}
