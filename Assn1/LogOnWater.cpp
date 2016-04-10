#include "LogOnWater.h"

LogOnWater::LogOnWater(int line, GameMap::Linetype linetype)
	:CarLikeObject(line, linetype, LOGWIDTH, LOGHEIGHT, "LOG") {
	setDisY(SPEED);
	setColor(132, 92, 0);
}