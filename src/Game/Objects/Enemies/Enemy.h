#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "Tiled/Object.h"
#include "Game/Scenes/CombatScene.h"

namespace Redge
{
	struct Statuseffects
	{
		bool burned = false;
		uint8_t burnedtimer = 0;

		bool frozen = false;
		uint8_t frozentimer = 0;

		uint8_t bleeding[4] = {};
		const uint8_t bleedingtimer = 2;

		uint8_t cold[3] = {0, 0 ,0};
		const uint8_t coldtimer = 4;


		auto SetBurned(uint8_t timer) -> void;
		auto SetFrozen() -> void;
		auto SetBleeding() -> void;
		auto GetBleedingDamage() -> float;
		auto SetCold() -> void;
		auto GetColdMultiplier() -> float;
		auto CombatUpdate() -> void;
	};
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
		auto GetStatuseffects() -> Statuseffects;

		virtual auto DrawSprite(Rectangle destination) const -> void = 0;

	private:
		Statuseffects m_Statuseffects;
		float m_MaximumHp{};
		float m_CurrentHp{};

		float m_Initiative{};
		float m_Damage{};
	};
} // namespace Redge
