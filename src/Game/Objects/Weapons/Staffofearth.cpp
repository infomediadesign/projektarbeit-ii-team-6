#include "Staffofearth.h"
#include "Game/Objects/Enemies/Enemy.h"
#include "Game/Objects/Character.h"

auto Redge::Staffofearth::Attack1(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen)
	{
		Enemy.TakeDamage(40);
	}
	else Enemy.TakeDamage(80);
	if(!Character.GetStatuseffects().frozen)
	{
		Character.SetHealth(Character.GetHealth()-20);
	}
	else Character.SetHealth(Character.GetHealth()-40);
}
auto Redge::Staffofearth::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(Enemy.GetCurrentHp()/Enemy.GetMaximumHp() > Character.GetHealth()/Character.GetMaxHealth())
	{
		if(!Enemy.GetStatuseffects().frozen)
		{
			Enemy.TakeDamage(15);
		}
		else Enemy.TakeDamage(30);
	}
}