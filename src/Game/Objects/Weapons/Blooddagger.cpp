#include "Blooddagger.h"
#include "Game/Objects/Enemies/Enemy.h"

auto Redge::Blooddagger::Attack1(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen) Enemy.TakeDamage(5);
	else Enemy.TakeDamage(10);
	Enemy.GetStatuseffects().SetBleeding();
}
auto Redge::Blooddagger::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen) Enemy.TakeDamage(Enemy.GetStatuseffects().GetBleedingDamage());
	else Enemy.TakeDamage(2 * Enemy.GetStatuseffects().GetBleedingDamage());
}
