#pragma once
#include "GObject.h"
#include "mat.h"
#include <list>

class GScene : public GObject{
private:
	double cam_x, cam_y;
public:
	enum CameraMode { TOP, POV, SHOULDER };
	GScene();
	void drawScene();
	void updateScene();
	void setCameraMode(CameraMode mode);
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
	std::list<GObject*> getCollisionsOf(GObject* obj, std::string type);
	std::list<GObject*> getNonCollisions(GObject* obj);
private:
	CameraMode mode_cam;
};
