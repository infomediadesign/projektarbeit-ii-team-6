#include "Cactus.h"

namespace Redge
{
	Cactus::Cactus(Vector2 position, uint8_t spriteIndex) : Tiled::Object(position), m_SpriteIndex(spriteIndex)
	{
	}

	auto Cactus::Render() const -> void
	{
		Vector2 position = Position;
		position.x -= m_Sprites.GetTileWidth() / 2;
		position.y -= m_Sprites.GetTileHeight();

		m_Sprites.DrawTile(m_SpriteIndex, 0, position);
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Cactus>::from_json(const json& json) -> Redge::Cactus
{
	assert(json["point"].get<bool>());
	auto name = json["name"].get<std::string>();

	if (name == "Cactus1")
		return Redge::Cactus(Vector2{json["x"].get<float>(), json["y"].get<float>()}, 0);

	if (name == "Cactus2")
		return Redge::Cactus(Vector2{json["x"].get<float>(), json["y"].get<float>()}, 1);

	if (name == "Cactus3")
		return Redge::Cactus(Vector2{json["x"].get<float>(), json["y"].get<float>()}, 2);

	if (name == "Cactus4")
		return Redge::Cactus(Vector2{json["x"].get<float>(), json["y"].get<float>()}, 3);

	if (name == "Cactus5")
		return Redge::Cactus(Vector2{json["x"].get<float>(), json["y"].get<float>()}, 4);

	throw std::runtime_error("Unknown NPC type");
}
