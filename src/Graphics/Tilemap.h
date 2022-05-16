#pragma once

#include <filesystem>

#include "Tileset.h"

namespace Redge
{
	struct Layer
	{
		std::vector<uint16_t> Data;
		std::vector<Rectangle> CollisionBoxes;

		int32_t Width;
		int32_t Height;
		
		bool Visible;
	};  

	struct Tilemap
	{
		std::vector<Layer> Layers;
		std::vector<std::pair<uint16_t, Tileset>> Tilesets;

		int32_t Width;
		int32_t Height;

		int32_t TileWidth;
		int32_t TileHeight;

		auto Draw() const -> void;
		auto DrawScaled(float scale) const -> void;
		auto CheckCollision(Rectangle checkBox) const -> bool;

		static auto FromTiled(std::filesystem::path filePath) -> Tilemap;

	private:
		auto DrawTile(uint16_t index, Vector2 position, float scale) const -> void;
	};
} // namespace Redge
