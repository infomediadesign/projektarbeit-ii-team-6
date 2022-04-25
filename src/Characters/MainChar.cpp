
#include <cstdlib>

#include "raylib.h"
#include "MainChar.h"

namespace Redge
{
	mainChar mainChar1;
	int movement()
	{
		if (IsKeyDown(KEY_D))
		{
			mainChar1.vMainCharPos.x = mainChar1.vMainCharPos.x + iMainCharVel;
			mainChar::direction = right;
		}

		else if (IsKeyDown(KEY_A))
		{
			mainChar1.vMainCharPos.x = mainChar1.vMainCharPos.x - iMainCharVel;
			mainChar::direction = left;
		}
		else if (IsKeyDown(KEY_W))
		{
			mainChar1.vMainCharPos.y = mainChar1.vMainCharPos.y - iMainCharVel;
			mainChar::direction = up;
		}

		else if (IsKeyDown(KEY_S))
		{
			mainChar1.vMainCharPos.y = mainChar1.vMainCharPos.y + iMainCharVel;
			mainChar::direction = down;
		}
		else mainChar::direction = neutral;
	}

}//namespace Redge
