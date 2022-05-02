#include "Character.h"

#include <raylib.h>

namespace Redge
{
	auto Character::NextFrame() -> void
	{
		currentframe = (currentframe + 1) % m_Character.GetTileCountX();
	}

	auto Character::Draw() const -> void
	{
		m_Character.DrawTile(currentframe, static_cast<int>(Direction), Position);
	}

	auto Character::DrawScaled(float scale) const -> void
	{
		m_Character.DrawTileScaled(currentframe, static_cast<int>(Direction), Position, scale);
	}
} // namespace Redge
