#pragma once

#include "Scene.h"

#include <memory>

#include <nlohmann/json.hpp>

namespace Tiled
{
	struct Object
	{
		virtual ~Object() = default;

		virtual auto Update(Redge::Scene* scene, struct ObjectLayer& layer) -> void = 0;
		virtual auto Render() const -> void = 0;
		virtual auto RenderUI() const -> void = 0;
	};
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<std::unique_ptr<Tiled::Object>>
{
	static auto from_json(const json& json) -> std::unique_ptr<Tiled::Object>;
};
