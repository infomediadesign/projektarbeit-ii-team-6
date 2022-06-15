#pragma once

#include "Graphics/Tileset.h"
#include "Objects/Types/Collidable.h"
#include "Tiled/Object.h"

#include <raylib.h>

namespace Redge
{
	class UpgradeStation final : public Tiled::Object, public ICollidable
	{
	public:
		explicit UpgradeStation(Vector2 position);

		auto Update(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto LateUpdate(Scene* scene, Tiled::ObjectLayer& layer) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;

		auto OnCollision(Tiled::Object& other) -> void override;
		auto CheckCollision(ICollidable* other) const -> bool override;

		auto IsColliding(const Rectangle& rect) const -> bool override;
		auto IsColliding(const Vector2& center, float radius) const -> bool override;
		auto IsColliding(const Vector2& point) const -> bool override;

	private:
		auto GetHitBox() const -> Rectangle;

		Vector2 m_Position;

		static constexpr float s_FrameDuration = 0.2;
		float m_FrameTime = 0;

		Tileset m_Column = Tileset("assets/Tilesets/objects/upgradeStand.png", 16, 16);
		Tileset m_Ghosts = Tileset("assets/Tilesets/objects/upgradeGhosts.png", 16, 16);
		uint8_t m_AnimationFrame = 0;
		uint8_t m_AnimationColor;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::UpgradeStation>
{
	static auto from_json(const json& json) -> Redge::UpgradeStation;
};
