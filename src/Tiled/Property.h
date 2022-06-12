#pragma once

#include <variant>
#include <string>
#include <filesystem>

#include <raylib.h>

#include <nlohmann/json.hpp>

namespace Tiled
{
	struct Property
	{
		std::string Name;
		std::variant<std::string, int, float, bool, Color, std::filesystem::path/*, TODO: object, class*/> Value;
	};
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<Tiled::Property>
{
	static auto from_json(const json& json) -> Tiled::Property;
};

template <>
struct nlohmann::adl_serializer<Color>
{
	static auto from_json(const json& json) -> Color;
};
