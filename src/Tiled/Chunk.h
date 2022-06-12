#pragma once

#include <vector>

#include <nlohmann/json.hpp>

namespace Tiled
{
	struct Chunk
	{
		std::vector<int> Data;
		int Width;
		int Height;
		int X;
		int Y;
	};
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<Tiled::Chunk>
{
	static auto from_json(const json& json) -> Tiled::Chunk;
};
