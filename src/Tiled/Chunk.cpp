#include "Chunk.h"

auto nlohmann::adl_serializer<Tiled::Chunk>::from_json(const json& json) -> Tiled::Chunk
{
	return Tiled::Chunk{
		json["data"].get<std::vector<int>>(),
		json["width"].get<int>(),
		json["height"].get<int>(),
		json["x"].get<int>(),
		json["y"].get<int>(),
	};
}
