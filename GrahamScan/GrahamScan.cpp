#include <iostream>
#include <time.h>
#include "Graph.h"
#include "Point.h"
#include "DynamicArray.h"
#include "HeapSort.h"
using namespace std;
clock_t GrahamStart, GrahamStop, SortStart, SortStop;

void GrahamScan(Graph* graph, Dynamic_Array<Point>* PointsCopy)
{
	Point* StartPoint = graph->GetStartPoint();

	//copy of points without StartPoint
	graph->MakeCopyOfPoints(PointsCopy, *StartPoint);

	PointsCopy->NewCoordinatesSystem(*StartPoint);

	BinaryHeap<Point>* binaryHeap = new BinaryHeap<Point>(PointsCopy, true, false);

	SortStart = clock();
	binaryHeap->HeapSort();
	SortStop = clock();
	
	
	graph->AddVertexToHull(*StartPoint-*StartPoint);
	graph->AddVertexToHull(PointsCopy->getData(0));

	cout << "Main GrahamScan's loop starts..." << endl;
	GrahamStart = clock();
	for (int i = 1; i < PointsCopy->currentSize; i++)
	{
		graph->AddVertexToHull(PointsCopy->getData(i));
		//till right turn - remove second to last vertex
			while (Compare(graph->GetVertex(graph->GetNumberOfVertex() - 1) - graph->GetVertex(graph->GetNumberOfVertex() - 2),
				graph->GetVertex(graph->GetNumberOfVertex() - 2) - graph->GetVertex(graph->GetNumberOfVertex() - 3)) == -1)
		{
			graph->RemoveSecondToLastVertex();
		}
	}
	GrahamStop = clock();
	
	delete binaryHeap;
}

void DrawSummary(Graph* graph)
{
	cout.precision(numeric_limits<double>::max_digits10);
	cout << "\n============= SUMMARY =============" << endl;
	cout <<"Number of points: "<<graph->GetNumberOfPoints()<<endl
		<< "Number of vertex: "<< graph->GetNumberOfVertex()<<endl
		<< "Indexes of vertices: " << graph->IndexOfVertexToString()<<endl
		<< "Time of sorting[s]: " << (SortStop - SortStart) / (double)CLOCKS_PER_SEC << endl
		<< "Time of main Graham's loop[s]: " << (GrahamStop - GrahamStart) / (double)CLOCKS_PER_SEC << endl
		<< "Total time[s]: " << ((SortStop - SortStart) / (double)CLOCKS_PER_SEC) + ((GrahamStop - GrahamStart) / (double)CLOCKS_PER_SEC) << endl
		<< "===================================" << endl;
}



int main()
{
	Graph* graph = new Graph();
	Dynamic_Array<Point>* PointsCopy = new Dynamic_Array<Point>();

	graph->Load("points5.txt");
	//graph->Print();

	GrahamScan(graph, PointsCopy);
	DrawSummary(graph);
	//graph->PrintVertex();
	//graph->DrawGraph();


	delete graph, PointsCopy;
}