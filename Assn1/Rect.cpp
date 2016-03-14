#include "Rect.h"

Rect::Rect() {
	this->left = 0;
	this->top = 0;
	this->right = 0;
	this->bottom = 0;
}
Rect::Rect(double left, double top, double right, double bottom) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}
double Rect::left() {
	return this->left;
}
double Rect::top() {
	return this->top;
}
double  Rect::right() {
	return this->right;
}
double Rect::bottom() {
	return this->bottom;
}
bool Rect::isPointInRect(const Rect& rect, double x, double y) {
	if (rect.left <= x && x <= rect.right && rect.bottom <= y && y <= rect.top)
		return true;
	else 
		return false;
}
bool Rect::isCollide(const Rect& a, const Rect& b) {
	if (isPointInRect(a, b.left, b.top) || isPointInRect(a, b.left, b.bottom)
		|| isPointInRect(a, b.right, b.top) || isPointInRect(a, b.right, b.bottom))
		return true;
	else
		return false;
}