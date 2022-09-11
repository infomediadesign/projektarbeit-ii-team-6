#pragma once
#include "Game/Scene.h"
#include "Raylib/Tileset.h"
#include "Game/Objects/Character.h"
#include "Game/Objects/Weapons/Weapon.h"
#include "Game/Objects/Weapons/Firesword.h"
#include "Game/Objects/Weapons/Firestaff.h"

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
		bool prepphase = true;
		uint16_t actionpoints = 2;
		bool m_swapped = false;
		std::shared_ptr<Weapon> m_PreviousWeapon = nullptr;
		std::shared_ptr<Weapon> m_SelectedWeapon = std::make_shared<Firesword>();
		std::shared_ptr<Weapon> m_NextWeapon = std::make_shared<Firestaff>();

		std::shared_ptr<Character> m_Character{};

		using SelectedMove = void(Weapon::*)(Enemy&, Character&);
		std::vector<std::pair<std::shared_ptr<Weapon>, SelectedMove>> m_Moves{};



		float m_MaxHealth;
		float m_Health;
		float m_MaxOxygen;
		float m_Oxygen;

		float m_EnemyHealth;
		float m_EnemyMaxHealth;

		std::shared_ptr<Enemy> m_Enemy{};

		float OldScreenWidth;
		float OldScreenHeight;

		bool weaponswap = false;

		uint16_t uiScale = 4;

		Raylib::Tileset Statuseffects = Raylib::Tileset("assets/UI/Combat/Debuffs.png", 5, 1);

		Vector2 PosWeaponslot;
		Raylib::Tileset weaponslot = Raylib::Tileset("assets/UI/Combat/Weaponslot.png", 10 ,1);
		uint16_t weaponslotframe = 0;
		float TSLweaponslot = 0; //TSL -> Time since last
		float FDweaponslot = 0.17; //FD -> Frame Duration

		Vector2 PosPointdisplay;
		Raylib::Tileset pointdisplay = Raylib::Tileset("assets/UI/Combat/PointDisplay.png", 17, 1);
		Raylib::Tileset energyindicator = Raylib::Tileset("assets/UI/Combat/EnergyIndicator.png",1,2);
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
		bool rendertooltipp1;
		bool rendertooltipp2;

		Vector2 PosHPBarEnemy;
		Raylib::Tileset HPBarEnemy = Raylib::Tileset("assets/UI/Combat/HpBarCombatEnemy.png", 1,2 );
		float HPBarEnemyPercent = 1.f;

		Vector2 PosHPBarPlayer;
		Raylib::Tileset HPBarPlayer = Raylib::Tileset("assets/UI/Combat/HpBarCombat.png", 1 ,3);
		float HPBarPlayerO2Percent = 1.f;
		float HPBarPlayerPercent = 1.f;

		Texture2D background = LoadTexture("assets/UI/Combat/CombatBackground.png");
		std::shared_ptr<Scene> m_BackScene{};
	};
} // namespace Redge
