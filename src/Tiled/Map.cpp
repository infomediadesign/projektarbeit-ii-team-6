#include "Map.h"

#include <fstream>
#include <cassert>

auto Tiled::Map::FromFile(const std::filesystem::path& file) -> Map
{
	const auto parentPath = file.parent_path();

	std::ifstream fileStream(file);
	assert(fileStream.is_open());

	nlohmann::json json;
	fileStream >> json;

	auto map = json.get<Map>();

	for (const auto& entry : json["tilesets"])
	{
		const auto firstgid = entry["firstgid"].get<uint16_t>();
		const auto tilesetPath = parentPath / entry["source"].get<std::filesystem::path>();
		map.Tilesets.emplace_back(firstgid, Redge::Tileset::FromFile(tilesetPath));
	}

	return map;
}

auto nlohmann::adl_serializer<Tiled::Map>::from_json(const json& json) -> Tiled::Map
{
	return Tiled::Map{
		json["properties"].get<std::vector<Tiled::Property>>(),
		json["layers"].get<std::vector<std::unique_ptr<Tiled::Layer>>>(),
		std::vector<std::pair<uint16_t, Redge::Tileset>>(), // This uses relative paths from the file
		json["backgroundcolor"].get<Color>(),
		json["width"].get<int>(),
		json["height"].get<int>(),
		json["tilewidth"].get<int>(),
		json["tileheight"].get<int>(),
	};
}
