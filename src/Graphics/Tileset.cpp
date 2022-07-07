#include "Tileset.h"

#include <cassert>
#include <fstream>

#include <nlohmann/json.hpp>

namespace Redge
{
	Tileset::Tileset(const char* file, uint16_t tileCountX, uint16_t timeCountY) :
		m_Texture(LoadTexture(file)), m_TileCountX(tileCountX), m_TileCountY(timeCountY)
	{
		// Texture size is a multiple of a tile width
		assert(m_Texture.width % GetTileWidth() == 0);
		// Texture size is a multiple of a tile height
		assert(m_Texture.height % GetTileHeight() == 0);
	}

	Tileset::~Tileset()
	{
		UnloadTexture(m_Texture);
		m_Texture = Texture2D{};
		m_TileCountX = 0;
		m_TileCountY = 0;
	}

	Tileset::Tileset(Tileset&& other) noexcept :
		m_Texture(other.m_Texture), m_TileCountX(other.m_TileCountX), m_TileCountY(other.m_TileCountY)
	{
		other.m_Texture = Texture2D{};
		other.m_TileCountX = 0;
		other.m_TileCountY = 0;
	}

	auto Tileset::operator=(Tileset&& other) noexcept -> Tileset&
	{
		if (this == &other)
			return *this;

		UnloadTexture(m_Texture);

		m_Texture = other.m_Texture;
		m_TileCountX = other.m_TileCountX;
		m_TileCountY = other.m_TileCountY;

		other.m_Texture = Texture2D{};
		other.m_TileCountX = 0;
		other.m_TileCountY = 0;

		return *this;
	}

	auto Tileset::GetTileWidth() const -> uint16_t
	{
		return m_Texture.width / GetTileCountX();
	}

	auto Tileset::GetTileHeight() const -> uint16_t
	{
		return m_Texture.height / GetTileCountY();
	}

	auto Tileset::GetTileCountX() const -> uint16_t
	{
		return m_TileCountX;
	}

	auto Tileset::GetTileCountY() const -> uint16_t
	{
		return m_TileCountY;
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

	auto Tileset::FromFile(const std::filesystem::path& file) -> Tileset
	{
		std::ifstream fileStream(file);
		assert(fileStream.is_open());

		nlohmann::json json;
		fileStream >> json;

		const auto imagePath = file.parent_path()  / json["image"].get<std::string>();
		const auto columns = json["columns"].get<uint16_t>();
		const auto rows = json["tilecount"].get<uint16_t>() / columns;

		return Tileset(imagePath.string().c_str(), columns, rows);
	}
} // namespace Redge
