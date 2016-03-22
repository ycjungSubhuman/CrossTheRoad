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
int GObject::getR() {
	return r;
}
int GObject::getG() {
	return g;
}
int GObject::getB() {
	return b;
}
int GObject::getZ() {
	return z;
}
std::string GObject::getType() {
	return this->type;
}
void GObject::setColor(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}
bool GObject::isCollide(GObject& o1, GObject& o2) {
	if (Rect::isCollide(o1.hitbox, o2.hitbox)) 
		return true;
	else 
		return false;
}
