#pragma once

#include "Tiled/Layer.h"
#include "Graphics/Tileset.h"

#include <nlohmann/json.hpp>

namespace Tiled
{
	struct Map
	{
		std::vector<Property> Properties;
		std::map<uint16_t, std::unique_ptr<Layer>> Layers;
		std::map<uint16_t, Redge::Tileset> Tilesets;
		Color BackgroundColor;
		int Width;
		int Height;
		int TileWidth;
		int TileHeight;

		auto Update(Redge::Scene* scene) -> void;
		auto Render() const -> void;
		auto RenderUI() const -> void;

		static auto FromFile(const std::filesystem::path& file) -> Map;
	};
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<Tiled::Map>
{
	static auto from_json(const json& json) -> Tiled::Map;
};