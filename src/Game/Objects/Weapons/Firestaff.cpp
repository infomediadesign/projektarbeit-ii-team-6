#include "Firestaff.h"
#include "Game/Objects/Enemies/Enemy.h"
auto Redge::Firestaff::Attack1(Enemy& Enemy, Character& Character) -> void
{
	Enemy.GetStatuseffects().SetBurned(4);
}
auto Redge::Firestaff::Attack2(Enemy& Enemy, Character& Character) -> void
{
	Enemy.TakeDamage(5*Enemy.GetStatuseffects().GetBurnedTimer());
}
