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
	std::function<void(const Rect& canvas)> drawFunc;
public:
	GObject(const Rect& obj, const Rect& hitbox, std::function<void(const Rect&)> drawFunc, int z=0, std::string type="OBJECT");
	void setFunc(std::function<void(const Rect&)> func);
	void draw();
	std::string getType();
	static bool isCollide(const GObject&, const GObject&);
};