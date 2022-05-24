#include "Tilemap.h"

#include "Entities/Character.h"

#include <cassert>
#include <fstream>

#include <nlohmann/json.hpp>

namespace Redge
{
	auto Tilemap::Update(Camera2D& camera) -> void
	{
		for (auto& layer : Layers)
		{
			// NOTE: Possibly update entities even when not visible?
			if (!layer.Visible)
				continue;

			for (auto& entity : layer.Entities)
			{
				entity->Update(layer);
				if (auto character = dynamic_cast<Character*>(entity.get()))
					character->SetCameraTarget(camera);
			}
		}
	}

	auto Tilemap::Render() const -> void
	{
		for (const auto& layer : Layers)
		{
			if (!layer.Visible)
				continue;

			Vector2 position{};
			for (const auto index : layer.Tiles)
			{
				DrawTile(index, position, 1);
				position.x += static_cast<float>(TileWidth);

				if (position.x >= Width * TileWidth)
				{
					position.y += static_cast<float>(TileHeight);
					position.x = 0;
				}
			}

			for (const auto& entity : layer.Entities)
				entity->Render();
		}
	}

	auto Tilemap::RenderUI() const -> void
	{
		for (const auto& layer : Layers)
		{
			if (!layer.Visible)
				continue;

			for (const auto& entity : layer.Entities)
				entity->RenderUI();
		}
	}

	auto Tilemap::CheckCollision(Rectangle checkBox) const -> bool
	{
		for (const auto& layer : Layers)
		{
			for (const auto& box : layer.Rectangles)
			{
				if (box.Visible && CheckCollisionRecs(box.Value, checkBox))
					return true;
			}
		}

		return false;
	}

	static auto ConfigureObjectFromTiled(const nlohmann::json& json, Tiled::Object& object) -> void
	{
		object.Visible = true;
		if (auto visible = json.find("visible"); visible != json.end())
			object.Visible = visible->get<bool>();

		if (auto name = json.find("name"); name != json.end())
			object.Name = name->get<std::string>();
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

			auto type = element.find("type");
			assert(type != element.end());
			auto typeStr = type->get<std::string>();

			layer.Visible = true;
			if (auto visible = element.find("visible"); visible != element.end())
				layer.Visible = visible->get<bool>();

			if (typeStr == "tilelayer")
			{
				if (auto data = element.find("data"); data != element.end())
					layer.Tiles = data->get<std::vector<uint16_t>>();
			}
			else if (typeStr == "objectgroup")
			{
				auto objects = element.find("objects");
				if (objects == element.end())
					continue;

				for (const auto& object : *objects)
				{
					if (object.find("ellipse") != object.end())
					{
						auto& ellipse = layer.Ellipses.emplace_back();
						ConfigureObjectFromTiled(object, ellipse);

						ellipse.Value.x = object["x"].get<float>();
						ellipse.Value.y = object["y"].get<float>();
						ellipse.Value.width = object["width"].get<float>();
						ellipse.Value.height = object["height"].get<float>();
					}
					else if (object.find("polygon") != object.end())
					{
						auto& polygon = layer.Polygons.emplace_back();
						ConfigureObjectFromTiled(object, polygon);

						for (const auto& poly : object["polygon"])
						{
							auto& point = polygon.Points.emplace_back();
							point.x = poly["x"].get<float>();
							point.y = poly["y"].get<float>();
						}
					}
					else if (object.find("point") != object.end())
					{
						auto& point = layer.Points.emplace_back();
						ConfigureObjectFromTiled(object, point);

						point.Value.x = object["x"].get<float>();
						point.Value.y = object["y"].get<float>();

						if (point.Name == "Character")
							layer.Entities.push_back(std::make_unique<Character>(point.Value));
					}
					else
					{
						auto& rectangle = layer.Rectangles.emplace_back();
						ConfigureObjectFromTiled(object, rectangle);

						rectangle.Value.x = object["x"].get<float>();
						rectangle.Value.y = object["y"].get<float>();
						rectangle.Value.width = object["width"].get<float>();
						rectangle.Value.height = object["height"].get<float>();
					}
				}
			}
		}

		const auto parentPath = filePath.parent_path();
		for (const auto& element : json["tilesets"])
			map.Tilesets.push_back({element["firstgid"].get<uint16_t>(),
				Tileset::FromTiled((parentPath / element["source"]).string().c_str())});

		return map;
	}

	auto Tilemap::DrawTile(uint16_t index, Vector2 position, float scale) const -> void
	{
		if (index <= 0)
			return;

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
