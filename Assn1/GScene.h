#pragma once
#include "GObject.h"
#include <vector>

class GScene {
private:
	std::vector<GObject*> objects;
public:
	void drawAll();
	GObject* addObject(GObject* obj);
	GObject* removeObject(GObject* obj);
	std::vector<GObject*> getCollisions(GObject* obj); //get all colliding GObjects of obj
	std::vector<GObject*> getCollisionsOf(GObject* obj, std::string type); //get all colliding GObjects of obj with type "type"
};
