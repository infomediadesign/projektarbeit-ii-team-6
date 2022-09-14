#pragma once
#include "Raylib/Tileset.h"

namespace Redge
{
	class Character;
	class Enemy;
	class Weapon
	{
	public:
		virtual ~Weapon() = default;
		virtual auto Attack1(Enemy& Enemy, Character& Character) -> void = 0;
		virtual auto Attack2(Enemy& Enemy, Character& Character) -> void = 0;
		uint8_t ApCostAttack1;
		uint8_t ApCostAttack2;
		uint8_t SpriteID;
		Raylib::Tileset Weaponsprites16 = Raylib::Tileset("assets/UI/Combat/weaponItemsprites_x16.png", 10, 1);
		Raylib::Tileset Weaponsprites10 = Raylib::Tileset("assets/UI/Combat/weaponItemsprites_x10.png", 10, 1);
		Raylib::Tileset ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/AttackButton.png", 1, 3);
		Raylib::Tileset ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/AttackButton.png", 1, 3);
		Texture2D TooltippAttack1;
		Texture2D TooltippAttack2;
	};
} // namespace Redge
