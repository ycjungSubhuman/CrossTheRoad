#include "GObject.h"
#include "Rect.h"
#include <string>

void GObject::setRect(const Rect& rect) {
	/* sets the obj boundbox */
	this->obj = rect;
}
void GObject::onTrasverseDo(const std::function<void(GObject*)>& fun) {
	/* for all the child nodes, call fun */
	for (std::list<GObject*>::iterator it = children.begin(); it != children.end(); it++) {
		fun(*it);
	}
}
Rect GObject::getGlobalobj() {
	/* get global bounding box */
	return gloobj;
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
GObject* GObject::addObject(GObject* obj) {
	/* adds a node to the child of this node
	keeping the order of z-index left to right */

	bool isAdded = false;
	for (std::list<GObject*>::iterator i = children.begin(); i != children.end(); i++) {
		if (obj->getZ() < (*i)->getZ()) {
			isAdded = true;
			children.insert(i, obj);
			break;
		}
	}
	if (!isAdded) {
		//the end of this list
		children.push_back(obj);
	}
	return obj;
}
GObject* GObject::removeObject(GObject* obj) {
	/* remove specified GObject from the root of Scene Graph */
	delete obj;
	children.erase(std::find(children.begin(), children.end(), obj));
	return obj;
}

GObject::~GObject() {
	//delete all the children.
	if (children.empty()) { //Leaf Node
		//Nothing to do. just return
		return;
	}
	else {
		//delete objects iteratively(recursive call actually)
		for (std::list<GObject*>::iterator it = children.begin(); it != children.end(); it++) {
			delete (*it);
		}
	}
}