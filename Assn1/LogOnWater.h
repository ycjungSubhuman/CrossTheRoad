#pragma once
#include "CarLikeObject.h"

/* LogOnWater : Logs floating on the water field. */
class LogOnWater : public CarLikeObject {
public:
	enum { LOGWIDTH = 10, LOGHEIGHT=15, GENTIME = 500, SPEED = 1 };
	LogOnWater(int line, GameMap::Linetype linetype);
	virtual void draw(mat4 MVMatrix);
};
