#include "Firesword.h"
#include "Game/Objects/Enemies/Enemy.h"
auto Redge::Firesword::Attack1(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen)Enemy.TakeDamage(5);
	else Enemy.TakeDamage(10);
	Enemy.GetStatuseffects().SetBurned(1);
}
auto Redge::Firesword::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen)
	{
		if (Enemy.GetStatuseffects().burned)
			Enemy.TakeDamage(20);
		else
			Enemy.TakeDamage(5);
	}
	else
	{
		if (Enemy.GetStatuseffects().burned)
			Enemy.TakeDamage(40);
		else
			Enemy.TakeDamage(10);
	}
}
