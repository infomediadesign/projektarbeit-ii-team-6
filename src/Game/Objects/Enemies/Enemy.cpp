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
} // namespace Redge
