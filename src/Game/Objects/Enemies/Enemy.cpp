#include "Enemy.h"

namespace Redge
{
	Enemy::Enemy(Vector2 position, float maximumHp, float initiative, float damage) :
		Tiled::Object(position), m_MaximumHp(maximumHp), m_CurrentHp(maximumHp), m_Initiative(initiative),
		m_Damage(damage)
	{
	}

	auto Enemy::GetCollisionType() const -> CollisionType
	{
		return CollisionTypeEnemy;
	}

	auto Enemy::GetMaximumHp() const -> float
	{
		return m_MaximumHp;
	}

	auto Enemy::GetCurrentHp() const -> float
	{
		return m_CurrentHp;
	}

	auto Enemy::TakeDamage(float amount) -> void
	{
		m_CurrentHp -= amount;
	}

	auto Enemy::GetInitiative() const -> float
	{
		return m_Initiative;
	}

	auto Enemy::GetDamage() const -> float
	{
		return m_Damage;
	}

	auto Enemy::GetStatuseffects() -> Statuseffects&
	{
		return m_Statuseffects;
	}
	auto Statuseffects::CombatUpdate() -> void
	{
		if (burnedtimer > 0)
		{
			burnedtimer--;
		}
		else
			burned = false;

		if (frozentimer > 0)
		{
			frozentimer--;
		}
		else
			frozen = false;

		for (int i = 0; i < 4; i++)
		{
			if (bleeding[i] > 0)
			{
				bleeding[i]--;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if(cold[i] > 0)
			{
				cold[i]--;
			}
		}
	}
	auto Statuseffects::SetBurned(uint8_t timer) -> void
	{
		burned = true;
		burnedtimer += timer;
	}
	auto Statuseffects::SetFrozen(bool state) -> void
	{
		frozen = state;
		if(state) frozentimer = 2;
		else frozentimer = 0;
	}
	auto Statuseffects::SetBleeding() -> void
	{
		bool added = false;
		for (int i = 0; i < 4; i++)
		{
			if (bleeding[i] == 0)
			{
				bleeding[i] = bleedingtimer;
				added = true;
				break;
			}
		}
		if (!added)
		{
			bleeding[0] = bleedingtimer;
		}
	}
	auto Statuseffects::SetCold() -> void
	{
		bool added = false;
		for (int i = 0; i < 3; i++)
		{
			if (cold[i] == 0)
			{
				cold[i] = coldtimer;
				added = true;
				break;
			}
		}
		if (!added)
		{
			cold[0] = coldtimer;
		}
	}
	auto Statuseffects::GetColdMultiplier() -> float
	{
		float multiplier = 1;
		for (int i = 0; i < 3; i++)
		{
			if(cold[i] > 0)
			{
				multiplier -= 0.15;
			}
		}
		return multiplier;
	}
	auto Statuseffects::GetBleedingDamage() -> float
	{
		float damage = 0;
		for (int i = 0; i < 4; i++)
		{
			if (bleeding[i] > 0)
			{
				damage += 5;
			}
		}
		return damage;
	}
	auto Statuseffects::GetVineDrain() -> float
	{
		float value = 0;
		for (int i = 0; i < 5; i++)
		{
			if (vine[i])
			{
				value += 5;
			}
		}
		return value;
	}
	auto Statuseffects::SetVineZero() -> void
	{
		for (int i = 0; i < 5; i++)
		{
			if (vine[i])
			{
				vine[i] = false;
			}
		}
	}
} // namespace Redge
