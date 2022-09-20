#include "NPC.h"

namespace Redge
{
	NPC::NPC(Vector2 position, const char* file) : Tiled::Object(position), m_Animations(file, 8, 1)
	{
		Position.x -= m_Animations.GetTileWidth() / 2;
		Position.y -= m_Animations.GetTileHeight() / 2;
	}

	auto NPC::Update(Redge::Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		m_Frametime += GetFrameTime();
		if (m_Frametime >= s_FrameDuration)
		{
			m_Frametime -= s_FrameDuration;
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
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/scientistIdle.png");

	if (name == "Blacksmith")
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/smithIdle.png");

	if (name == "Shopkeeper")
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/ShopkeeperIdle.png");

	if (name == "Banker")
		return Redge::NPC(Vector2{json["x"].get<float>(), json["y"].get<float>()}, "assets/Entities/bankerIdle.png");

	throw std::runtime_error("Unknown NPC type");
}
