#include "Object.h"

auto nlohmann::adl_serializer<std::unique_ptr<Tiled::Object>>::from_json(const json& json) -> std::unique_ptr<Tiled::Object>
{
	// TODO: Create objects from Tiled map data
	throw std::runtime_error("Unhandled object type");
}
