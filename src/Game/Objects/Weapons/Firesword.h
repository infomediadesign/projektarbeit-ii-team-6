#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Firesword final: public Weapon
	{
		public:
			Firesword() : Weapon("assets/UI/Combat/WeaponIdle/feuerSchwertIdle.png")
			{
				ApCostAttack1 = 1;
				ApCostAttack2 = 1;
				SpriteID = 4;
				TooltippAttack1 = LoadTexture("assets/UI/Combat/attacks/FireSmiteDescription.png");
				TooltippAttack2 = LoadTexture("assets/UI/Combat/attacks/FireSlashDescription.png");
				ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/attacks/FireSmite.png", 1, 3);
				ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/attacks/FireSlash.png", 1, 3);
			};
			auto Attack1(Enemy& Enemy, Character& Character) -> void override;
			auto Attack2(Enemy& Enemy, Character& Character) -> void override;
	};
} // namespace Redge
