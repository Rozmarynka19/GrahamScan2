#include <iostream>
#include "Graph.h"
#include "Point.h"
#include "DynamicArray.h"
#include "HeapSort.h"
using namespace std;

void GrahamScan(Graph* graph, Dynamic_Array<Point>* PointsCopy)
{
	Point* StartPoint = graph->GetStartPoint();
	//cout << StartPoint->label << ": " << StartPoint->x << "," << StartPoint->y << endl;

	//copy of points without StartPoint
	graph->MakeCopyOfPoints(PointsCopy, *StartPoint);

	/*cout << "PointsCopy's Size: " << PointsCopy->currentSize << endl;
	for (int i = 0; i < PointsCopy->currentSize; i++)
	{
		cout << PointsCopy->getData(i).label << ": " << PointsCopy->getData(i).x << ", " << PointsCopy->getData(i).y << endl;
	}*/


	PointsCopy->NewCoordinatesSystem(*StartPoint);

	/*cout << "PointsCopy's Size: " << PointsCopy->currentSize << endl;
	for (int i = 0; i < PointsCopy->currentSize; i++)
	{
		cout << PointsCopy->getData(i).label << ": " << PointsCopy->getData(i).x << ", " << PointsCopy->getData(i).y << endl;
		getchar();
	}*/

	BinaryHeap<Point>* binaryHeap = new BinaryHeap<Point>(PointsCopy, true, false);
	/*for (int i = 0; i < PointsCopy->currentSize; i++)
	{
		cout << PointsCopy->getData(i).label << ": " << PointsCopy->getData(i).x << ", " << PointsCopy->getData(i).y << " " << PointsCopy->getData(i).x / PointsCopy->getData(i).y << endl;
		getchar();
	}*/
	//cout << "OK" << endl;
	binaryHeap->HeapSort();
	
	cout << "PointsCopy's Size: " << PointsCopy->currentSize << endl;
	/*for (int i = 0; i < PointsCopy->currentSize; i++)
	{
		cout << PointsCopy->getData(i).label << ": " << PointsCopy->getData(i).x << ", " << PointsCopy->getData(i).y << " " << PointsCopy->getData(i).x / PointsCopy->getData(i).y << endl;
		getchar();
	}*/
	


	cout << "Przed petla" << endl;
	graph->AddVertexToHull(*StartPoint-*StartPoint);
	graph->AddVertexToHull(PointsCopy->getData(0));
	for (int i = 1; i < PointsCopy->currentSize; i++)
	{
		graph->AddVertexToHull(PointsCopy->getData(i));
		//dopoki zakret w prawo
			while (Compare(graph->GetVertex(graph->GetNumberOfVertex() - 1) - graph->GetVertex(graph->GetNumberOfVertex() - 2),
				graph->GetVertex(graph->GetNumberOfVertex() - 2) - graph->GetVertex(graph->GetNumberOfVertex() - 3)) == -1)
		{
			graph->RemoveSecondToLastVertex();
		}
	}
	
	delete binaryHeap;
}




int main()
{
	Graph* graph = new Graph();
	Dynamic_Array<Point>* PointsCopy = new Dynamic_Array<Point>();

	graph->Load("points5.txt");
	//graph->Print();

	GrahamScan(graph, PointsCopy);
	graph->PrintVertex();
	//graph->DrawGraph();


	cout << "Hello World!\n";
	delete graph, PointsCopy;

	//////////////////////////////////////////////////////////

	//Dynamic_Array<int>* ar = new Dynamic_Array<int>();
	//ar->addElement(10);
	//ar->addElement(250);
	//ar->addElement(2340);
	//ar->addElement(530);
	//ar->addElement(30);
	//ar->addElement(53);
	//ar->addElement(23);
	//ar->addElement(64);
	//ar->addElement(5);
	//ar->addElement(56);

	//for (int i = 0; i < ar->currentSize; i++)
	//	cout << ar->getData(i) << endl;

	//cout << endl;
	//cout << endl;


	//BinaryHeap<int>* bh = new BinaryHeap<int>(ar, false, false);
	//

	//for (int i = 0; i < ar->currentSize; i++)
	//	cout << ar->getData(i) << endl;

	//cout << endl;
	//	cout << endl;

	//bh->HeapSort();

	//for (int i = 0; i < ar->currentSize; i++)
	//	cout << ar->getData(i) << endl;

	//delete ar, bh;
}