#include "Object.h"

#include "Objects/Character.h"

auto nlohmann::adl_serializer<std::unique_ptr<Tiled::Object>>::from_json(const json& json)
	-> std::unique_ptr<Tiled::Object>
{
	// TODO: Create objects from Tiled map data
	const auto name = json["name"].get<std::string>();

	if (name == "Character")
		return std::make_unique<Redge::Character>(json.get<Redge::Character>());

	throw std::runtime_error("Unhandled object type");
}
