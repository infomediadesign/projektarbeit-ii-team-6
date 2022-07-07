#pragma once

#include "Tiled/Object.h"
#include "Raylib/Tileset.h"

#include <array>

#include <raylib.h>
#include <raymath.h>

namespace Redge
{
	class Torch : public Tiled::Object
	{
	public:
		Torch(Vector2 position) : position(position){};
		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;

	private:
		Vector2 position;
		Raylib::Tileset m_Animation = Raylib::Tileset("assets/Tilesets/objects/torch.png", 6, 1);
		uint16_t m_AnimationFrame = 0;
		static constexpr float s_FrameDuration = 0.2;
		float m_Frametime = 0;
	};
} // namespace Redge

template<>
struct nlohmann::adl_serializer<Redge::Torch>
{
	static auto from_json(const json& json) -> Redge::Torch;
};
