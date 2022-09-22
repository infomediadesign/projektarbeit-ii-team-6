#pragma once
#include "Game/Objects/Weapons/Weapon.h"
namespace Redge
{
	class Firestaff final : public Weapon
	{
	public:
		Firestaff() : Weapon("assets/UI/Combat/WeaponIdle/feuerstabIdle.png")
		{
			ApCostAttack1 = 2;
			ApCostAttack2 = 2;
			SpriteID = 1;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/FireStormDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/FireCurseDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/FireStorm.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/FireCurse.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
