#include "Firestaff.h"
#include "Game/Objects/Enemies/Enemy.h"
auto Redge::Firestaff::Attack1(Enemy& Enemy, Character& Character) -> void
{
	Enemy.GetStatuseffects().SetBurned(5);
}
auto Redge::Firestaff::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen) Enemy.TakeDamage(5*Enemy.GetStatuseffects().GetBurnedTimer());
	else Enemy.TakeDamage(2*5*Enemy.GetStatuseffects().GetBurnedTimer());
}
