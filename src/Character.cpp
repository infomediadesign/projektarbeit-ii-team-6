#include "Character.h"

#include <raylib.h>

namespace Redge
{
	auto Character::Draw() const -> void
	{
		m_Character.DrawTile(static_cast<int>(Direction), 0, Position);
	}

	auto Character::DrawScaled(float scale) const -> void
	{
		m_Character.DrawTileScaled(static_cast<int>(Direction), 0, Position, scale);
	}
} // namespace Redge
