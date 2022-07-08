#pragma once

namespace Tiled
{
	struct Layer;
} // namespace Tiled


namespace Redge
{
	class Entity
	{
	public:
		virtual ~Entity() = default;

		virtual auto Update(Tiled::Layer& layer) -> void = 0;

		virtual auto Render() const -> void = 0;
		virtual auto RenderUI() const -> void = 0;
	};
} // namespace Redge
