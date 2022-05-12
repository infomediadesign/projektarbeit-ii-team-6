#pragma once

#include <cstdint>
#include <filesystem>

#include <raylib.h>

namespace Redge
{
	class Tileset
	{
	public:
		Tileset(const char* file, uint16_t tileWidth, uint16_t tileHeight);
		~Tileset();

		Tileset(const Tileset&) = delete;
		auto operator=(const Tileset&) -> Tileset& = delete;

		Tileset(Tileset&& other) noexcept;
		auto operator=(Tileset&& other) noexcept -> Tileset&;

		[[nodiscard]] auto GetTileWidth() const -> uint16_t;
		[[nodiscard]] auto GetTileHeight() const -> uint16_t;

		[[nodiscard]] auto GetTileCountX() const -> uint16_t;
		[[nodiscard]] auto GetTileCountY() const -> uint16_t;

		auto DrawTile(uint16_t x, uint16_t y, Vector2 position, Color tint = WHITE) const -> void;
		auto DrawTileScaled(uint16_t x, uint16_t y, Vector2 position, float scale , Color tint = WHITE) const -> void;

		static auto FromTiled(std::filesystem::path filePath) -> Tileset;

	private:
		Texture2D m_Texture{};
		uint16_t m_TileWidth{};
		uint16_t m_TileHeight{};
	};
} // namespace Redge
