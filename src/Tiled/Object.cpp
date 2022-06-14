#include "Object.h"

#include "Objects/Character.h"

#include <cassert>

struct NullObject final : Tiled::Object
{
	auto Update(Redge::Scene* scene, Tiled::ObjectLayer& layer) -> void override
	{
	}

	auto LateUpdate(Redge::Scene* scene, Tiled::ObjectLayer& layer) -> void override
	{
	}

	auto Render() const -> void override
	{
	}

	auto RenderUI() const -> void override
	{
	}
};

auto nlohmann::adl_serializer<std::unique_ptr<Tiled::Object>>::from_json(const json& json)
	-> std::unique_ptr<Tiled::Object>
{
	// TODO: Create objects from Tiled map data
	const auto name = json["name"].get<std::string>();

	if (name == "charakter")
		return std::make_unique<Redge::Character>(json.get<Redge::Character>());

	// TOOD: assert(!"Unhandled object type");
	return std::make_unique<NullObject>();
}
