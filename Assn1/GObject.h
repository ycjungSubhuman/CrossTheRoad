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
	int z; //z-index(relative to the parent)
	GObject* parent; //pointer to the parent node
	Rect obj; //local boundbox(relative to parent's position)
	Rect hitbox; //collision box(relative to obj)
	double rotx, roty; //position of rotation center (reletive to obj)
	double rotation; //amount of rotation
	std::string type; //type of this object(for RTTS with convenience)
	std::list<GObject*> children; //list of children
public:
	GObject(const Rect& obj, const Rect& hitbox, std::string type="OBJECT");
	void setPos(double x, double y);
	void setRotCenter(double x, double y);
	void setRotation(double rot);
	int getZ();
	double getX();
	double getY();
	Rect getobj();
	Rect gethitbox();
	virtual void draw(mat4 MVMatrix)=0;
	virtual void frameAction()=0;
	std::string getType();
	GObject* getChildOfType(std::string type);
	std::list<GObject*>* getChildren() const;

	static bool isCollide(GObject&, GObject&);
	GObject* addObject(GObject* obj, int z=0);
	GObject* removeObject(GObject* obj);
	GObject* getParent();

	~GObject();
};