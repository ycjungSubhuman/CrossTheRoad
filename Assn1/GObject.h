#pragma once
#include "Rect.h"
#include <string>
#include <list>
#include <functional>
#include "mat.h"

class GObject {
protected:
	void setRect(const Rect& rect);
	void onTraverseDraw(mat4 MVMatrix);
	void onTraverseUpdate();
private:
	double z;
	GObject* parent; //pointer to the parent node
	Rect obj; //local boundbox(relative to parent's position)
	Rect hitbox; //collision box(relative to obj)
	double rotx, roty, rotz; //position of rotation center (reletive to obj)
	double rotation_z, rotation_x; //amount of rotation about z and x
	double scale_x, scale_y, scale_z;
	std::string type; //type of this object(for RTTS with convenience)
	std::list<GObject*> children; //list of children
public:
	GObject(const Rect& obj, const Rect& hitbox, std::string type="OBJECT");
	void setPos(double x, double y, double z=0);
	void setRotCenter(double x, double y, double z=0);
	void setRotation(double rotz, double rotx=0);
	void setScale(double x, double y, double z);
	double getZ();
	double getX();
	double getY();
	Rect getobj();
	Rect getgloobj(); //get obj with global location
	Rect gethitbox();
	double getRotation();
	virtual void draw(mat4 MVMatrix)=0;
	virtual void frameAction()=0;
	std::string getType();
	GObject* getChildOfType(std::string type);
	std::list<GObject*>* getChildren();

	static bool isCollide(GObject&, GObject&);
	GObject* addObject(GObject* obj);
	GObject* removeObject(GObject* obj);
	GObject* getParent();

	~GObject();
};