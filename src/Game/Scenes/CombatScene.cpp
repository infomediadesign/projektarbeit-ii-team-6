#include "CombatScene.h"
#include "Game/Game.h"

Redge::CombatScene::CombatScene(Redge::Game* Host) : Scene(Host)
{
	RelocateUI();
}

auto Redge::CombatScene::Update() -> void
{
	DrawTexturePro(background,
		{0, 0, static_cast<float>(background.width), static_cast<float>(background.height)},
		{0,0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())},
		{0,0},
		0,
		WHITE);

	if(IsKeyDown(KEY_H)) healslottriggered = true;
	else healslottriggered = false;

	if(IsKeyDown(KEY_TAB) && weaponslotframe == 0) weaponswap = true;
	else if(weaponslotframe != 0) weaponswap = true;
	else weaponswap = false;


	TSLweaponslot += GetFrameTime();
	TSLpointdisplay += GetFrameTime();

		if (TSLweaponslot >= FDweaponslot)
		{
			TSLweaponslot -= FDweaponslot;
			if(weaponswap){weaponslotframe = (weaponslotframe + 1) % weaponslot.GetTileCountX();}
		}

	if (TSLpointdisplay >= FDpointdisplay)
	{
		TSLpointdisplay -= FDpointdisplay;
		pointdisplayframe = (pointdisplayframe + 1) % pointdisplay.GetTileCountX();
	}

}
auto Redge::CombatScene::RenderWorld() const -> void
{
}
auto Redge::CombatScene::RenderUI() const -> void
{
	weaponslot.DrawTileScaled(weaponslotframe,
		0,
		PosWeaponslot,
		uiScale,
		WHITE
		);

	pointdisplay.DrawTileScaled(pointdisplayframe,
		0,
		PosPointdisplay,
		uiScale,
		WHITE);

	attackbutton.DrawTileScaled(0,
		ABS1,
		PosAttackButton1,
		uiScale,
		WHITE);
	attackbutton.DrawTileScaled(0,
		ABS2,
		PosAttackButton2,
		uiScale,
		WHITE);

	healslot.DrawTileScaled(static_cast<int>(healslottriggered),
		0,
		PosHealslot,
		uiScale,
		WHITE);

	HPBarEnemy.DrawTileScaled(0,
		1,
		PosHPBarEnemy,
		uiScale,
		WHITE);
	HPBarEnemy.DrawTilePartScaled(0,
		0,
		PosHPBarEnemy,
		HPBarEnemyState,
		uiScale,
		WHITE);

	HPBarPlayer.DrawTileScaled(0,
		2,
		PosHPBarPlayer,
		uiScale,
		WHITE);
	HPBarPlayer.DrawTilePartScaled(0,
		1,
		PosHPBarPlayer,
		HPBarPlayerO2State,
		uiScale,
		WHITE);
	HPBarPlayer.DrawTilePartScaled(0,
		0,
		PosHPBarPlayer,
		HPBarPlayerState,
		uiScale,
		WHITE);
}

auto Redge::CombatScene::SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>
{
	m_BackScene.swap(scene);
	return scene;
}
auto Redge::CombatScene::RelocateUI() -> void
{
	PosWeaponslot = {static_cast<float>(GetScreenWidth()/2 - weaponslot.GetTileWidth()*uiScale/2),static_cast<float>(weaponslot.GetTileHeight()/4*uiScale)};
	PosPointdisplay = {static_cast<float>(GetScreenWidth()-(pointdisplay.GetTileWidth()*1.5 + attackbutton.GetTileWidth()) * uiScale), static_cast<float>(GetScreenHeight()-(pointdisplay.GetTileHeight() + attackbutton.GetTileHeight()) * uiScale)};
	PosAttackButton1 = {PosPointdisplay.x + pointdisplay.GetTileWidth()*uiScale, PosPointdisplay.y - attackbutton.GetTileHeight()/2*uiScale};
	PosAttackButton2 = {PosPointdisplay.x + pointdisplay.GetTileWidth()*uiScale, PosPointdisplay.y + (pointdisplay.GetTileHeight() - attackbutton.GetTileHeight()/2)*uiScale};
	PosHealslot = {PosPointdisplay.x - pointdisplay.GetTileWidth()*uiScale, static_cast<float>(PosPointdisplay.y + (pointdisplay.GetTileHeight()/2-healslot.GetTileHeight()/1.5)*uiScale)};
	PosHPBarPlayer = {static_cast<float>(pointdisplay.GetTileHeight()*uiScale/4),static_cast<float>(pointdisplay.GetTileHeight()*uiScale/4)};
	PosHPBarEnemy = {static_cast<float>(GetScreenWidth()-HPBarEnemy.GetTileWidth()*uiScale - pointdisplay.GetTileWidth()*uiScale/4), static_cast<float>(PosHPBarPlayer.y + (HPBarPlayer.GetTileHeight()/2 - HPBarEnemy.GetTileHeight()/2)*uiScale)};
}
