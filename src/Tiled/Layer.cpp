#include "Layer.h"

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
		returnValue.Properties = properties->get<std::vector<Tiled::Property>>();

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

	if (const auto data = json.find("chunks"); data != json.end())
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
	returnValue.DrawOrder = order != json.end() ? order->get<Tiled::DrawOrder>() : Tiled::DrawOrder::Index;

	if (const auto objects = json.find("objects"); objects != json.end())
		returnValue.Objects = objects->get<std::vector<std::unique_ptr<Tiled::Object>>>();

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
		returnValue.Layers = layers->get<std::vector<std::unique_ptr<Tiled::Layer>>>();

	return returnValue;
}

auto nlohmann::adl_serializer<std::unique_ptr<Tiled::Layer>>::from_json(const json& json) -> std::unique_ptr<Tiled::Layer>
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
