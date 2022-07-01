#include "Object.h"

#include "Objects/Character.h"
#include "Objects/Spikes.h"
#include "Objects/Torch.h"
#include "Objects/Slime.h"
#include "Objects/UpgradeStation.h"
#include "Objects/Wall.h"

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

	if (name == "slime")
		return std::make_unique<Redge::Slime>(json.get<Redge::Slime>());

	if (name == "torch")
		return std::make_unique<Redge::Torch>(json.get<Redge::Torch>());

	if (name == "wall_hitbox")
		return std::make_unique<Redge::Wall>(json.get<Redge::Wall>());

	if (name == "upgrade")
		return std::make_unique<Redge::UpgradeStation>(json.get<Redge::UpgradeStation>());

	if (name == "spikes")
		return std::make_unique<Redge::Spikes>(json.get<Redge::Spikes>());

	// TOOD: assert(!"Unhandled object type");
	return std::make_unique<NullObject>();
}
