#pragma once
#include "Game/Objects/Weapons/Weapon.h"

namespace Redge
{
	class Firesword final: public Weapon
	{
		public:
			Firesword();
			auto Attack1(Enemy& Enemy) -> void override;
			auto Attack2(Enemy& Enemy) -> void override;
	};
} // namespace Redge
