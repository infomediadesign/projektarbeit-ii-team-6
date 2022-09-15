#include "Icespear.h"
#include "Game/Objects/Enemies/Enemy.h"
auto Redge::IceSpear::Attack1(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen) Enemy.TakeDamage(5);
	else Enemy.TakeDamage(10);
	Enemy.GetStatuseffects().SetCold();
}
auto Redge::IceSpear::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen) Enemy.TakeDamage(25);
	else Enemy.TakeDamage(50);
}
