#pragma once

#include <cstdint>
#include <filesystem>

#include <raylib.h>

namespace Raylib
{
	class Tileset
	{
	public:
		Tileset(const char* file, uint16_t tileCountX, uint16_t timeCountY);
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
		auto DrawTileScaled(uint16_t x, uint16_t y, Vector2 position, float scale, Color tint = WHITE) const -> void;

		auto DrawTileTo(uint16_t x, uint16_t y, Rectangle destination, Color tint = WHITE) const -> void;

		auto DrawTilePart(uint16_t x, uint16_t y, Vector2 position, Vector2 section, Color tint = WHITE) const -> void;
		auto DrawTilePartScaled(uint16_t x, uint16_t y, Vector2 position, Vector2 section, float scale, Color tint = WHITE) const -> void;

		static auto FromFile(const std::filesystem::path& file) -> Tileset;

	private:
		Texture2D m_Texture{};
		uint16_t m_TileCountX{};
		uint16_t m_TileCountY{};
	};
} // namespace Raylib
