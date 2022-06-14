#pragma once

#include <filesystem>
#include <string>
#include <variant>

#include <nlohmann/json.hpp>
#include <raylib.h>


namespace Tiled
{
	using PropertyMap = std::unordered_map<std::string,
		std::variant<std::string, int, float, bool, Color, std::filesystem::path /*, TODO: object, class*/>>;
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<Tiled::PropertyMap>
{
	static auto from_json(const json& json) -> Tiled::PropertyMap;
};

template <>
struct nlohmann::adl_serializer<Color>
{
	static auto from_json(const json& json) -> Color;
};
