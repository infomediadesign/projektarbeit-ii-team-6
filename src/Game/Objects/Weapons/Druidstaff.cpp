#include "Druidstaff.h"
#include "Game/Objects/Enemies/Enemy.h"
#include "Game/Objects/Character.h"
auto Redge::Druidstaff::Attack1(Enemy& Enemy, Character& Character) -> void
{
 	Character.GetStatuseffects().ClearStatuseffects();
}
auto Redge::Druidstaff::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(Character.GetHealth()+20 <= Character.GetMaxHealth())
	{
		Character.SetHealth(Character.GetHealth()+20);
	}
	else Character.SetHealth(Character.GetMaxHealth());
}
