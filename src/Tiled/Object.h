#pragma once

#include <memory>

#include <nlohmann/json.hpp>

namespace Tiled
{
	struct Object
	{
	};
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<std::unique_ptr<Tiled::Object>>
{
	static auto from_json(const json& json) -> std::unique_ptr<Tiled::Object>;
};
