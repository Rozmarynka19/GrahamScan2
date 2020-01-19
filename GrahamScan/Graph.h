#pragma once
#include "Point.h"
#include "DynamicArray.h"
using namespace std;

class Graph
{
	friend class Point;
	friend void GrahamScan(Graph* graph, Dynamic_Array<Point>* PointsCopy);

	static int graphNumber;
	Dynamic_Array<Point>* Points;
	//this list store points which should be connected by edges
	Linked_List<Point>* VertexOfHull;

	void prepareFiles(fstream& pointFile, fstream& edgeFile);
public:
	Graph();	
	////Graph(const Graph* graph);
	~Graph();
	////unsigned int GetListOfPointsSize();
	unsigned int GetNumberOfVertex();
	void Print();
	void PrintVertex();
	Point* GetStartPoint();
	void MakeCopyOfPoints(Dynamic_Array<Point>* PointsCopy, Point StartPoint);
	void AddVertexToHull(Point vertex);
	void RemoveSecondToLastVertex();
	Point GetVertex(int index);
	void Load(string filename);
	void DrawGraph();
};