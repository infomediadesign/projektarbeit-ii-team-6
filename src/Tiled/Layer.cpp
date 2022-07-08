#include "Layer.h"

#include "Tiled/Map.h"
#include "Game/Objects/Types/Collidable.h"

namespace Tiled
{
	auto Layer::Update(Redge::Scene* scene) -> void
	{
	}

	auto Layer::Render(const Map& map, Rectangle viewArea) const -> void
	{
	}

	auto Layer::RenderUI() const -> void
	{
	}

	auto TileLayer::Render(const Map& map, Rectangle viewArea) const -> void
	{
		if (!Visible)
			return;

		RenderTiles(map);
		RenderChunks(map, viewArea);
	}

	auto TileLayer::RenderTiles(const Map& map) const -> void
	{
		auto position = Vector2{
			static_cast<float>(OffsetX),
			static_cast<float>(OffsetY),
		};

		auto column = 0;
		for (const auto& index : Data)
		{
			map.DrawTile(index, position);

			position.x += map.TileWidth;
			++column;

			if (column >= Width)
			{
				position.x -= map.TileWidth * column;
				position.y += map.TileHeight;
				column = 0;
			}
		}
	}

	auto TileLayer::RenderChunks(const Map& map, Rectangle viewArea) const -> void
	{
		for (const auto& chunk : Chunks)
		{
			auto position = Vector2{
				static_cast<float>(chunk.X) * map.TileWidth,
				static_cast<float>(chunk.Y) * map.TileHeight,
			};

			auto area = Rectangle{
				position.x,
				position.y,
				static_cast<float>(chunk.Width) * map.TileWidth,
				static_cast<float>(chunk.Height) * map.TileHeight,
			};

			if (!CheckCollisionRecs(viewArea, area))
				continue;

			auto column = 0;
			for (const auto& index : chunk.Data)
			{
				map.DrawTile(index, position);

				position.x += map.TileWidth;
				++column;

				if (column >= chunk.Width)
				{
					position.x -= map.TileWidth * column;
					position.y += map.TileHeight;
					column = 0;
				}
			}
		}
	}

	auto ObjectLayer::Update(Redge::Scene* scene) -> void
	{
		// NOTE: Should the layers update even if not visible?
		if (!Visible)
			return;

		std::vector<std::shared_ptr<Object>> objects;

		for (auto& [_, object] : Objects)
			objects.emplace_back(object);

		for (auto& object : objects)
			object->Update(scene, *this);

		for (auto i = 0; i < objects.size(); ++i)
		{
			auto& object1 = objects[i];

			auto collidable1 = dynamic_cast<Redge::ICollidable*>(object1.get());
			if (collidable1 == nullptr)
				continue;

			for (auto j = i + 1; j < objects.size(); ++j)
			{
				auto& object2 = objects[j];

				auto collidable2 = dynamic_cast<Redge::ICollidable*>(object2.get());
				if (collidable2 == nullptr)
					continue;

				if (!collidable1->CheckCollision(collidable2))
					continue;

				collidable1->OnCollision(*object2);
				collidable2->OnCollision(*object1);
			}
		}

		for (auto& object : objects)
			object->LateUpdate(scene, *this);
	}

	auto ObjectLayer::Render(const Map& map, Rectangle viewArea) const -> void
	{
		if (!Visible)
			return;

		// TODO: DrawOrder is currently ignored
		for (const auto& [_, object] : Objects)
			object->Render();
	}

	auto ObjectLayer::RenderUI() const -> void
	{
		if (!Visible)
			return;

		// TODO: DrawOrder is currently ignored
		for (const auto& [_, object] : Objects)
			object->RenderUI();
	}

	auto ImageLayer::Render(const Map& map, Rectangle viewArea) const -> void
	{
		if (!Visible)
			return;

		// TODO: Render image
	}

	auto GroupLayer::Update(Redge::Scene* scene) -> void
	{
		// NOTE: Should the layers update even if not visible?
		if (!Visible)
			return;

		for (auto& [_, layer] : Layers)
			layer->Update(scene);
	}

	auto GroupLayer::Render(const Map& map, Rectangle viewArea) const -> void
	{
		if (!Visible)
			return;

		for (const auto& [_, layer] : Layers)
			layer->Render(map, viewArea);
	}

	auto GroupLayer::RenderUI() const -> void
	{
		if (!Visible)
			return;

		for (const auto& [_, layer] : Layers)
			layer->RenderUI();
	}
} // namespace Tiled

auto nlohmann::adl_serializer<Tiled::DrawOrder>::from_json(const json& json) -> Tiled::DrawOrder
{
	if (json.get<std::string>() == "topdown")
		return Tiled::DrawOrder::TopDown;

	return Tiled::DrawOrder::Index;
}

auto nlohmann::adl_serializer<Tiled::Layer>::from_json(const json& json) -> Tiled::Layer
{
	Tiled::Layer returnValue;

	const auto name = json.find("name");
	returnValue.Name = name != json.end() ? name->get<std::string>() : "";

	if (const auto properties = json.find("properties"); properties != json.end())
		returnValue.Properties = properties->get<Tiled::PropertyMap>();

	const auto visible = json.find("visible");
	returnValue.Visible = visible != json.end() ? visible->get<bool>() : true;

	const auto opacity = json.find("opacity");
	returnValue.Opacity = opacity != json.end() ? opacity->get<double>() : 1;

	const auto tint = json.find("tintcolor");
	returnValue.Tint = tint != json.end() ? tint->get<Color>() : WHITE;

	const auto posX = json.find("x");
	returnValue.X = posX != json.end() ? posX->get<int>() : 0;

	const auto posY = json.find("y");
	returnValue.Y = posY != json.end() ? posY->get<int>() : 0;

	const auto offsetX = json.find("offsetx");
	returnValue.OffsetX = offsetX != json.end() ? offsetX->get<double>() : 0;

	const auto offsetY = json.find("offsety");
	returnValue.OffsetY = offsetY != json.end() ? offsetY->get<double>() : 0;

	return returnValue;
}

auto nlohmann::adl_serializer<Tiled::TileLayer>::from_json(const json& json) -> Tiled::TileLayer
{
	Tiled::TileLayer returnValue;

	static_cast<Tiled::Layer&>(returnValue) = json.get<Tiled::Layer>();

	if (const auto chunks = json.find("chunks"); chunks != json.end())
		returnValue.Chunks = chunks->get<std::vector<Tiled::Chunk>>();

	if (const auto data = json.find("data"); data != json.end())
		returnValue.Data = data->get<std::vector<int>>();

	const auto startX = json.find("startx");
	returnValue.StartX = startX != json.end() ? startX->get<int>() : 0;

	const auto startY = json.find("starty");
	returnValue.StartY = startY != json.end() ? startY->get<int>() : 0;

	const auto width = json.find("width");
	returnValue.Width = width != json.end() ? width->get<int>() : 0;

	const auto height = json.find("height");
	returnValue.Height = height != json.end() ? height->get<int>() : 0;

	return returnValue;
}

auto nlohmann::adl_serializer<Tiled::ObjectLayer>::from_json(const json& json) -> Tiled::ObjectLayer
{
	Tiled::ObjectLayer returnValue;

	static_cast<Tiled::Layer&>(returnValue) = json.get<Tiled::Layer>();

	const auto order = json.find("draworder");
	returnValue.Order = order != json.end() ? order->get<Tiled::DrawOrder>() : Tiled::DrawOrder::Index;

	if (const auto objects = json.find("objects"); objects != json.end())
	{
		for (const auto& entry : *objects)
			returnValue.Objects.emplace(entry["id"].get<uint16_t>(), entry.get<std::unique_ptr<Tiled::Object>>());
	}

	return returnValue;
}

auto nlohmann::adl_serializer<Tiled::ImageLayer>::from_json(const json& json) -> Tiled::ImageLayer
{
	Tiled::ImageLayer returnValue;

	static_cast<Tiled::Layer&>(returnValue) = json.get<Tiled::Layer>();

	returnValue.Image = json.get<std::filesystem::path>();

	const auto repeatX = json.find("repeatx");
	returnValue.RepeatX = repeatX != json.end() ? repeatX->get<bool>() : false;

	const auto repeatY = json.find("repeaty");
	returnValue.RepeatX = repeatY != json.end() ? repeatY->get<bool>() : false;

	return returnValue;
}

auto nlohmann::adl_serializer<Tiled::GroupLayer>::from_json(const json& json) -> Tiled::GroupLayer
{
	Tiled::GroupLayer returnValue;

	static_cast<Tiled::Layer&>(returnValue) = json.get<Tiled::Layer>();

	if (const auto layers = json.find("objects"); layers != json.end())
	{
		for (const auto& entry : *layers)
			returnValue.Layers.emplace(entry["id"].get<uint16_t>(), entry.get<std::unique_ptr<Tiled::Layer>>());
	}

	return returnValue;
}

auto nlohmann::adl_serializer<std::unique_ptr<Tiled::Layer>>::from_json(const json& json)
	-> std::unique_ptr<Tiled::Layer>
{
	const auto type = json.find("type");
	if (type == json.end())
		throw std::runtime_error("No layer type specified");

	const auto typeStr = type->get<std::string>();

	if (typeStr == "tilelayer")
		return std::make_unique<Tiled::TileLayer>(json.get<Tiled::TileLayer>());

	if (typeStr == "objectgroup")
		return std::make_unique<Tiled::ObjectLayer>(json.get<Tiled::ObjectLayer>());

	if (typeStr == "imagelayer")
		return std::make_unique<Tiled::ImageLayer>(json.get<Tiled::ImageLayer>());

	if (typeStr == "group")
		return std::make_unique<Tiled::GroupLayer>(json.get<Tiled::GroupLayer>());

	throw std::runtime_error("Unknown layer type");
}
