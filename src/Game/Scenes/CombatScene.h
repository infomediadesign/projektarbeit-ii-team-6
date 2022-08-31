#pragma once
#include "Game/Scene.h"
#include "Raylib/Tileset.h"
#include "Game/Objects/Character.h"

namespace Redge
{
	class CombatScene final : public Scene
	{
	public:
		CombatScene(Game* Host);
		auto Update() -> void override;

		auto SetCharacter(std::shared_ptr<Character> character) -> void;
		auto SetEnemy(std::shared_ptr<Enemy> enemy) -> void;

		auto RenderWorld() const -> void override;
		auto RenderUI() const -> void override;

		auto RelocateUI() -> void;

		auto SetBackScene(std::shared_ptr<Scene> scene) -> std::shared_ptr<Scene>;

	private:

		bool nextphase = false;
		bool prepphase = 1;


		std::shared_ptr<Character> m_Character{};
		float m_MaxHealth;
		float m_Health;
		float m_MaxOxygen;
		float m_Oxygen;

		std::shared_ptr<Enemy> m_Enemy{};

		float OldScreenWidth;
		float OldScreenHeight;

		bool weaponswap = false;

		uint16_t uiScale = 4;

		Vector2 PosWeaponslot;
		Raylib::Tileset weaponslot = Raylib::Tileset("assets/UI/Combat/Weaponslot.png", 4 ,1);
		uint16_t weaponslotframe = 0;
		float TSLweaponslot = 0; //TSL -> Time since last
		float FDweaponslot = 0.17; //FD -> Frame Duration

		Vector2 PosPointdisplay;
		Raylib::Tileset pointdisplay = Raylib::Tileset("assets/UI/Combat/PointDisplay.png", 17, 1);
		uint16_t pointdisplayframe = 0;
		float TSLpointdisplay = 0;
		float FDpointdisplay = 0.10;

		Vector2 PosAttackButton1;
		Vector2 PosAttackButton2;
		Raylib::Tileset attackbutton = Raylib::Tileset("assets/UI/Combat/AttackButton.png",1,3);
		uint16_t ABS1 = 0; //ABS -> Attack button state
		uint16_t ABS2 = 0;

		Vector2 PosHealslot;
		Raylib::Tileset healslot = Raylib::Tileset("assets/UI/Combat/HealSlot.png", 2, 1);
		bool healslottriggered = false;

		Vector2 PosHPBarEnemy;
		Raylib::Tileset HPBarEnemy = Raylib::Tileset("assets/UI/Combat/HpBarCombatEnemy.png", 1,2 );
		float HPBarEnemyPercent = 1.f;
		Vector2 HPBarEnemyState = {static_cast<float>(HPBarEnemy.GetTileWidth()* HPBarEnemyPercent), static_cast<float>(HPBarEnemy.GetTileHeight())};

		Vector2 PosHPBarPlayer;
		Raylib::Tileset HPBarPlayer = Raylib::Tileset("assets/UI/Combat/HpBarCombat.png", 1 ,3);
		float HPBarPlayerO2Percent = 1.f;
		float HPBarPlayerPercent = 1.f;

		Texture2D background = LoadTexture("assets/UI/Combat/CombatBackground.png");
		std::shared_ptr<Scene> m_BackScene{};
	};
} // namespace Redge
