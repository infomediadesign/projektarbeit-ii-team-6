#include "Property.h"

auto nlohmann::adl_serializer<Tiled::Property>::from_json(const json& json) -> Tiled::Property
{
	const auto type = json["type"].get<std::string>();

	if (type == "string")
	{
		return Tiled::Property{
			json["name"].get<std::string>(),
			json["value"].get<std::string>(),
		};
	}

	if (type == "int")
	{
		return Tiled::Property{
			json["name"].get<std::string>(),
			json["value"].get<int>(),
		};
	}

	if (type == "float")
	{
		return Tiled::Property{
			json["name"].get<std::string>(),
			json["value"].get<float>(),
		};
	}

	if (type == "bool")
	{
		return Tiled::Property{
			json["name"].get<std::string>(),
			json["value"].get<bool>(),
		};
	}

	if (type == "color")
	{
		return Tiled::Property{
			json["name"].get<std::string>(),
			json["value"].get<Color>(),
		};
	}

	if (type == "file")
	{
		return Tiled::Property{
			json["name"].get<std::string>(),
			json["value"].get<std::filesystem::path>(),
		};
	}

	throw std::runtime_error("Unsupported property type");
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
