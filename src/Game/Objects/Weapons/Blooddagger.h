#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Blooddagger final: public Weapon
	{
	public:
		Blooddagger() : Weapon("assets/UI/Combat/WeaponIdle/BlutDaggerIdle.png")
		{
			ApCostAttack1 = 1;
			ApCostAttack2 = 1;
			SpriteID = 8;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/BloodSlashDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/BloodPierceDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/BloodSlash.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/BloodPierce.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
