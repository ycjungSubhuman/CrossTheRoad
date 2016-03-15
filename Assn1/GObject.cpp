#include "GObject.h"
#include "Rect.h"
#include <string>

void GObject::setRect(const Rect& rect) {
	this->obj = rect;
}
GObject::GObject(const Rect& obj, const Rect& hitbox, int z, std::string type) {
	this->obj = obj;
	this->hitbox = hitbox;
	this->type = type;
	this->drawFunc = [](const Rect&,int,int,int)->void {};
}
void GObject::setFunc(const std::function<void(const Rect&,int,int,int)>& func) {
	this->drawFunc = func;
}
void GObject::draw() {
	this->drawFunc(obj, r, g, b);
}
std::string GObject::getType() {
	return this->type;
}
void GObject::setColor(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}
bool GObject::isCollide(const GObject& o1, const GObject& o2) {
	if (Rect::isCollide(o1.hitbox, o2.hitbox)) 
		return true;
	else 
		return false;
}