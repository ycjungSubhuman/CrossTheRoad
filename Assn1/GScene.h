#pragma once
#include "GObject.h"
#include "mat.h"
#include <list>

class GScene : public GObject{
private:
	double cam_x, cam_y;
public:
	GScene();
	void drawScene();
	void updateScene();
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
	std::list<GObject*> getCollisions(GObject* obj);
	std::list<GObject*> getCollisionsOf(GObject* obj, std::string type);
};
