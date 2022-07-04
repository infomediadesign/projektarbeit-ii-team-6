#pragma once

#include "Graphics/Tileset.h"
#include "Objects/Items/Item.h"
#include "Objects/Types/Collidable.h"
#include "Tiled/Object.h"
#include <raymath.h>
#include <raylib.h>
#include <Objects/Character.h>

namespace Redge
{

	class Slime final : public Tiled::Object//, public ICollidable
	{
	public:
		Slime(Vector2 position) : s_Current_Position(position){};
		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;

	private:
		std::shared_ptr<Character> character;
		Vector2 s_Current_Position;
		Vector2 s_Previous_Position;
		float s_Speed = 0.5;
		Tileset m_Animation = Tileset("assets/Entities/slime.png", 24, 24);
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
