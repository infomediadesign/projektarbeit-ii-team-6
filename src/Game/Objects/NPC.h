#pragma once

#include "Raylib/Tileset.h"
#include "Tiled/Object.h"

namespace Redge
{
	class NPC : public Tiled::Object
	{
	public:
		NPC(Vector2 position, const char* file, float frameDuration);

		auto Update(Redge::Scene *scene, Tiled::ObjectLayer &layer) -> void override;
		auto Render() const -> void override;

	private:
		Raylib::Tileset m_Animations;
		uint16_t m_AnimationFrame = 0;
		float m_FrameDuration = 0;
		float m_Frametime = 0;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::NPC>
{
	static auto from_json(const json& json) -> Redge::NPC;
};
