#include "Character.h"

#include <raylib.h>

namespace Redge
{
	auto Character::Render() const -> void
	{
		m_Character.DrawTile(m_CurrentFrame, static_cast<uint16_t>(m_Direction), m_Position);
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

	auto Character::GetSize() const -> Vector2
	{
		return Vector2{
			static_cast<float>(m_Character.GetTileWidth()),
			static_cast<float>(m_Character.GetTileHeight())
		};
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
