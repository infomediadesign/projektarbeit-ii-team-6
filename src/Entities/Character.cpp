#include "Character.h"

#include <raylib.h>

namespace Redge
{
	auto Character::Draw() const -> void
	{
		DrawScaled(1);
	}

	auto Character::DrawScaled(float scale) const -> void
	{
		m_Character.DrawTileScaled(m_CurrentFrame, static_cast<uint16_t>(m_Direction), m_Position, scale);
	}

	auto Character::NextFrame() -> void
	{
		++m_CurrentFrame %= m_Character.GetTileCountX();
	}

	auto Character::ResetFrame() -> void
	{
		m_CurrentFrame = 0;
	}

	auto Character::GetPosition() const -> Vector2
	{
		return m_Position;
	}

	auto Character::GetDirection() const -> Orientation
	{
		return m_Direction;
	}

	auto Character::SetPosition(Vector2 pos) -> void
	{
		m_Position = pos;
	}

	auto Character::SetDirection(Orientation dir) -> void
	{
		if (m_Direction != dir)
			ResetFrame();

		m_Direction = dir;
	}
} // namespace Redge
