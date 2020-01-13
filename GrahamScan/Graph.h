#pragma once
#include "Point.h"
using namespace std;

class Graph
{
	friend class Point;
	friend void GrahamScan(Graph* graph, Linked_List<Point>* LinkedList);

	static int graphNumber;
	Linked_List<Point>* listOfPoints;
	//this list store points which should be connected by edges
	Linked_List<Point>* listOfEdges;

	void prepareFiles(fstream& pointFile, fstream& edgeFile);
public:
	Graph();	
	//Graph(const Graph* graph);
	~Graph();
	//unsigned int GetListOfPointsSize();
	//unsigned int GetListOfEdgesSize();
	void Print();
	void CopyListOfPoints(Linked_List<Point>* LinkedList);
	void Load(string filename);
	void DrawGraph();
};