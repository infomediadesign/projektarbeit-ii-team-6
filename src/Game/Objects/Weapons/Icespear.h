#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class IceSpear final: public Weapon
	{
	public:
		IceSpear()
		{
			ApCostAttack1 = 1;
			ApCostAttack2 = 2;
			SpriteID = 6;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/IceStormDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/PiercingIceDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/IceStorm.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/PiercingIce.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
