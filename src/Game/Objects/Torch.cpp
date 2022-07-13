#include "Torch.h"

namespace Redge
{
	Torch::Torch(Vector2 position) : Tiled::Object(position)
	{
	}

	auto Torch::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		m_Frametime += GetFrameTime();
		if (m_Frametime >= s_FrameDuration)
		{
			m_Frametime -= s_FrameDuration;
			++m_AnimationFrame %= m_Animation.GetTileCountX();
		}
	}

	auto Torch::RenderBelow() const -> void
	{
		m_Animation.DrawTile(m_AnimationFrame, 0,
			Vector2Add(Position,
				Vector2{
					static_cast<float>(-m_Animation.GetTileWidth()) / 2,
					static_cast<float>(-m_Animation.GetTileHeight()) / 2,
				}));
		BeginBlendMode(BLEND_ADDITIVE);
		DrawTexture(m_Mask, Position.x - m_Mask.width / 2, Position.y - m_Mask.height / 2, Color{214, 65, 96, 50});
		EndBlendMode();
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Torch>::from_json(const json& json) -> Redge::Torch
{
	assert(json["point"].get<bool>());
	return Redge::Torch(Vector2{json["x"].get<float>(), json["y"].get<float>()});
}
