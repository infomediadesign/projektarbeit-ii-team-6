#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Staffofearth final: public Weapon
	{
	public:
		Staffofearth() : Weapon("assets/UI/Combat/WeaponIdle/StabDerErdeIdle.png")
		{
			ApCostAttack1 = 2;
			ApCostAttack2 = 1;
			SpriteID = 3;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/SacrificialStrikeDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/EnvyStrikeDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/SacrificialStrike.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/EnvyStrike.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
