#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Druidstaff final: public Weapon
	{
	public:
		Druidstaff()
		{
			ApCostAttack1 = 1;
			ApCostAttack2 = 2;
			SpriteID = 0;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/PlantsBlessingDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/HealingNatureDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/PlantsBlessing.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/HealingNature.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
