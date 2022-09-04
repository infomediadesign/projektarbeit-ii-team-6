#pragma once
#include "Game/Scenes/CombatScene.h"

namespace Redge
{
	class Enemy;
	class Weapon
	{
	public:
		virtual ~Weapon() = default;
		virtual auto Attack1(Enemy& Enemy) -> void = 0;
		virtual auto Attack2(Enemy& Enemy) -> void = 0;
	};
} // namespace Redge
