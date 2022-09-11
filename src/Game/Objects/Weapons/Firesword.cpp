#include "Firesword.h"
#include "Game/Objects/Enemies/Enemy.h"
auto Redge::Firesword::Attack1(Enemy& Enemy, Character& Character) -> void
{
	Enemy.TakeDamage(5);
	Enemy.GetStatuseffects().SetBurned(1);
}
auto Redge::Firesword::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(Enemy.GetStatuseffects().burned)Enemy.TakeDamage(20);
	else Enemy.TakeDamage(5);
}
