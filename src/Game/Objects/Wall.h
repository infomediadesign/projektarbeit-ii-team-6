#pragma once

#include "Game/Objects/Types/Collidable.h"
#include "raylib.h"
#include "Tiled/Object.h"

namespace Redge
{
	class Wall final : public Tiled::Object, public ICollidable
	{
	public:
		explicit Wall(Rectangle area);

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
		Rectangle m_Area;
	};
} // namespace Redge

template <>
struct nlohmann::adl_serializer<Redge::Wall>
{
	static auto from_json(const json& json) -> Redge::Wall;
};
