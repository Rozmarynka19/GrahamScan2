#pragma once
#include "LinkedList.h"
#include "Point.h"
using namespace std;

class Graph
{
	friend class Point;

	static int graphNumber;
	Linked_List<Point>* listOfPoints;
	//this list store points which should be connected by edges
	Linked_List<Point>* listOfEdges;

	void prepareFiles(fstream& pointFile, fstream& edgeFile);
public:
	Graph();	
	//Graph(const Graph* graph);
	~Graph();
	void Load(string filename);
	void DrawGraph();
};