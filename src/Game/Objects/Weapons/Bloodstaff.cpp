#include "Bloodstaff.h"
#include "Game/Objects/Enemies/Enemy.h"
#include "Game/Objects/Character.h"
auto Redge::Bloodstaff::Attack1(Enemy& Enemy, Character& Character) -> void
{
	Enemy.GetStatuseffects().MultiplyBleedingTimer(2);
}
auto Redge::Bloodstaff::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(Character.GetHealth()+Enemy.GetStatuseffects().GetBleedingDamage() * 2 <= Character.GetMaxHealth())
	{
		Character.SetHealth(Character.GetHealth()+Enemy.GetStatuseffects().GetBleedingDamage() * 2);
	}
	else Character.SetHealth(Character.GetMaxHealth());
	Enemy.GetStatuseffects().ClearBleed();
}
