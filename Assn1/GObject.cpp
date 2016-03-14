#include "GObject.h"
#include "Rect.h"
#include <string>

GObject::GObject(const Rect& obj, const Rect& hitbox, std::function<void(const Rect&)> drawFunc, int z, std::string type) {
	this->obj = obj;
	this->hitbox = hitbox;
	this->type = type;
	this->drawFunc = drawFunc;
}
void GObject::setFunc(std::function<void(const Rect&)> func) {
	this->drawFunc = func;
}
void GObject::draw() {
	this->drawFunc(this->obj);
}
std::string GObject::getType() {
	return this->type;
}
bool GObject::isCollide(const GObject& o1, const GObject& o2) {
	if (Rect::isCollide(o1.hitbox, o2.hitbox)) 
		return true;
	else 
		return false;
}