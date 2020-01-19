#pragma once
#include "LinkedList.h"
#include "DynamicArray.h"
#include "Graph.h"

class Point
{
	friend class Graph;
	template <class T> friend class BinaryHeap;
	friend void GrahamScan(Graph* graph, Dynamic_Array<Point>* PointsCopy);
	friend int Compare(Point p1, Point p2);
public:	double x;
	double y;
	int label;

//public:
	Point();
	Point(const Point& point);
	Point(double a, double b,int l);
	bool operator<(const Point& arg);
	bool operator>(const Point& arg);
	//Point& operator=(const Point& arg);
	bool operator==(const Point& arg);
	Point operator-(const Point& RightArg) const;
	//Point& operator-=(const Point& RightArg);
	//Point operator=(const Point& RightArg);
};