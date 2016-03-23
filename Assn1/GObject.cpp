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
	Rect a = Rect(o1.getobj().x() + o1.gethitbox().x(), o1.getobj().y() + o1.gethitbox().y(), o1.gethitbox().width(), o1.gethitbox().height());
	Rect b = Rect(o2.getobj().x() + o2.gethitbox().x(), o2.getobj().y() + o2.gethitbox().y(), o2.gethitbox().width(), o2.gethitbox().height());

	if (Rect::isCollide(a, b)) 
		return true;
	else 
		return false;
}
