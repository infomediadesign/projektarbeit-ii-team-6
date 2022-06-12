#include "Tileset.h"

#include <cassert>
#include <fstream>

#include <nlohmann/json.hpp>

namespace Redge
{
	Tileset::Tileset(const char* file, uint16_t tileWidth, uint16_t tileHeight) :
		m_Texture(LoadTexture(file)), m_TileWidth(tileWidth), m_TileHeight(tileHeight)
	{
		// Texture size is a multiple of a tile width
		assert(m_Texture.width % m_TileWidth == 0);
		// Texture size is a multiple of a tile height
		assert(m_Texture.height % m_TileHeight == 0);
	}

	Tileset::~Tileset()
	{
		UnloadTexture(m_Texture);
		m_Texture = Texture2D{};
		m_TileWidth = 0;
		m_TileHeight = 0;
	}

	Tileset::Tileset(Tileset&& other) noexcept :
		m_Texture(other.m_Texture), m_TileWidth(other.m_TileWidth), m_TileHeight(other.m_TileHeight)
	{
		other.m_Texture = Texture2D{};
		other.m_TileWidth = 0;
		other.m_TileHeight = 0;
	}

	auto Tileset::operator=(Tileset&& other) noexcept -> Tileset&
	{
		if (this == &other)
			return *this;

		UnloadTexture(m_Texture);

		m_Texture = other.m_Texture;
		m_TileWidth = other.m_TileWidth;
		m_TileHeight = other.m_TileHeight;

		other.m_Texture = Texture2D{};
		other.m_TileWidth = 0;
		other.m_TileHeight = 0;

		return *this;
	}

	auto Tileset::GetTileWidth() const -> uint16_t
	{
		return m_TileWidth;
	}

	auto Tileset::GetTileHeight() const -> uint16_t
	{
		return m_TileHeight;
	}

	auto Tileset::GetTileCountX() const -> uint16_t
	{
		return m_Texture.width / m_TileWidth;
	}

	auto Tileset::GetTileCountY() const -> uint16_t
	{
		return m_Texture.height / m_TileHeight;
	}

	auto Tileset::DrawTile(uint16_t x, uint16_t y, Vector2 position, Color tint) const -> void
	{
		DrawTileScaled(x, y, position, 1, tint);
	}

	auto Tileset::DrawTileScaled(uint16_t x, uint16_t y, Vector2 position, float scale, Color tint) const -> void
	{
		// Check passed parameters are within bounds
		assert(x < GetTileCountX());
		assert(y < GetTileCountY());

		Rectangle rect;
		rect.x = static_cast<float>(GetTileWidth() * x);
		rect.y = static_cast<float>(GetTileHeight() * y);
		rect.width = static_cast<float>(GetTileWidth());
		rect.height = static_cast<float>(GetTileHeight());

		Rectangle dest;
		dest.x = position.x;
		dest.y = position.y;
		dest.width = rect.width * scale;
		dest.height = rect.height * scale;
		DrawTexturePro(m_Texture, rect, dest, Vector2{}, 0, tint);
	}

	auto Tileset::DrawTilePart(uint16_t x, uint16_t y, Vector2 position, Vector2 section, Color tint) const -> void
	{
		DrawTilePartScaled(x, y, position, section, 1, tint);
	}

	auto Tileset::DrawTilePartScaled(uint16_t x, uint16_t y, Vector2 position, Vector2 section, float scale, Color tint) const -> void
	{
		// Check passed parameters are within bounds
		assert(x < GetTileCountX());
		assert(y < GetTileCountY());
		assert(section.x <= GetTileWidth());
		assert(section.y <= GetTileHeight());

		Rectangle rect;
		rect.x = static_cast<float>(GetTileWidth() * x);
		rect.y = static_cast<float>(GetTileHeight() * y);
		rect.width = section.x;
		rect.height = section.y;

		Rectangle dest;
		dest.x = position.x;
		dest.y = position.y;
		dest.width = rect.width * scale;
		dest.height = rect.height * scale;
		DrawTexturePro(m_Texture, rect, dest, Vector2{}, 0, tint);
	}

	auto Tileset::FromTiled(std::filesystem::path filePath) -> Tileset
	{
		std::ifstream fileStream(filePath);
		assert(fileStream.is_open());

		nlohmann::json json;
		fileStream >> json;

		const auto imagePath = filePath.parent_path()  / json["image"].get<std::string>();
		const auto tileWidth = json["tilewidth"].get<uint16_t>();
		const auto tileHeight = json["tileheight"].get<uint16_t>();

		return Tileset{imagePath.string().c_str(), tileWidth, tileHeight};
	}
} // namespace Redge
