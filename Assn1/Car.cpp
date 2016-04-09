#include "Car.h"

Car::Car(int line, GameMap::Linetype linetype)
:CarLikeObject(line, linetype, CARWIDTH, CARHEIGHT, "CAR") {
	setDisY(SPEED);
}
void Car::draw(mat4 MVMatrix) {
	/* -------------------------- */
	/* implement car drawing here */
	/* -------------------------- */
}