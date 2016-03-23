#include "Rect.h"
#include <stdlib.h>

Rect::Rect() {
	this->_x = 0;
	this->_y = 0;
	this->_width = 0;
	this->_height = 0;
}
Rect::Rect(double x, double y, double width, double height) {
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;
}
double Rect::left() {
	return this->_x;
}
double Rect::top() {
	return this->_y;
}
double  Rect::right() {
	return this->_x + this->_width;
}
double Rect::bottom() {
	return this->_y - this->_height;
}
double Rect::x() {
	return _x;
}
double Rect::y() {
	return _y;
}
double Rect::width() {
	return _width;
}
double Rect::height() {
	return _height;
}
bool Rect::isPointInRect(Rect& rect, double x, double y) {
	if (rect.left() <= x && x <= rect.right() && rect.bottom() <= y && y <= rect.top())
		return true;
	else 
		return false;
}
void Rect::setX(int x) {
	this->_x = x;
}
void Rect::setY(int y) {
	this->_y = y;
}
void Rect::setWidth(int width) {
	this->_width = width;
}
void Rect::setHeight(int height) {
	this->_height = height;
}
bool Rect::isCollide(Rect& a, Rect& b) {
	return abs((long long)(a._x - b._x)) * 2 < a._width + b._width &&
		abs((long long)(a._y - b._y)) < a._height + b._height;
}