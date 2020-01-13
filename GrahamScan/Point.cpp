#include "Point.h"

Point::Point()
{
	x = y = 0;
}
Point::Point(double a, double b)
{
	x = a;
	y = b;
}
bool Point::operator<(const Point& arg)
{
	return ((x < arg.x)&&(y<arg.y));
}
bool Point::operator>(const Point& arg)
{
	return ((x > arg.x) && (y > arg.y));
}
bool Point::operator==(const Point& arg)
{
	return ((x == arg.x) && (y == arg.y));
}
Point Point::operator-(const Point& RightArg) const
{
	return Point(this->x - RightArg.x, this->y - RightArg.y);
}
//Point& Point::operator-=(const Point& RightArg)
//{
//	this->x -= RightArg.x;
//	this->y -= RightArg.y;
//
//	return *this;
//
//}
Point Point::operator=(const Point& RightArg)
{
	this->x = RightArg.x;
	this->y = RightArg.y;

	return *this;
}
