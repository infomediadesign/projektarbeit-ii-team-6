#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Ironhammer final: public Weapon
	{
	public:
		Ironhammer() : Weapon("assets/UI/Combat/WeaponIdle/EisenHammerIdle.png")
		{
			ApCostAttack1 = 2;
			ApCostAttack2 = 2;
			SpriteID = 5;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/IronStrikeDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/EarthquakeDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/IronStrike.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/Earthquake.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
