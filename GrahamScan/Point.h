#pragma once
#include "LinkedList.h"
#include "Graph.h"

class Point
{
	friend class Graph;
	template <class T> friend class BinaryHeap;
	friend void GrahamScan(Graph* graph, Linked_List<Point>* LinkedList);
	friend int Compare(Point p1, Point p2);
public:	double x;
	double y;

//public:
	Point();
	Point(double a, double b);
	bool operator<(const Point& arg);
	bool operator>(const Point& arg);
	bool operator==(const Point& arg);
	Point operator-(const Point& RightArg) const;
	//Point& operator-=(const Point& RightArg);
	Point operator=(const Point& RightArg);
};