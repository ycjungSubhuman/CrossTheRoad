#pragma once

class Rect {
private:
	double left, top, right, bottom;
	static bool isPointInRect(const Rect& rect, double x, double y);
public:
	Rect();
	Rect(double x, double y, double width, double height);
	double top();
	double bottom();
	double left();
	double right();
	static bool isCollide(const Rect& a, const Rect& b);
};