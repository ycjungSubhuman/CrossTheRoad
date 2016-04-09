#include "LogOnWater.h"

LogOnWater::LogOnWater(int line, GameMap::Linetype linetype)
	:CarLikeObject(line, linetype, LOGWIDTH, LOGHEIGHT, "LOG") {
	setDisY(SPEED);
}
void LogOnWater::draw(mat4 MVMatrix) {
	/* -------------------------- */
	/* implement log drawing here */
	/* -------------------------- */
}