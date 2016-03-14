#pragma once
#include "Rect.h"
#include <string>

class GObject {
private:
	Rect obj;
	Rect hitbox;
	std::string type;
	void (*drawFunc)(Rect& canvas);
public:
	GObject(Rect obj, Rect hitbox, void(*drawFunc)(Rect& canvas));
	void draw();
	Rect getHitbox();
	std::string getType();
	static bool isCollide(const GObject&, const GObject&);
};