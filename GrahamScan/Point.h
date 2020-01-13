#pragma once

class Point
{
	friend class Graph;
	double x;
	double y;

public:
	Point();
	Point(double a, double b);

};