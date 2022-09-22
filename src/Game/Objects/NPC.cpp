#include "NPC.h"

namespace Redge
{
	NPC::NPC(Vector2 position, const char* file, float frameDuration) :
		Tiled::Object(position), m_Animations(file, 8, 1), m_FrameDuration(frameDuration)
	{
		Position.x -= m_Animations.GetTileWidth() / 2;
		Position.y -= m_Animations.GetTileHeight() / 2;
	}

	auto NPC::Update(Redge::Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		m_Frametime += GetFrameTime();
		if (m_Frametime >= m_FrameDuration)
		{
			m_Frametime -= m_FrameDuration;
			++m_AnimationFrame %= m_Animations.GetTileCountX();
		}
	}
	auto NPC::Render() const -> void
	{
		m_Animations.DrawTile(m_AnimationFrame, 0, Position);
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::NPC>::from_json(const json& json) -> Redge::NPC
{
	auto name = json["name"].get<std::string>();

	if (name == "Scientist")
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/scientistIdle.png",
			0.2);

	if (name == "Blacksmith")
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/smithIdle.png",
			0.4);

	if (name == "Shopkeeper")
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/ShopkeeperIdle.png",
			0.3);

	if (name == "Banker")
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/bankerIdle.png",
			0.2);

	throw std::runtime_error("Unknown NPC type");
}
