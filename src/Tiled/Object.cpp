#include "Object.h"

#include "Game/Objects/Character.h"
#include "Game/Objects/Mud.h"
#include "Game/Objects/Enemies/Bat.h"
#include "Game/Objects/Enemies/Cultist.h"
#include "Game/Objects/Enemies/Slime.h"
#include "Game/Objects/Spikes.h"
#include "Game/Objects/Torch.h"
#include "Game/Objects/UpgradeStation.h"
#include "Game/Objects/Wall.h"

#include <cassert>

namespace Tiled
{
	Object::Object(Vector2 position) : Position(position)
	{
	}

	auto Object::GetPosition() const -> Vector2
	{
		return Position;
	}
} // namespace Tiled

struct NullObject final : Tiled::Object
{
	NullObject() : Tiled::Object({})
	{
	}

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

auto nlohmann::adl_serializer<std::shared_ptr<Tiled::Object>>::from_json(const json& json)
	-> std::shared_ptr<Tiled::Object>
{
	// TODO: Create objects from Tiled map data
	const auto name = json["name"].get<std::string>();

	if (name == "character")
		return json.get<std::shared_ptr<Redge::Character>>();

	if (name == "slime")
		return std::make_unique<Redge::Slime>(json.get<Redge::Slime>());

	if (name == "cultist")
		return std::make_unique<Redge::Cultist>(json.get<Redge::Cultist>());

	if (name == "bat")
		return std::make_unique<Redge::Bat>(json.get<Redge::Bat>());

	if (name == "torch")
		return std::make_unique<Redge::Torch>(json.get<Redge::Torch>());

	if (name == "wall_hitbox")
		return std::make_unique<Redge::Wall>(json.get<Redge::Wall>());

	if (name == "mudFloor")
		return std::make_unique<Redge::Mud>(json.get<Redge::Mud>());

	if (name == "upgrade")
		return std::make_unique<Redge::UpgradeStation>(json.get<Redge::UpgradeStation>());

	if (name == "spikes")
		return std::make_unique<Redge::Spikes>(json.get<Redge::Spikes>());

	// TOOD: assert(!"Unhandled object type");
	return std::make_unique<NullObject>();
}
