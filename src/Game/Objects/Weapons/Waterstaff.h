#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Waterstaff final: public Weapon
	{
	public:
		Waterstaff() : Weapon("assets/UI/Combat/WeaponIdle/WasserStabIdle.png")
		{
			ApCostAttack1 = 2;
			ApCostAttack2 = 1;
			SpriteID = 2;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/HealingNatureDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/ColdWindDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/HealingNature.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/ColdWind.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
