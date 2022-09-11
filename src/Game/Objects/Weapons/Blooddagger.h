#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Blooddagger final: public Weapon
	{
	public:
		Blooddagger()
		{
			ApCostAttack1 = 1;
			ApCostAttack2 = 1;
			SpriteID = 8;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/AttackDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/AttackDescription.png");
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
