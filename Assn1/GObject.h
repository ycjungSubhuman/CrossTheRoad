#pragma once
#include "Rect.h"
#include <string>
#include <functional>

class GObject {
private:
	int z;
	Rect obj;
	Rect hitbox;
	std::string type;
	int r, g, b;
protected:
	void setRect(const Rect& rect);
public:
	GObject(const Rect& obj, const Rect& hitbox, int z=0, std::string type="OBJECT");
	void setPos(double x, double y);
	int getR();
	int getG();
	int getB();
	int getZ();
	double getX();
	double getY();
	virtual void draw()=0;
	virtual void frameAction()=0;
	std::string getType();
	void setColor(int r, int g, int b);
	static bool isCollide(GObject&, GObject&);

	//for priority queue compare
	int operator<(const GObject& obj);
};