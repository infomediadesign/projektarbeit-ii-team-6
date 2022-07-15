#include "Game/Objects/Bat.h"
#include "Tiled/Layer.h"

namespace Redge
{
	Bat::Bat(Vector2 position) : Object(position)
	{
	}

	auto Bat::Update(Scene* scene, Tiled::ObjectLayer& layer) -> void
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

		if (character != nullptr)
		{
			if (Vector2Distance(Position, character->GetPosition()) < 75)
			{
				Position = Vector2Add(Position,
					Vector2Scale(Vector2Normalize(Vector2Subtract(character->GetPosition(), Position)),
						s_Speed * GetFrameTime()));
				m_Frametime += GetFrameTime();
			}
		}

		if (m_Frametime >= s_FrameDuration)
		{
			m_Frametime -= s_FrameDuration;
			++m_AnimationFrame %= m_Animation.GetTileCountX();
		}
	}

	auto Bat::Render() const -> void
	{
		m_Animation.DrawTile(m_AnimationFrame, 0,
			Vector2Add(Position,
				Vector2{
					static_cast<float>(-m_Animation.GetTileWidth()) / 2,
					static_cast<float>(-m_Animation.GetTileHeight()) / 2,
				}));
	}
} // namespace Redge

auto nlohmann::adl_serializer<Redge::Bat>::from_json(const json& json) -> Redge::Bat
{
	assert(json["point"].get<bool>());
	return Redge::Bat(Vector2{json["x"].get<float>(), json["y"].get<float>()});
}
