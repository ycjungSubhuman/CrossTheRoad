#pragma once
#include "Rect.h"
#include <string>
#include <list>
#include <functional>
#include "mat.h"

class GObject {
protected:
	void setRect(const Rect& rect);
	void onTraverseDraw(mat4 stack);
	void onTraverseUpdate();
private:
	int z; //z-index
	GObject* parent; //pointer to the parent node
	Rect obj; //local boundbox(relative to parent's position)
	Rect hitbox; //collision box
	double rotx, roty; //position of rotation center (reletive to obj)
	double rotation; //amount of rotation
	std::string type; //type of this object(for RTTS with convenience)
	std::list<GObject*> children; //list of children
public:
	GObject(const Rect& obj, const Rect& hitbox, int z=0, std::string type="OBJECT");
	void setPos(double x, double y);
	int getZ();
	double getX();
	double getY();
	Rect getobj();
	Rect gethitbox();
	virtual void draw()=0;
	virtual void frameAction()=0;
	std::string getType();

	static bool isCollide(GObject&, GObject&);
	GObject* addObject(GObject* obj);
	GObject* removeObject(GObject* obj);
	GObject* getParent();

	~GObject();
};