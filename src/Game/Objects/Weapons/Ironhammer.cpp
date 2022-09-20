#include "Ironhammer.h"
#include "Game/Objects/Enemies/Enemy.h"
#include "Game/Objects/Character.h"
auto Redge::Ironhammer::Attack1(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen)
	{
		if(Enemy.GetMaximumHp()*0.5 >= Enemy.GetCurrentHp())
		{
			Enemy.TakeDamage(60);
		}
		else Enemy.TakeDamage(30);
	}
	else
	{
		if(Enemy.GetMaximumHp()/2 >= Enemy.GetCurrentHp())
		{
			Enemy.TakeDamage(120);
		}
		else Enemy.TakeDamage(60);
	}
}
auto Redge::Ironhammer::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen)
	{
		if(Character.GetMaxHealth()*0.34 >= Character.GetHealth())
		{
			Enemy.TakeDamage(60);
		}
		else Enemy.TakeDamage(30);
	}
	else
	{
		if(Character.GetMaxHealth()*0.34 >= Character.GetHealth())
		{
			Enemy.TakeDamage(120);
		}
		else Enemy.TakeDamage(60);
	}
}

