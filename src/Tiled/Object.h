#pragma once

#include "Game/Scene.h"

#include <memory>

#include <nlohmann/json.hpp>

namespace Tiled
{
	class Object
	{
	public:
		Object(Vector2 position);
		virtual ~Object() = default;

		virtual auto Update(Redge::Scene* scene, struct ObjectLayer& layer) -> void{}
		virtual auto LateUpdate(Redge::Scene* scene, struct ObjectLayer& layer) -> void{}

		virtual auto RenderBelow() const -> void{}
		virtual auto Render() const -> void{}
		virtual auto RenderAbove() const -> void{}
		virtual auto RenderUI() const -> void{}

		[[nodiscard]] auto GetPosition() const -> Vector2;

	protected:
		Vector2 Position;
	};
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<std::unique_ptr<Tiled::Object>>
{
	static auto from_json(const json& json) -> std::unique_ptr<Tiled::Object>;
};
