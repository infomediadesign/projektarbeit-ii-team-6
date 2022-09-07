#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Firesword final: public Weapon
	{
		public:
			Firesword()
			{
				ApCostAttack1 = 1;
				ApCostAttack2 = 1;
				SpriteID = 4;
				TooltippAttack1 = LoadTexture("assets/UI/Combat/AttackDescription.png");
				TooltippAttack2 = LoadTexture("assets/UI/Combat/AttackDescription.png");
			};
			auto Attack1(Enemy& Enemy) -> void override;
			auto Attack2(Enemy& Enemy) -> void override;
	};
} // namespace Redge
