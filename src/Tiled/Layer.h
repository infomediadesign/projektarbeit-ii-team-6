#pragma once

#include "Scene.h"
#include "Tiled/Chunk.h"
#include "Tiled/Object.h"
#include "Tiled/Property.h"

#include <filesystem>

namespace Tiled
{
	enum class DrawOrder
	{
		TopDown,
		Index,
	};

	struct Layer
	{
		virtual ~Layer() = default;

		virtual auto Update(Redge::Scene* scene) -> void;
		virtual auto Render() const -> void;
		virtual auto RenderUI() const -> void;

		std::string Name;
		std::vector<Property> Properties;
		bool Visible;
		double Opacity;
		Color Tint;
		int X;
		int Y;
		double OffsetX;
		double OffsetY;
	};

	struct TileLayer final : Layer
	{
		std::vector<Chunk> Chunks;
		std::vector<int> Data;
		int StartX;
		int StartY;
		int Width;
		int Height;

		auto Render() const -> void override;
	};

	struct ObjectLayer final : Layer
	{
		DrawOrder DrawOrder;
		std::map<uint16_t, std::unique_ptr<Object>> Objects;

		auto Update(Redge::Scene* scene) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;
	};

	struct ImageLayer final : Layer
	{
		std::filesystem::path Image;
		bool RepeatX;
		bool RepeatY;

		auto Render() const -> void override;
	};

	struct GroupLayer final : Layer
	{
		std::map<uint16_t, std::unique_ptr<Layer>> Layers;

		auto Update(Redge::Scene* scene) -> void override;
		auto Render() const -> void override;
		auto RenderUI() const -> void override;
	};
} // namespace Tiled

template <>
struct nlohmann::adl_serializer<Tiled::DrawOrder>
{
	static auto from_json(const json& json) -> Tiled::DrawOrder;
};

template <>
struct nlohmann::adl_serializer<Tiled::Layer>
{
	static auto from_json(const json& json) -> Tiled::Layer;
};

template <>
struct nlohmann::adl_serializer<Tiled::TileLayer>
{
	static auto from_json(const json& json) -> Tiled::TileLayer;
};

template <>
struct nlohmann::adl_serializer<Tiled::ObjectLayer>
{
	static auto from_json(const json& json) -> Tiled::ObjectLayer;
};

template <>
struct nlohmann::adl_serializer<Tiled::ImageLayer>
{
	static auto from_json(const json& json) -> Tiled::ImageLayer;
};

template <>
struct nlohmann::adl_serializer<Tiled::GroupLayer>
{
	static auto from_json(const json& json) -> Tiled::GroupLayer;
};

template <>
struct nlohmann::adl_serializer<std::unique_ptr<Tiled::Layer>>
{
	static auto from_json(const json& json) -> std::unique_ptr<Tiled::Layer>;
};
