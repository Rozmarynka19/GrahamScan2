//#include <iomanip>
#include <string>
#include <fstream>
#include <direct.h> //_mkdir
#include <sstream>
//#include "DynamicArray.h"
#include "Graph.h"
//#include "Point.h"
using namespace std;

int Graph::graphNumber=0;
Graph::Graph()
{
	Points = new Dynamic_Array<Point>();
	VertexOfHull = new Linked_List<Point>();
}
//Graph::Graph(const Graph* graph)
//{
//	nodeArray = graph->nodeArray;
//	edgeArray = new Dynamic_Array<Edge>();
//}
Graph::~Graph()
{
	delete Points;
	delete VertexOfHull;
}
//unsigned int Graph::GetListOfPointsSize()
//{
//	return listOfPoints->GetSize();
//}
unsigned int Graph::GetNumberOfVertex()
{
	return VertexOfHull->GetSize();
}
void Graph::MakeCopyOfPoints(Dynamic_Array<Point>* PointsCopy, Point StartPoint)
{
	Points->CopyWithout(PointsCopy, StartPoint);
}
void Graph::AddVertexToHull(Point vertex)
{
	VertexOfHull->addToTail(vertex);
}
void Graph::RemoveSecondToLastVertex()
{
	VertexOfHull->RemoveSecondToLast();
}
Point Graph::GetVertex(int index)
{
	return *(VertexOfHull->GetDataOfElement(index));
}
void Graph::Print()
{
	for (int i = 0; i < Points->currentSize; i++)
	{
		cout <<Points->getData(i).label << ": " << Points->getData(i).x << "," << Points->getData(i).y << endl;
	}
}
void Graph::PrintVertex()
{
	List_Node<Point>* tmp = VertexOfHull->head;
	cout << "VertexOfHull's Size: " << VertexOfHull->GetSize() << endl;
	/*cout << "Press ENTER to continue... " << endl;
	getchar();*/
	for (int i = 0; i < VertexOfHull->size; i++)
	{
		cout <<tmp->data.label<<": "<< tmp->data.x << ", " << tmp->data.y << endl;
		tmp = tmp->next;
	}
}
Point* Graph::GetStartPoint()
{
	return Points->FindStartPoint();
}
void Graph::Load(string filename)
{
	ifstream plik;

	plik.open(filename);

	if (plik.good())
	{
		string line;
		int number;
		double x, y;

		plik >> line;
		//cout << line << endl;
		number = atoi(line.c_str());

		for (int i = 0; i < number; i++)
		{
			plik >> line;
			x = atof(line.c_str());
			plik >> line;
			y = atof(line.c_str());

			//cout << x << "\t" << y;
			//getchar();
			Points->addElement(*(new Point(x, y,i)));
		}
		if (!plik.eof()) {
			cout << "I got sth else to read..." << endl;
			cout << line << endl;
		}

		cout << "\nGraph has been loaded." << endl;
		//cout<<nodeArray->getData(7);
		//nodeArray->operator[](5).x;
		//(*nodeArray)[5].x;
	}
	else
	{
		try
		{
			throw logic_error("Reading file failed!");
		}
		catch (logic_error & error)
		{
			cout << "Logic error: " << error.what() << " Make sure that the file exists." << endl;
			terminate();
		}
	}
}

void Graph::prepareFiles(fstream& pointFile, fstream& vertexFile)
{
	/*ofstream file;
	file.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\plik.txt", std::ios::out);
	if (!file.good()) cerr << "file corrupted" << endl;*/
	for (int i = 0; i < Points->currentSize; i++)
	{
		pointFile << "		" << Points->getData(i).label << " [pos=\"" << Points->getData(i).x * 5<< "," << Points->getData(i).y * 5 << "!\"]" << endl;
	}
	for (int i = 1; i < VertexOfHull->GetSize(); i++)
	{
		/*file << " " << (*edgeArray)[i].firstIndex << " -- " << (*edgeArray)[i].secondIndex
			<< " [label=" <<fixed<< (*edgeArray)[i].cost << "]" << endl;*/
		vertexFile << " " << VertexOfHull->GetDataOfElement(i-1)->label << " -> " << VertexOfHull->GetDataOfElement(i)->label
			//<<" [label=\"" << (*edgeArray)[i].cost
			//<<" taillabel="<< (*edgeArray)[i].firstIndex
			//<<" headlabel="<< (*edgeArray)[i].secondIndex
			//<<"\"]"
			<< endl;
	}
	vertexFile << " " << VertexOfHull->GetDataOfElement(VertexOfHull->GetSize() - 1)->label << " -> " << VertexOfHull->GetDataOfElement(0)->label << endl;
}
void Graph::DrawGraph()
{
	fstream points, vertex, out;
	string line = "", outName;
	stringstream ss;

	_mkdir("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph");
	ss << "\"\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\neato.exe\" -Tpdf \"C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\out.dot\" -o \"C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\graph"<<graphNumber<<".pdf\"";
	//"C:\\Program Files (x86)\\Graphviz2.38\\bin\\neato.exe" -Tpdf "C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\out.dot" -o "C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\graph.pdf"
	outName = ss.str();
	//cout << outName << endl;
	points.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\points.txt",std::ios::out|std::ios::in|std::ios::trunc);
	vertex.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\vertex.txt",std::ios::out|std::ios::in|std::ios::trunc);
	out.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\out.dot",std::ios::out|std::ios::in|std::ios::trunc);

	if (!points.good()) cerr << "Open points.txt failed!" << endl;
	if (!vertex.good()) cerr << "Open vertex.txt failed!" << endl;
	if (!out.good()) cerr << "Open out.dot failed!" << endl;

	prepareFiles(points, vertex);

	out << "digraph D {" << std::endl;
	out << "	{" << std::endl;
	//out << "	 node [shape = circle, style=filled, fontsize=10]" << std::endl;
	out << "	 node [shape = circle, style=filled, width=0.2, fixedsize=true, fontsize=10]" << std::endl;
	//out << "	 node [shape = point]" << std::endl;

	points.seekg(0, std::ios::beg);
	while (getline(points, line)) {
		out << line << std::endl;
	}
	out << "	}" << std::endl;
	vertex.seekg(0, std::ios::beg);
	while (getline(vertex, line)) {
		out << line << std::endl;
	}
	points.close();
	vertex.close();
	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\points.txt");
	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\vertex.txt");
	out << "}" << std::endl;
	out.close();
	system(outName.c_str());
	graphNumber++;

	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan2\\graph\\out.dot");
}