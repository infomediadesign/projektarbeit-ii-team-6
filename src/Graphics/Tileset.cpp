#include "Tileset.h"

#include <cassert>
#include <stdexcept>

namespace Redge
{
	Tileset::Tileset(const char* file, const uint16_t tileWidth, const uint16_t tileHeight) :
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

	auto Tileset::DrawTile(const uint16_t x, const uint16_t y, const Vector2 position, const Color tint) const -> void
	{
		// Check passed parameters are within bounds
		assert(x < GetTileCountX());
		assert(y < GetTileCountY());

		Rectangle rect;
		rect.x = static_cast<float>(GetTileWidth() * x);
		rect.y = static_cast<float>(GetTileHeight() * y);
		rect.width = static_cast<float>(GetTileWidth());
		rect.height = static_cast<float>(GetTileHeight());
		DrawTextureRec(m_Texture, rect, position, tint);
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
} // namespace Redge
