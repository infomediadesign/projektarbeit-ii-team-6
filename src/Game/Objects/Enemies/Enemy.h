#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "Tiled/Object.h"

namespace Redge
{
	class Enemy : public Tiled::Object, public ICollidable
	{
	public:
		Enemy(Vector2 position, float maximumHp, float initiative, float damage);

		[[nodiscard]] auto GetCollisionType() const -> CollisionType final;

		[[nodiscard]] auto GetMaximumHp() const -> float;
		[[nodiscard]] auto GetCurrentHp() const -> float;
		auto TakeDamage(float amount) -> void;

		[[nodiscard]] auto GetInitiative() const -> float;
		[[nodiscard]] auto GetDamage() const -> float;

		virtual auto DrawSprite(Rectangle destination) const -> void = 0;

	private:
		float m_MaximumHp{};
		float m_CurrentHp{};

		float m_Initiative{};
		float m_Damage{};
	};
} // namespace Redge
