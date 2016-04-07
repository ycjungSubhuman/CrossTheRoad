#pragma once
#include "GObject.h"
#include <list>

class GScene : public GObject{
public:
	void drawScene();
	void updateScene();
	void clearOutOfRect(Rect& rect);
	std::list<GObject*> getCollisions(GObject* obj);
	std::list<GObject*> getCollisionsOf(GObject* obj, std::string type);
};
