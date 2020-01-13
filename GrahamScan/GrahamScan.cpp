#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	Graph* graph = new Graph();
	graph->Load("points1.txt");
	graph->DrawGraph();
	cout << "Hello World!\n";
}