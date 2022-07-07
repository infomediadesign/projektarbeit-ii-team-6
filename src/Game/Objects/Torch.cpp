#include "Torch.h"

namespace Redge
{
	auto Torch::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		m_Frametime += GetFrameTime();
		if (m_Frametime >= s_FrameDuration)
		{
			m_Frametime -= s_FrameDuration;
			++m_AnimationFrame %= m_Animation.GetTileCountX();
		}
	}

	auto Torch::LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
	}

	auto Torch::Render() const -> void
	{
		m_Animation.DrawTile(m_AnimationFrame, 0,
			Vector2Add(position,
				Vector2{
					static_cast<float>(-m_Animation.GetTileWidth()) / 2,
					static_cast<float>(-m_Animation.GetTileHeight()) / 2,
				}));
		BeginBlendMode(BLEND_MULTIPLIED);
		DrawCircleV(position, 30, Color{255, 255, 255, 75});
		EndBlendMode();
	}

	auto Torch::RenderUI() const -> void
	{
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Torch>::from_json(const json& json) -> Redge::Torch
{
	assert(json["point"].get<bool>());
	return Redge::Torch(Vector2{json["x"].get<float>(), json["y"].get<float>()});
}
