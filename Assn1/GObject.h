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
	std::function<void(const Rect&,int,int,int)> drawFunc;
	int r, g, b;
public:
	GObject(const Rect& obj, const Rect& hitbox, int z=0, std::string type="OBJECT");
	void setFunc(const std::function<void(const Rect&,int,int,int)>& func);
	void draw();
	std::string getType();
	void setColor(int r, int g, int b);
	static bool isCollide(const GObject&, const GObject&);
};