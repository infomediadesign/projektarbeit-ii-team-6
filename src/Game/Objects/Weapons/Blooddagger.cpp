#include "Blooddagger.h"
#include "Game/Objects/Enemies/Enemy.h"

auto Redge::Blooddagger::Attack1(Enemy& Enemy, Character& Character) -> void
{
	Enemy.TakeDamage(5);
	Enemy.GetStatuseffects().SetBleeding();
}
auto Redge::Blooddagger::Attack2(Enemy& Enemy, Character& Character) -> void
{
	Enemy.TakeDamage(Enemy.GetStatuseffects().GetBleedingDamage());
}
