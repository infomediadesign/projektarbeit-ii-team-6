#include "Property.h"

auto nlohmann::adl_serializer<Tiled::PropertyMap>::from_json(const json& json) -> Tiled::PropertyMap
{
	Tiled::PropertyMap properties;

	for (const auto& entry : json)
	{
		const auto type = json["type"].get<std::string>();

		if (type == "string")
			properties.emplace(json["name"].get<std::string>(), json["value"].get<std::string>());
		else if (type == "int")
			properties.emplace(json["name"].get<std::string>(), json["value"].get<int>());
		else if (type == "float")
			properties.emplace(json["name"].get<std::string>(), json["value"].get<float>());
		else if (type == "bool")
			properties.emplace(json["name"].get<std::string>(), json["value"].get<bool>());
		else if (type == "color")
			properties.emplace(json["name"].get<std::string>(), json["value"].get<Color>());
		else if (type == "file")
			properties.emplace(json["name"].get<std::string>(), json["value"].get<std::filesystem::path>());
		else
			throw std::runtime_error("Uknown property type");
	}

	return properties;
}

auto nlohmann::adl_serializer<Color>::from_json(const json& json) -> Color
{
	const auto value = json.get<std::string>();

	if (value.length() == 7)
	{
		return Color{
			static_cast<uint8_t>(std::stoul(value.substr(1, 2), nullptr, 16)),
			static_cast<uint8_t>(std::stoul(value.substr(3, 2), nullptr, 16)),
			static_cast<uint8_t>(std::stoul(value.substr(5, 2), nullptr, 16)),
		};
	}
	else
	{
		return Color{
			static_cast<uint8_t>(std::stoul(value.substr(3, 2), nullptr, 16)),
			static_cast<uint8_t>(std::stoul(value.substr(5, 2), nullptr, 16)),
			static_cast<uint8_t>(std::stoul(value.substr(7, 2), nullptr, 16)),
			static_cast<uint8_t>(std::stoul(value.substr(1, 2), nullptr, 16)),
		};
	}
}
