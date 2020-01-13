#include <iostream>
#include "Graph.h"
#include "HeapSort.h"
using namespace std;

void GrahamScan(Graph* graph, Linked_List<Point>* LinkedList)
{
	Point* StartPoint = LinkedList->FindStartPoint();
	//cout << "startpoint: " << StartPoint->x << "\t" << StartPoint->y << endl;
	if (LinkedList->SearchAndDestoryNode(*StartPoint, Compare<Point>)) cout << "Removing StartPoint failed!" << endl;

	graph->listOfEdges->addToTail(*StartPoint);
	Point p = graph->listOfEdges->GetDataOfElement(0);
	cout << p.x << "\t" << p.y << endl;
	LinkedList->NewCoordinatesSystem(StartPoint);

	BinaryHeap<Point>* binaryHeap = new BinaryHeap<Point>(LinkedList, true, false);
	binaryHeap->HeapSort();

	graph->listOfEdges->addToTail(LinkedList->GetDataOfElement(0));
	for (int i = 1; i < LinkedList->GetSize(); i++)
	{
		graph->listOfEdges->addToTail(LinkedList->GetDataOfElement(i));
		//dopoki zakret w prawo
		while (Compare(graph->listOfEdges->GetDataOfElement(graph->listOfEdges->GetSize()-1) - graph->listOfEdges->GetDataOfElement(graph->listOfEdges->GetSize() - 2),
			graph->listOfEdges->GetDataOfElement(graph->listOfEdges->GetSize() - 2) - graph->listOfEdges->GetDataOfElement(graph->listOfEdges->GetSize() - 3)))
		{
			graph->listOfEdges->RemoveSecondToLast();
		}
	}
}



int main()
{
	Graph* graph = new Graph();
	Linked_List<Point>* LinkedList = new Linked_List<Point>();

	graph->Load("points1.txt");

	graph->CopyListOfPoints(LinkedList);
	GrahamScan(graph, LinkedList);
	//graph->Print();
	graph->DrawGraph();

	cout << "Hello World!\n";
}