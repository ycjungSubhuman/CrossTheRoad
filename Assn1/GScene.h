#pragma once
#include "GObject.h"
#include <vector>

class GScene {
private:
	GObject* background;
	std::vector<GObject*> objects;
	int size;
public:
	GScene();
	GObject* getObject(int index);
	GObject* addObject(GObject* obj);
	GObject* removeObject(GObject* obj);
	std::vector<GObject*> getCollisions(GObject* obj);
};
