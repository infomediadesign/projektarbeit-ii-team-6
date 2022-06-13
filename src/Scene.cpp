#include "Scene.h"

namespace Redge
{
	Scene::Scene(Game* host) : Host(host)
	{
		Camera.offset.x = static_cast<float>(GetScreenWidth()) / 2;
		Camera.offset.y = static_cast<float>(GetScreenHeight()) / 2;
		Camera.zoom = 1;
	}
} // namespace Redge
