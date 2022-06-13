#include "Map.h"

#include <fstream>
#include <cassert>

namespace Tiled
{
	auto Map::Update(Redge::Scene* scene) -> void
	{
		for (auto& [_, layer] : Layers)
			layer->Update(scene);
	}

	auto Map::Render() const -> void
	{
		for (auto& [_, layer] : Layers)
			layer->Render();
	}

	auto Map::RenderUI() const -> void
	{
		for (auto& [_, layer] : Layers)
			layer->RenderUI();
	}

	auto Map::FromFile(const std::filesystem::path& file) -> Map
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
			map.Tilesets.emplace(firstgid, Redge::Tileset::FromFile(tilesetPath));
		}

		return map;
	}
} // namespace Tiled

auto nlohmann::adl_serializer<Tiled::Map>::from_json(const json& json) -> Tiled::Map
{
	Tiled::Map returnValue;

	if (const auto properties = json.find("properties"); properties != json.end())
		returnValue.Properties = properties->get<std::vector<Tiled::Property>>();

	for (const auto& entry : json["layers"])
		returnValue.Layers.emplace(entry["id"].get<uint16_t>(), entry.get<std::unique_ptr<Tiled::Layer>>());

	// Tilesets uses relative paths from the file, so they can't be added here

	const auto background = json.find("backgroundcolor");
	returnValue.BackgroundColor = background != json.end() ? background->get<Color>() : Color{};

	const auto width = json.find("width");
	returnValue.Width = width != json.end() ? width->get<int>() : 0;

	const auto height = json.find("height");
	returnValue.Height = height != json.end() ? height->get<int>() : 0;

	const auto tileWidth = json.find("tilewidth");
	returnValue.TileWidth = tileWidth != json.end() ? tileWidth->get<int>() : 0;

	const auto tileHeight = json.find("tileheight");
	returnValue.TileHeight = tileHeight != json.end() ? tileHeight->get<int>() : 0;

	return returnValue;
}
