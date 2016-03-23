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
	this->z = z;
}
void GObject::setPos(double x, double y) {
	this->obj.setX(x);
	this->obj.setY(y);
}
double GObject::getX() {
	return this->obj.left();
}
double GObject::getY() {
	return this->obj.top();
}
Rect GObject::getobj() {
	return this->obj;
}
Rect GObject::gethitbox() {
	return this->hitbox;
}
int GObject::getZ() {
	return z;
}
std::string GObject::getType() {
	return this->type;
}
bool GObject::isCollide(GObject& o1, GObject& o2) {
	if (Rect::isCollide(o1.hitbox, o2.hitbox)) 
		return true;
	else 
		return false;
}
