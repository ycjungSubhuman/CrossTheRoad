#pragma once
#include "Rect.h"
#include <string>
#include <list>
#include <functional>

class GObject {
protected:
	void setRect(const Rect& rect);
	void onTrasverseDo(const std::function<void(GObject*)>& fun);
	Rect getGlobalobj();
private:
	int z;
	Rect obj;
	Rect hitbox;
	double rotx, roty;
	double rotation;
	std::string type;
	std::list<GObject*> children;
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

	~GObject();
};