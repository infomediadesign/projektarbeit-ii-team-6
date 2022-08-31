#include "CombatScene.h"
#include "Game/Game.h"
#include "PauseScene.h"

Redge::CombatScene::CombatScene(Redge::Game* Host) : Scene(Host)
{
	RelocateUI();
}

auto Redge::CombatScene::Update() -> void
{
	m_MaxHealth = m_Character->GetMaxHealth();
	m_Health  = m_Character->GetHealth();
	m_MaxOxygen = m_Character->GetMaxOxygen();
	m_Oxygen = m_Character->GetOxygen();

	HPBarPlayerPercent = m_Health/m_MaxHealth;
	HPBarPlayerO2Percent = m_Oxygen/m_MaxOxygen;

	if(OldScreenWidth != GetScreenWidth() || OldScreenHeight != GetScreenHeight()) RelocateUI();
	if (IsKeyPressed(KEY_ESCAPE))
	{
		auto pauseScene = std::make_shared<PauseScene>(Host);
		pauseScene->SetBackScene(Host->SetScene(pauseScene));
	}

	if(IsKeyDown(KEY_H)|| (CheckCollisionPointRec(GetMousePosition(),{PosHealslot.x,PosHealslot.y, static_cast<float>(healslot.GetTileWidth()*uiScale),static_cast<float>(healslot.GetTileHeight()*uiScale)}) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))) healslottriggered = true;
	else healslottriggered = false;

	if(IsKeyDown(KEY_TAB) && weaponslotframe == 0) weaponswap = true;
	else if(weaponslotframe != 0) weaponswap = true;
	else weaponswap = false;

	if(CheckCollisionPointRec(GetMousePosition(),{PosAttackButton1.x,PosAttackButton1.y, static_cast<float>(attackbutton.GetTileWidth()*uiScale),static_cast<float>(attackbutton.GetTileHeight()*uiScale)}) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		ABS1 = 2;
	}
	else if(CheckCollisionPointRec(GetMousePosition(),{PosAttackButton1.x,PosAttackButton1.y, static_cast<float>(attackbutton.GetTileWidth()*uiScale),static_cast<float>(attackbutton.GetTileHeight()*uiScale)}))
	{
		ABS1 = 1;
	}
	else ABS1 = 0;

	if(CheckCollisionPointRec(GetMousePosition(),{PosAttackButton2.x,PosAttackButton2.y, static_cast<float>(attackbutton.GetTileWidth()*uiScale),static_cast<float>(attackbutton.GetTileHeight()*uiScale)}) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		ABS2 = 2;
	}
	else if(CheckCollisionPointRec(GetMousePosition(),{PosAttackButton2.x,PosAttackButton2.y, static_cast<float>(attackbutton.GetTileWidth()*uiScale),static_cast<float>(attackbutton.GetTileHeight()*uiScale)}))
	{
		ABS2 = 1;
	}
	else ABS2 = 0;

	if(nextphase)
	{
		nextphase = false;
		prepphase = !prepphase;
	}

	if(prepphase)
	{
		if(IsKeyPressed(KEY_ENTER) && actionpoints == 0)
			nextphase = true;
	}
	else
	{
	actionpoints = 3;
	}

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
	OldScreenHeight = GetScreenHeight();
	OldScreenWidth = GetScreenWidth();
}
auto Redge::CombatScene::RenderWorld() const -> void
{
}
auto Redge::CombatScene::RenderUI() const -> void
{
	DrawTexturePro(background,
		{0, 0, static_cast<float>(background.width), static_cast<float>(background.height)},
		{0,0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())},
		{0,0},
		0,
		WHITE);

	Rectangle enemyArea{};
	enemyArea.width = 200;
	enemyArea.height = 400;
	enemyArea.x = static_cast<float>(GetScreenWidth() * 0.84) - enemyArea.width / 2;
	enemyArea.y = static_cast<float>(GetScreenHeight() * 0.53) - enemyArea.height;
	m_Enemy->DrawSprite(enemyArea);

	// UI

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
	Vector2 HPBarPlayerState = {static_cast<float>(HPBarPlayer.GetTileWidth()* HPBarPlayerPercent), static_cast<float>(HPBarPlayer.GetTileHeight())};
	HPBarPlayer.DrawTilePartScaled(0,
		1,
		PosHPBarPlayer,
		HPBarPlayerState,
		uiScale,
		WHITE);
	Vector2 HPBarPlayerO2State = {static_cast<float>(HPBarPlayer.GetTileWidth()* HPBarPlayerO2Percent), static_cast<float>(HPBarPlayer.GetTileHeight())};
	HPBarPlayer.DrawTilePartScaled(0,
		0,
		PosHPBarPlayer,
		HPBarPlayerO2State,
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

auto Redge::CombatScene::SetCharacter(std::shared_ptr<Character> character) -> void
{
	m_Character = std::move(character);
}

auto Redge::CombatScene::SetEnemy(std::shared_ptr<Enemy> enemy) -> void
{
	m_Enemy = std::move(enemy);
}
