#include "Point.h"

Point::Point()
{
	x = y = 0;
	label = -1;
}
Point::Point(const Point& point)
{
	x = point.x;
	y = point.y;
	label = point.label;
}
Point::Point(double a, double b,int l)
{
	x = a;
	y = b;
	label = l;
}
bool Point::operator<(const Point& arg)
{
	return ((x < arg.x)&&(y<arg.y));
}
bool Point::operator>(const Point& arg)
{
	return ((x > arg.x) && (y > arg.y));
}
//Point& Point::operator=(const Point& arg)
//{
//	x = arg.x;
//	y = arg.y;
//
//	return *this;
//}
bool Point::operator==(const Point& arg)
{
	return ((x == arg.x) && (y == arg.y));
}
Point Point::operator-(const Point& RightArg) const
{
	return Point(this->x - RightArg.x, this->y - RightArg.y,this->label);
}
//Point& Point::operator-=(const Point& RightArg)
//{
//	this->x -= RightArg.x;
//	this->y -= RightArg.y;
//
//	return *this;
//
//}
//Point Point::operator=(const Point& RightArg)
//{
//	this->x = RightArg.x;
//	this->y = RightArg.y;
//
//	return *this;
//}
