#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "raylib.h"
#include "Raylib/Tileset.h"
#include "Tiled/Object.h"

namespace Redge
{
	class Cactus final : public Tiled::Object
	{
	public:
		Cactus(Vector2 position, uint8_t spriteIndex);

		auto Render() const -> void override;

	private:
		Raylib::Tileset m_Sprites = Raylib::Tileset("assets/Tilesets/Objects/Cacti.png", 5, 1);
		uint8_t m_SpriteIndex = 0;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Cactus>
{
	static auto from_json(const json& json) -> Redge::Cactus;
};
