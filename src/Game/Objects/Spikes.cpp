#include "Spikes.h"

#include "raymath.h"

namespace Redge
{
	Spikes::Spikes(Vector2 position) : Tiled::Object(position)
	{
	}

	auto Spikes::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		m_LoopTime += GetFrameTime();
		if (m_LoopTime >= s_LoopDuration)
			m_LoopTime -= s_LoopDuration;

		if (m_LoopTime < s_HiddenDuration)
			m_AnimationFrame = 0;
		else if (m_LoopTime >= s_HiddenDuration + s_TransitionDuration &&
			m_LoopTime <= s_LoopDuration - s_TransitionDuration)
			m_AnimationFrame = 2;
		else
			m_AnimationFrame = 1;
	}

	auto Spikes::RenderBelow() const -> void
	{
		auto offset = Vector2{
			static_cast<float>(-m_Spikes.GetTileWidth()) / 2,
			static_cast<float>(-m_Spikes.GetTileHeight()) / 2,
		};

		m_Spikes.DrawTile(m_AnimationFrame, 0, Vector2Add(Position, offset));
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Spikes>::from_json(const json& json) -> Redge::Spikes
{
	assert(json["point"].get<bool>());

	return Redge::Spikes(Vector2{
		json["x"].get<float>(),
		json["y"].get<float>(),
	});
}
