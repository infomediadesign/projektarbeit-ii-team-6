#pragma once
#include "Game/Objects/Weapons/Weapon.h"
namespace Redge
{
	class Firestaff final : public Weapon
	{
	public:
		Firestaff()
		{
			ApCostAttack1 = 2;
			ApCostAttack2 = 2;
			SpriteID = 1;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/AttackDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/AttackDescription.png");
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge