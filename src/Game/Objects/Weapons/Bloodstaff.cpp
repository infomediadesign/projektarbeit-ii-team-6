#include "Bloodstaff.h"
#include "Game/Objects/Enemies/Enemy.h"
auto Redge::Bloodstaff::Attack1(Enemy& Enemy, Character& Character) -> void
{
	Enemy.GetStatuseffects().MultiplyBleedingTimer(2);
}
auto Redge::Bloodstaff::Attack2(Enemy& Enemy, Character& Character) -> void
{
}
