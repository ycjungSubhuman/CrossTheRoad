#pragma once
#include "GObject.h"
#include "mat.h"
#include <list>

class GScene : public GObject{
private:
	double cam_x, cam_y;
	double camdest_x, camdest_y;
public:
	void drawScene();
	void updateScene();
	void setCamDest(double x, double y);
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
	std::list<GObject*> getCollisions(GObject* obj);
	std::list<GObject*> getCollisionsOf(GObject* obj, std::string type);
};
