#pragma once

#include "Graphics/Tileset.h"
#include "Objects/Types/Collidable.h"
#include "Tiled/Object.h"

#include <raylib.h>

namespace Redge
{
	class Spikes final : public Tiled::Object
	{
	public:
		explicit Spikes(Vector2 position);

		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;

	private:
		static constexpr float s_LoopDuration = 5;
		static constexpr float s_HiddenDuration = 2;
		static constexpr float s_TransitionDuration = 0.2;
		float m_LoopTime = 0;

		uint8_t m_AnimationFrame = 0;
		Tileset m_Spikes = Tileset("assets/Tilesets/objects/spikes.png", 3, 1);

		Vector2 m_Position;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Spikes>
{
	static auto from_json(const json& json) -> Redge::Spikes;
};
