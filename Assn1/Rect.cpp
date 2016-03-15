#include "Rect.h"

Rect::Rect() {
	this->_left = 0;
	this->_top = 0;
	this->_right = 0;
	this->_bottom = 0;
}
Rect::Rect(double left, double top, double right, double bottom) {
	this->_left = left;
	this->_top = top;
	this->_right = right;
	this->_bottom = bottom;
}
double Rect::left() {
	return this->_left;
}
double Rect::top() {
	return this->_top;
}
double  Rect::right() {
	return this->_right;
}
double Rect::bottom() {
	return this->_bottom;
}
bool Rect::isPointInRect(const Rect& rect, double x, double y) {
	if (rect._left <= x && x <= rect._right && rect._bottom <= y && y <= rect._top)
		return true;
	else 
		return false;
}
bool Rect::isCollide(const Rect& a, const Rect& b) {
	if (isPointInRect(a, b._left, b._top) || isPointInRect(a, b._left, b._bottom)
		|| isPointInRect(a, b._right, b._top) || isPointInRect(a, b._right, b._bottom))
		return true;
	else
		return false;
}