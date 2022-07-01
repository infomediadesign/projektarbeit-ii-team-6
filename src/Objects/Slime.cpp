#include "Objects/Slime.h"
#include "Tiled/Layer.h"

namespace Redge
{
	auto Slime::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
		if (character == nullptr)
		{
			for (const auto& [number, object] : layer.Objects)
			{
				if (auto player = std::dynamic_pointer_cast<Character>(object))
				{
					character = player;
					break;
				}
			}
		}

		s_Previous_Position = s_Current_Position;

		if (character != nullptr)
		{
			if (Vector2Distance(s_Current_Position, character->GetPosition()) < 75)
			{
			s_Current_Position = Vector2Add(
				s_Current_Position, Vector2Scale(
					Vector2Normalize(
						Vector2Subtract(character->GetPosition(), s_Current_Position)),
						s_Speed));
				m_Frametime += GetFrameTime();
			}
		}

		if (m_Frametime >= s_FrameDuration)
		{
			m_Frametime -= s_FrameDuration;
			++m_AnimationFrame %= m_Animation.GetTileCountX();
		}
	}

	auto Slime::LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void
	{
	}

	auto Slime::Render() const -> void
	{
		m_Animation.DrawTile(m_AnimationFrame, 0,
			Vector2Add(s_Current_Position,
				Vector2{
					static_cast<float>(-m_Animation.GetTileWidth()) / 2,
					static_cast<float>(-m_Animation.GetTileHeight()) / 2,
				}));
	}

	auto Slime::RenderUI() const -> void
	{
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Slime>::from_json(const json& json) -> Redge::Slime
{
	assert(json["point"].get<bool>());
	return Redge::Slime(Vector2{json["x"].get<float>(), json["y"].get<float>()});
}
