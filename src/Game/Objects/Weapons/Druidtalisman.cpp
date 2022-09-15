#include "Druidtalisman.h"
#include "Game/Objects/Enemies/Enemy.h"
#include "Game/Objects/Character.h"
auto Redge::Druidtalisman::Attack1(Enemy& Enemy, Character& Character) -> void
{
	Enemy.GetStatuseffects().AddVine(1);
}
auto Redge::Druidtalisman::Attack2(Enemy& Enemy, Character& Character) -> void
{
	if(!Enemy.GetStatuseffects().frozen)
	{
		Enemy.TakeDamage(Enemy.GetStatuseffects().GetVineDrain());
		if (Character.GetHealth() + Enemy.GetStatuseffects().GetVineDrain() <= Character.GetMaxHealth())
		{
			Character.SetHealth(Character.GetHealth() + Enemy.GetStatuseffects().GetVineDrain());
		}
		else Character.SetHealth(Character.GetMaxHealth());
	}
	else
		Enemy.TakeDamage(2*Enemy.GetStatuseffects().GetVineDrain());
		if (Character.GetHealth() + 2 * Enemy.GetStatuseffects().GetVineDrain() <= Character.GetMaxHealth())
		{
			Character.SetHealth(Character.GetHealth() + 2 * Enemy.GetStatuseffects().GetVineDrain());
		}
	else Character.SetHealth(Character.GetMaxHealth());
}
