#pragma once

#include <cstdlib>

#include "raelib.h"



namespace Redge;
{
	class mainChar
	{
	public:
		Texture2D tPlayer = Load Texture("");
		Vector2 vMainCharPos = { 100, 100}
		int iMainCharVel = 5;
		enum direction {up, down, left, right, neutral};
		direction direction = neutral;
	private:
	};
}//namespace Redge
