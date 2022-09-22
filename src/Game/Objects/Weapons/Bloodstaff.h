#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Bloodstaff final: public Weapon
	{
	public:
		Bloodstaff() : Weapon("assets/UI/Combat/WeaponIdle/BlutMagieStabIdle.png")
		{
			ApCostAttack1 = 2;
			ApCostAttack2 = 2;
			SpriteID = 7;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/BloodCurseDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/BloodRitualDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/BloodCurse.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/BloodRitual.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
