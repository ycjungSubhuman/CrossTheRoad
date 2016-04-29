#include "Car.h"
#include <vector>
#include "ModelManager.h"

extern ModelManager* modelManager;

Car::Car(int line, GameMap::Linetype linetype)
:CarLikeObject(line, linetype, CARWIDTH, CARHEIGHT, "CAR") {
	setDisY((double)SPEED/2);
	std::vector<std::string> namelist = { "police_car", "Taxi", "truck_blue" };
	int ind = rand() % 3;
	if (ind == 0) setColor(23, 23, 145);
	else if (ind == 1) setColor(145, 145, 23);
	else setColor(77, 77, 145);
	
	vec3 pos_glo = modelManager->getGlobalPos(namelist[ind]);
	setPos(getX() + pos_glo.x, getY() + pos_glo.y, getZ() + pos_glo.z);
	setModel(modelManager->getModel(namelist[ind]));
}
