#pragma once
#include "Raylib/Tileset.h"

namespace Redge
{
	class Character;
	class Enemy;
	class Weapon
	{
	public:
		Weapon(const char* idleSprite) : m_IdleSprite(idleSprite, 2, 1){};
		virtual ~Weapon() = default;
		virtual auto Attack1(Enemy& Enemy, Character& Character) -> void = 0;
		virtual auto Attack2(Enemy& Enemy, Character& Character) -> void = 0;
		uint8_t ApCostAttack1;
		uint8_t ApCostAttack2;
		uint8_t SpriteID;
		Raylib::Tileset Weaponsprites16 = Raylib::Tileset("assets/UI/Combat/weaponItemsprites_x16.png", 11, 1);
		Raylib::Tileset Weaponsprites10 = Raylib::Tileset("assets/UI/Combat/weaponItemsprites_x10.png", 11, 1);
		Raylib::Tileset ButtonAttack1 = Raylib::Tileset("assets/UI/Combat/AttackButton.png", 1, 3);
		Raylib::Tileset ButtonAttack2 = Raylib::Tileset("assets/UI/Combat/AttackButton.png", 1, 3);
		Texture2D TooltippAttack1;
		Texture2D TooltippAttack2;

		void DrawSprite(Rectangle area)
		{
			m_IdleSprite.DrawTileTo(m_IdleFrame, 0, area);

			// HACK: This is a terrible hack that doesn't need to be (with use of mutable)
			m_Frametime += GetFrameTime();
			if (m_Frametime >= s_FrameDuration)
			{
				m_Frametime -= s_FrameDuration;
				++m_IdleFrame %= m_IdleSprite.GetTileCountX();
			}
		};

	private:
		Raylib::Tileset m_IdleSprite;
		mutable uint16_t m_IdleFrame = 0;
		static constexpr float s_FrameDuration = 0.3;
		mutable float m_Frametime = 0;
	};
} // namespace Redge
