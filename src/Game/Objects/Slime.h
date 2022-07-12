#pragma once

#include "Game/Objects/Character.h"
#include "Raylib/Tileset.h"
#include "Tiled/Object.h"

#include <raylib.h>
#include <raymath.h>

namespace Redge
{

	class Slime final : public Tiled::Object
	{
	public:
		Slime(Vector2 position);
		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;

	private:
		std::shared_ptr<Character> character;
		float s_Speed = 60;
		Raylib::Tileset m_Animation = Raylib::Tileset("assets/Entities/slime.png", 8, 1);
		uint16_t m_AnimationFrame = 0;
		static constexpr float s_FrameDuration = 0.15;
		float m_Frametime = 0;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Slime>
{
	static auto from_json(const json& json) -> Redge::Slime;
};
