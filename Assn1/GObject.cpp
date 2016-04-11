#include "GObject.h"
#include "Rect.h"
#include "Game.h"
#include <string>
#include <queue>

extern Game game;

void GObject::setRect(const Rect& rect) {
	/* sets the obj boundbox */
	this->obj = rect;
}
void GObject::onTraverseDraw(mat4 MVMatrix) {

	/* Get parent's matrix */
	mat4 MVMatrixLocal = MVMatrix;

	MVMatrixLocal = MVMatrixLocal
		* Translate(vec3(obj.x(), obj.y(), 0))
		* Translate(vec3(rotx, roty, 0))
		* RotateZ((GLfloat)rotation)
		* Translate(vec3(-rotx, -roty, 0));

	std::list<GObject*>::iterator nonnegstart = children.begin(); //the children with the first non-negative z-index
	//negative indices
	if (nonnegstart != children.end()) {
		if ((*nonnegstart)->getZ() < 0) {
			for (std::list<GObject*>::iterator it = children.begin(); it != children.end(); it++) {
				if ((*it)->getZ() >= 0) {
					nonnegstart = it;
					break;
				}
				else {
					(*it)->onTraverseDraw(MVMatrixLocal);
				}
			}
		}
	}
	//draw this node

	draw(MVMatrixLocal);

	//positive indexes
	if (nonnegstart != children.end()) {
		for (std::list<GObject*>::iterator it = nonnegstart; it != children.end(); it++) {
			(*it)->onTraverseDraw(MVMatrixLocal);
		}
	}
}
void GObject::onTraverseUpdate() {
	//preorder traverse
	frameAction();//do this node's update
	//update children
	for (std::list<GObject*>::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->onTraverseUpdate();
	}
}
GObject::GObject(const Rect& obj, const Rect& hitbox, std::string type) {
	this->parent = nullptr;
	this->obj = obj;
	this->hitbox = hitbox;
	this->type = type;
	this->z = 0;
}
void GObject::setPos(double x, double y) {
	this->obj.setX(x);
	this->obj.setY(y);
}
void GObject::setRotCenter(double x, double y) {
	this->rotx = x;
	this->roty = y;
}
void GObject::setRotation(double rot) {
	this->rotation = rot;
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
Rect GObject::getgloobj() {
	//get object of global location 
	GObject* curr_node = this; 
	double x = 0, y = 0;
	Rect original_rect = this->getobj();

	while (curr_node != nullptr) {
		Rect curr_rect = curr_node->getobj();
		x += curr_rect.x();
		y += curr_rect.y();
		
		curr_node = curr_node->getParent();
	}
	return Rect(x, y, original_rect.width(), original_rect.height());
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
GObject* GObject::getChildOfType(std::string type) {
	/* returns the most closest -in hierachial sense- child with given type */
	GObject* result = (type==this->type) ? this : nullptr;
	GObject* tmp = nullptr;
	if (result == nullptr) {
		for (std::list<GObject*>::iterator it = children.begin(); it != children.end(); it++) {
			tmp = (*it)->getChildOfType(type);
			if (tmp != nullptr) result = tmp;
		}
	}
	return result;
}
std::list<GObject*>* GObject::getChildren() {
	return &children;
}
bool GObject::isCollide(GObject& o1, GObject& o2) {
	Rect a = Rect(o1.getgloobj().x() + o1.gethitbox().x(), o1.getgloobj().y() + o1.gethitbox().y(), o1.gethitbox().width(), o1.gethitbox().height());
	Rect b = Rect(o2.getgloobj().x() + o2.gethitbox().x(), o2.getgloobj().y() + o2.gethitbox().y(), o2.gethitbox().width(), o2.gethitbox().height());

	if (Rect::isCollide(a, b)) 
		return true;
	else 
		return false;
}
GObject* GObject::addObject(GObject* obj, int z) {
	/* adds a node to the child of this node
	keeping the order of z-index left to right */
	bool isAdded = false;

	//sets the z-index of this object to the given z
	obj->z = z;

	//order to z-index
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
	//set parent
	obj->parent = this;
	return obj;
}
GObject* GObject::removeObject(GObject* obj) {
	/* remove specified GObject from the root of Scene Graph */
	std::queue<GObject*> travq;
	std::list<GObject*>* current_children;
	std::list<GObject*> result;

	travq.push(this);

	while (!travq.empty()) {
		current_children = travq.front()->getChildren();
		travq.pop();
		for (std::list<GObject*>::iterator it = current_children->begin(); it != current_children->end(); it++) {
			if ((*it) == obj) {
				current_children->erase(it);
				delete obj;
				return obj;
			}
			travq.push((*it));
		}
	}
	return nullptr;
}
GObject* GObject::getParent() {
	return parent;
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