#include "Tilemap.h"

#include <cassert>
#include <fstream>

#include <nlohmann/json.hpp>

namespace Redge
{
	auto Tilemap::Draw() const -> void
	{
		DrawScaled(1);
	}

	auto Tilemap::DrawScaled(float scale) const -> void
	{
		for (const auto& layer : Layers)
		{
			if (!layer.Visible)
				continue;

			Vector2 position{};
			auto xIndex = 0;
			for (const auto index : layer.Data)
			{
				DrawTile(index, position, scale);
				position.x += static_cast<float>(TileWidth) * scale;

				++xIndex;

				if (xIndex >= layer.Width)
				{
					position.y += static_cast<float>(TileHeight) * scale;
					position.x = 0;
					xIndex = 0;
				}
			}
		}
	}

	auto Tilemap::FromTiled(std::filesystem::path filePath) -> Tilemap
	{
		std::ifstream fileStream(filePath);
		assert(fileStream.is_open());

		nlohmann::json json;
		fileStream >> json;

		Tilemap map{};

		map.Width = json["width"].get<int32_t>();
		map.Height = json["height"].get<int32_t>();

		map.TileWidth = json["tilewidth"].get<int32_t>();
		map.TileHeight = json["tileheight"].get<int32_t>();

		for (const auto& element : json["layers"])
		{
			auto& layer = map.Layers.emplace_back();
			layer.Data = element["data"].get<std::vector<uint16_t>>();
			layer.Width = element["width"].get<int32_t>();
			layer.Height = element["height"].get<int32_t>();
			layer.Visible = element["visible"].get<bool>();
		}

		const auto parentPath = filePath.parent_path();
		for (const auto& element : json["tilesets"])
			map.Tilesets.push_back({element["firstgid"].get<uint16_t>(),
			                        Tileset::FromTiled((parentPath / element["source"]).string().c_str())
			});

		return map;
	}

	auto Tilemap::DrawTile(uint16_t index, Vector2 position, float scale) const -> void
	{
		for (const auto& [firstIndex, tileset] : Tilesets)
		{
			if (index < firstIndex)
				continue;

			index -= firstIndex;
			const auto x = index % tileset.GetTileCountX();
			const auto y = index / tileset.GetTileCountX();

			tileset.DrawTile(x, y, position);
		}
	}
} // namespace Redge
