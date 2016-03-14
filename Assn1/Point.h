#pragma once
class Point {
private:
	double x, y;
public:
	Point(double x, double y);
	double get_x();
	double get_y();
	void set_pt(double x, double y);
};
