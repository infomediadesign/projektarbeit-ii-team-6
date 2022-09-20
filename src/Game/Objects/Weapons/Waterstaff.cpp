#include "Waterstaff.h"
#include "Game/Objects/Enemies/Enemy.h"
#include "Game/Objects/Character.h"
auto Redge::Waterstaff::Attack1(Enemy& Enemy, Character& Character) -> void
{
	float consumed = Character.GetStatuseffects().ConsumeCold();
	if(Character.GetHealth()+consumed*10 <= Character.GetMaxHealth())
	{
		Character.SetHealth(Character.GetHealth()+consumed*10);
	}
	else Character.SetHealth(Character.GetMaxHealth());
}
auto Redge::Waterstaff::Attack2(Enemy& Enemy, Character& Character) -> void
{
	int case_ = Enemy.GetStatuseffects().GetColdMultiplier() * 100;
	switch(case_){
	case(100-15) :Enemy.TakeDamage(5); break;
	case(100-30) : Enemy.TakeDamage(10); break;
	case(100-45) : Enemy.TakeDamage(15); Enemy.GetStatuseffects().SetFrozen(true); break;
	}
}