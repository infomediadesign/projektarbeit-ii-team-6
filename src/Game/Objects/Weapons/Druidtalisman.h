#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Druidtalisman final: public Weapon
	{
	public:
		Druidtalisman()
		{
			ApCostAttack1 = 1;
			ApCostAttack2 = 2;
			SpriteID = 9;
			TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/NaturesRevengeDescription.png");
			TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/RagingNatureDescription.png");
			ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/NaturesRevenge.png", 1, 3);
			ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/RagingNature.png", 1, 3);
		};
		auto Attack1(Enemy& Enemy, Character& Character) -> void override;
		auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
