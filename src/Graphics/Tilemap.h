#pragma once

#include "Tileset.h"

#include <filesystem>
#include <vector>

namespace Tiled
{
	struct Object
	{
		bool Visible;
		std::string Name;
	};

	struct Rectangle : Object
	{
		::Rectangle Value;
	};

	struct Point : Object
	{
		Vector2 Value;
	};

	struct Ellipse : Object
	{
		::Rectangle Value;
	};

	struct Polygon : Object
	{
		std::vector<Vector2> Points;
	};

	struct Layer : Object
	{
		std::vector<uint16_t> Tiles;

		std::vector<Rectangle> Rectangles;
		std::vector<Point> Points;
		std::vector<Ellipse> Ellipses;
		std::vector<Polygon> Polygons;
	};
} // namespace Tiled

namespace Redge
{
	struct Tilemap
	{
		std::vector<Tiled::Layer> Layers;
		std::vector<std::pair<uint16_t, Tileset>> Tilesets;

		int32_t Width;
		int32_t Height;

		int32_t TileWidth;
		int32_t TileHeight;

		Vector2 Spawn;

		auto Draw() const -> void;
		auto DrawScaled(float scale) const -> void;

		auto CheckCollision(Rectangle checkBox) const -> bool;

		static auto FromTiled(std::filesystem::path filePath) -> Tilemap;

	private:
		auto DrawTile(uint16_t index, Vector2 position, float scale) const -> void;
	};
} // namespace Redge
