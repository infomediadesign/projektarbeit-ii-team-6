#include "CombatScene.h"

#include "Game/Game.h"
#include "Game/Objects/Enemies/Cultist.h"
#include "MainMenu.h"
#include "PauseScene.h"
#include "functional"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "ConstantConditionsOC"

Redge::CombatScene::CombatScene(Redge::Game* Host) : Scene(Host)
{
	RelocateUI();
}

auto Redge::CombatScene::Update() -> void
{
	m_MaxHealth = m_Character->GetMaxHealth();
	m_Health = m_Character->GetHealth();
	m_MaxOxygen = m_Character->GetMaxOxygen();
	m_Oxygen = m_Character->GetOxygen();

	HPBarPlayerPercent = m_Health / m_MaxHealth;
	HPBarPlayerO2Percent = m_Oxygen / m_MaxOxygen;

	m_EnemyMaxHealth = m_Enemy->GetMaximumHp();
	m_EnemyHealth = m_Enemy->GetCurrentHp();

	HPBarEnemyPercent = m_EnemyHealth/ m_EnemyMaxHealth;

	if(IsKeyPressed(KEY_BACKSPACE)) //TODO dont use attacks when weapon is not existing
	{
		m_Moves.clear();
		actionpoints = 2;
	}

	if (OldScreenWidth != GetScreenWidth() || OldScreenHeight != GetScreenHeight())
		RelocateUI();
	if (IsKeyPressed(KEY_ESCAPE))
	{
		auto pauseScene = std::make_shared<PauseScene>(Host);
		pauseScene->SetBackScene(Host->SetScene(pauseScene));
	}

	if (IsKeyDown(KEY_H) ||
		(CheckCollisionPointRec(GetMousePosition(),
			 {PosHealslot.x, PosHealslot.y, static_cast<float>(healslot.GetTileWidth() * uiScale),
				 static_cast<float>(healslot.GetTileHeight() * uiScale)}) &&
			IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
	{
		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))healslottriggered = true;
	}
	else
		healslottriggered = false;

	// TODO: Possibly check if there are any action points to even swap weapons
	if (IsKeyDown(KEY_TAB) && weaponslotframe == 0)
		weaponswap = true;
	else if (weaponslotframe != 0)
		weaponswap = true;
	else
		weaponswap = false;

	if (CheckCollisionPointRec(GetMousePosition(),
			{PosAttackButton1.x, PosAttackButton1.y, static_cast<float>(attackbutton.GetTileWidth() * uiScale),
				static_cast<float>(attackbutton.GetTileHeight() * uiScale)}) &&
		(IsMouseButtonDown(MOUSE_BUTTON_LEFT)||IsMouseButtonReleased(MOUSE_BUTTON_LEFT)))
	{
		ABS1 = 2;
		drawtooltipp1 = true;
		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && actionpoints >= m_SelectedWeapon->ApCostAttack1)
		{
			m_Moves.emplace_back(m_SelectedWeapon, &Weapon::Attack1);
			actionpoints -= m_SelectedWeapon->ApCostAttack1;
			m_LastUsedWeapon = m_SelectedWeapon;
		}
	}
	else if (CheckCollisionPointRec(GetMousePosition(),
				 {PosAttackButton1.x, PosAttackButton1.y, static_cast<float>(attackbutton.GetTileWidth() * uiScale),
					 static_cast<float>(attackbutton.GetTileHeight() * uiScale)}))
	{
		ABS1 = 1;
		drawtooltipp1 = true;
	}
	else
	{
		ABS1 = 0;
		drawtooltipp1 = false;
	}

	if (CheckCollisionPointRec(GetMousePosition(),
			{PosAttackButton2.x, PosAttackButton2.y, static_cast<float>(attackbutton.GetTileWidth() * uiScale),
				static_cast<float>(attackbutton.GetTileHeight() * uiScale)}) &&
		(IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_LEFT)))
	{
		ABS2 = 2;
		drawtooltipp2 = true;
		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && actionpoints >= m_SelectedWeapon->ApCostAttack2)
		{
			m_Moves.emplace_back(m_SelectedWeapon, &Weapon::Attack2);
			actionpoints -= m_SelectedWeapon->ApCostAttack2;
			m_LastUsedWeapon = m_SelectedWeapon;
		}
	}
	else if (CheckCollisionPointRec(GetMousePosition(),
				 {PosAttackButton2.x, PosAttackButton2.y, static_cast<float>(attackbutton.GetTileWidth() * uiScale),
					 static_cast<float>(attackbutton.GetTileHeight() * uiScale)}))
	{
		ABS2 = 1;
		drawtooltipp2 = true;
	}
	else
	{
		ABS2 = 0;
		drawtooltipp2 = false;
	}

	if (nextphase)
	{
		nextphase = false;
		prepphase = !prepphase;
	}

	if (prepphase)
	{
		if (IsKeyPressed(KEY_ENTER) && actionpoints >= 0)
			nextphase = true;
	}
	else
	{
		if (m_Character->GetInitiative() > m_Enemy->GetInitiative())
		{
			for (const auto& [weapon, move] : m_Moves)
				std::invoke(move, weapon, *m_Enemy, *m_Character);

			if(m_Enemy->GetCurrentHp()<= 0) Host->SetScene(m_BackScene);
			if(!m_Enemy->GetStatuseffects().frozen)
			{
				if (auto cultist = std::dynamic_pointer_cast<Cultist>(m_Enemy))
				{
					m_Character->GetStatuseffects().SetBurned(1);
				}
				if (m_Character->GetStatuseffects().frozen)
				{
					m_Character->SetHealth(m_Character->GetHealth() -
						(m_Enemy->GetDamage() * m_Enemy->GetStatuseffects().GetColdMultiplier()) * 2);
					m_Character->GetStatuseffects().SetFrozen(false);
				}
				else
					m_Character->SetHealth(m_Character->GetHealth() -
						m_Enemy->GetDamage() * m_Enemy->GetStatuseffects().GetColdMultiplier());
				if (m_Character->GetHealth() <= 0)
					Host->SetScene(std::make_shared<MainMenu>(Host));
			}
		}
		else
		{
			if(!m_Enemy->GetStatuseffects().frozen)
			{
				if (auto cultist = std::dynamic_pointer_cast<Cultist>(m_Enemy))
				{
					m_Character->GetStatuseffects().SetBurned(1);
				}
				if (m_Character->GetStatuseffects().frozen)
				{
					m_Character->SetHealth(m_Character->GetHealth() -
						(m_Enemy->GetDamage() * m_Enemy->GetStatuseffects().GetColdMultiplier()) * 2);
					m_Character->GetStatuseffects().SetFrozen(false);
				}
				else
					m_Character->SetHealth(m_Character->GetHealth() -
						m_Enemy->GetDamage() * m_Enemy->GetStatuseffects().GetColdMultiplier());
				if (m_Character->GetHealth() <= 0)
					Host->SetScene(std::make_shared<MainMenu>(Host));
			}

			for (const auto& [weapon, move] : m_Moves)
				std::invoke(move, weapon, *m_Enemy, *m_Character);

			if(m_Enemy->GetCurrentHp()<= 0) Host->SetScene(m_BackScene);

		}

		m_Moves.clear();

		actionpoints = 2;
		if(m_Enemy->GetStatuseffects().burned)
		{
			m_Enemy->TakeDamage(5);
		}
		m_Enemy->TakeDamage(m_Enemy->GetStatuseffects().GetBleedingDamage());
		if(m_Enemy->GetStatuseffects().GetVineDrain()>0)
		{
			m_Enemy->TakeDamage(m_Enemy->GetStatuseffects().GetVineDrain());
			if(m_Character->GetHealth()+m_Enemy->GetStatuseffects().GetVineDrain() <= m_Character->GetMaxHealth())m_Character->SetHealth(m_Character->GetHealth()+m_Enemy->GetStatuseffects().GetVineDrain());
			else m_Character->SetHealth(m_Character->GetMaxHealth());
		}
		if(m_Enemy->GetCurrentHp()<= 0) Host->SetScene(m_BackScene);

		if(m_Character->GetStatuseffects().burned)
		{
			m_Character->SetHealth(m_Character->GetHealth()-5);
		}
		m_Character->SetHealth(m_Character->GetHealth()-m_Character->GetStatuseffects().GetBleedingDamage());
		if(m_Character->GetHealth() <=0) Host->SetScene(std::make_shared<MainMenu>(Host));

		m_Character->GetStatuseffects().CombatUpdate();
		m_Enemy->GetStatuseffects().CombatUpdate();

		if(m_Character->GetOxygen()>0)m_Character->SetOxygen(m_Character->GetOxygen()-1); //Oxygen hardcoded
		else m_Character->SetHealth(m_Character->GetHealth()-1);
		if(m_Character->GetHealth() <=0) Host->SetScene(std::make_shared<MainMenu>(Host));
		nextphase = true;
	}

	TSLweaponslot += GetFrameTime();
	TSLpointdisplay += GetFrameTime();

	if (TSLweaponslot >= FDweaponslot)
	{
		TSLweaponslot -= FDweaponslot;
		if (weaponswap)
		{
			if(weaponslotframe >= 6 && !m_swapped)
			{
				if (m_LastUsedWeapon && m_LastUsedWeapon == m_SelectedWeapon)
					actionpoints--; // NOTE: Remove 1 action point when swapping from the last used weapon

				m_swapped = true;
				m_PreviousWeapon.swap(m_SelectedWeapon);
				m_SelectedWeapon.swap(m_NextWeapon);

				if (m_LastUsedWeapon && m_LastUsedWeapon == m_SelectedWeapon)
					actionpoints++; // NOTE: Add back 1 action point when swapping to the last used weapon
			}

			weaponslotframe = (weaponslotframe + 1) % weaponslot.GetTileCountX();
		}
		else m_swapped = false;
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

	Rectangle characterArea{};
	characterArea.width = 400;
	characterArea.height = 400;
	characterArea.x = static_cast<float>(GetScreenWidth() * 0.27) - characterArea.width / 2;
	characterArea.y = static_cast<float>(GetScreenHeight() * 0.87) - characterArea.height;
	m_SelectedWeapon->DrawSprite(characterArea);

	// UI
	if(m_NextWeapon != nullptr && (weaponslotframe <= 3 || weaponslotframe >= 7))
	{
		m_NextWeapon->Weaponsprites10.DrawTileScaled(m_NextWeapon->SpriteID,
			0,
			{PosWeaponslot.x + 4 * uiScale, PosWeaponslot.y + 8 * uiScale},
			uiScale,
			WHITE
		);
	}
	if(m_SelectedWeapon != nullptr && (weaponslotframe <= 3 || weaponslotframe >= 7))
	{
		m_SelectedWeapon->Weaponsprites16.DrawTileScaled(m_SelectedWeapon->SpriteID,
			0,
			{PosWeaponslot.x + 34 * uiScale, PosWeaponslot.y + 5 * uiScale},
			uiScale,
			WHITE
		);
	}
	if(m_PreviousWeapon != nullptr && (weaponslotframe <= 3 || weaponslotframe >= 7))
	{
		m_PreviousWeapon->Weaponsprites10.DrawTileScaled(m_PreviousWeapon->SpriteID,
			0,
			{PosWeaponslot.x +70 * uiScale, PosWeaponslot.y + 8 * uiScale},
			uiScale,
			WHITE
		);
	}

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

	if(actionpoints == 2)
	{
		energyindicator.DrawTileScaled(0,
			0,
			{PosPointdisplay.x + (pointdisplay.GetTileWidth()/2-energyindicator.GetTileWidth()/2-1)*uiScale, PosPointdisplay.y + (pointdisplay.GetTileHeight()/2-energyindicator.GetTileHeight()/2)*uiScale},
			uiScale,
			WHITE);
	}
	if(actionpoints == 1)
	{
		energyindicator.DrawTileScaled(0,
			1,
			{PosPointdisplay.x + (pointdisplay.GetTileWidth()/2-energyindicator.GetTileWidth()/2-1)*uiScale, PosPointdisplay.y + (pointdisplay.GetTileHeight()/2-energyindicator.GetTileHeight()/2)*uiScale},
			uiScale,
			WHITE);
	}

	//Attacks
	if(m_SelectedWeapon != nullptr)
	{
		m_SelectedWeapon->ButtonAttack1.DrawTileScaled(0,
			ABS1,
			PosAttackButton1,
			uiScale-2,
			WHITE);
		m_SelectedWeapon->ButtonAttack2.DrawTileScaled(0,
			ABS2,
			PosAttackButton2,
			uiScale-2,
			WHITE);
		if(drawtooltipp1)
		{
			DrawTexturePro(m_SelectedWeapon->TooltippAttack1,
				Rectangle{0, 0, static_cast<float>(m_SelectedWeapon->TooltippAttack1.width), static_cast<float>(m_SelectedWeapon->TooltippAttack1.height)},
				Rectangle{static_cast<float>(GetScreenWidth()/2-m_SelectedWeapon->TooltippAttack1.width/2*3),static_cast<float>(GetScreenHeight()/2-m_SelectedWeapon->TooltippAttack1.height/2*3), static_cast<float>(m_SelectedWeapon->TooltippAttack1.width*3), static_cast<float>(m_SelectedWeapon->TooltippAttack1.height*3)},
				{0, 0},
				0,
				WHITE);
		}
		if(drawtooltipp2)
		{
			DrawTexturePro(m_SelectedWeapon->TooltippAttack2,
				Rectangle{0, 0, static_cast<float>(m_SelectedWeapon->TooltippAttack2.width), static_cast<float>(m_SelectedWeapon->TooltippAttack2.height)},
				Rectangle{static_cast<float>(GetScreenWidth()/2-m_SelectedWeapon->TooltippAttack2.width/2*3),static_cast<float>(GetScreenHeight()/2-m_SelectedWeapon->TooltippAttack2.height/2*3), static_cast<float>(m_SelectedWeapon->TooltippAttack2.width*3), static_cast<float>(m_SelectedWeapon->TooltippAttack2.height*3)},
				{0, 0},
				0,
				WHITE);
		}
	}

	healslot.DrawTileScaled(static_cast<int>(healslottriggered),
		0,
		PosHealslot,
		uiScale,
		WHITE);

	//StatusEffects
	Vector2 statusPositionPlayer = Vector2{PosHPBarPlayer.x+Statuseffects.GetTileWidth() * uiScale, PosHPBarPlayer.y + HPBarPlayer.GetTileHeight() * uiScale+ Statuseffects.GetTileWidth()/2 * uiScale};
		if(m_Character->GetStatuseffects().burned)
		{
			Statuseffects.DrawTileScaled(0,
				0, statusPositionPlayer,
				uiScale,
				WHITE);
			statusPositionPlayer.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}
		if(m_Character->GetStatuseffects().GetBleedingDamage() > 0)
		{
			Statuseffects.DrawTileScaled(1,
				0, statusPositionPlayer,
				uiScale,
				WHITE);
			statusPositionPlayer.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}
		if(m_Character->GetStatuseffects().GetColdMultiplier() < 1)
		{
			Statuseffects.DrawTileScaled(2,
				0, statusPositionPlayer,
				uiScale,
				WHITE);
			statusPositionPlayer.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}
		if(m_Character->GetStatuseffects().frozen)
		{
			Statuseffects.DrawTileScaled(3,
				0, statusPositionPlayer,
				uiScale,
				WHITE);
			statusPositionPlayer.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}

		Vector2 statusPositionEnemy = Vector2{PosHPBarEnemy.x+Statuseffects.GetTileWidth() * uiScale, PosHPBarEnemy.y + HPBarEnemy.GetTileHeight() * uiScale+ Statuseffects.GetTileWidth()/2 * uiScale};
		if(m_Enemy->GetStatuseffects().burned)
		{
			Statuseffects.DrawTileScaled(0,
				0, statusPositionEnemy,
				uiScale,
				WHITE);
			statusPositionEnemy.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}
		if(m_Enemy->GetStatuseffects().GetBleedingDamage() > 0)
		{
			Statuseffects.DrawTileScaled(1,
				0, statusPositionEnemy,
				uiScale,
				WHITE);
			statusPositionEnemy.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}
		if(m_Enemy->GetStatuseffects().GetColdMultiplier() < 1)
		{
			Statuseffects.DrawTileScaled(2,
				0, statusPositionEnemy,
				uiScale,
				WHITE);
			statusPositionEnemy.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}
		if(m_Enemy->GetStatuseffects().frozen)
		{
			Statuseffects.DrawTileScaled(3,
				0, statusPositionEnemy,
				uiScale,
				WHITE);
			statusPositionEnemy.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}
		if(m_Enemy->GetStatuseffects().GetVineDrain()>0)
		{
			Statuseffects.DrawTileScaled(4,
				0, statusPositionEnemy,
				uiScale,
				WHITE);
			statusPositionEnemy.x += Statuseffects.GetTileWidth() *1.5 * uiScale;
		}

		//Health

	HPBarEnemy.DrawTileScaled(0,
		1,
		PosHPBarEnemy,
		uiScale,
		WHITE);
	Vector2 HPBarEnemyState = {static_cast<float>(HPBarEnemy.GetTileWidth()* HPBarEnemyPercent), static_cast<float>(HPBarEnemy.GetTileHeight())};
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
	m_PreviousWeapon = m_Character->GetWeapon(0);
	m_SelectedWeapon = m_Character->GetWeapon(1);
	m_NextWeapon = m_Character->GetWeapon(2);
}

auto Redge::CombatScene::SetEnemy(std::shared_ptr<Enemy> enemy) -> void
{
	m_Enemy = std::move(enemy);
}

#pragma clang diagnostic pop
