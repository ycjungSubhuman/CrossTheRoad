#include "Car.h"
#include "Background.h"

Car::Car(int line, Background::Linetype linetype, int z) : GObject(Rect(0,0,0,0), Rect(0,0,CARWIDTH,CARHEIGHT), z, "CAR")
{
	dis_y = 0.01;
	setRect(Rect)
}
