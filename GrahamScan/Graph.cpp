//#include <iomanip>
#include <string>
#include <fstream>
#include <direct.h> //_mkdir
#include <sstream>
#include "Graph.h"
using namespace std;

int Graph::graphNumber=0;
Graph::Graph()
{
	listOfPoints = new Linked_List<Point>();
	listOfEdges = new Linked_List<Point>();
}
//Graph::Graph(const Graph* graph)
//{
//	nodeArray = graph->nodeArray;
//	edgeArray = new Dynamic_Array<Edge>();
//}
Graph::~Graph()
{
	delete listOfPoints;
	delete listOfEdges;
}
//unsigned int Graph::GetListOfPointsSize()
//{
//	return listOfPoints->GetSize();
//}
//unsigned int Graph::GetListOfEdgesSize()
//{
//	return listOfEdges->GetSize();
//}
void Graph::CopyListOfPoints(Linked_List<Point>* LinkedList)
{
	for (int i = 0; i < listOfPoints->GetSize(); i++)
	{
		LinkedList->addToTail(listOfPoints->GetDataOfElement(i));
	}
}
void Graph::Print()
{
	List_Node<Point>* tmp = listOfEdges->head;
	for (int i = 0; i < listOfEdges->size; i++)
	{
		cout << tmp->data.x << "\t" << tmp->data.y << endl;
		tmp = tmp->next;
		getchar();
	}
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
			listOfPoints->addToTail(*(new Point(x, y)));
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

void Graph::prepareFiles(fstream& pointFile, fstream& edgeFile)
{
	/*ofstream file;
	file.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\plik.txt", std::ios::out);
	if (!file.good()) cerr << "file corrupted" << endl;*/
	for (int i = 0; i < listOfPoints->GetSize(); i++)
	{
		pointFile << "		" << i << " [pos=\"" << listOfPoints->GetDataOfElement(i).x<< "," << listOfPoints->GetDataOfElement(i).y<< "!\"]" << std::endl;
	}
	for (int i = 0; i < listOfEdges->GetSize(); i++)
	{
		/*file << " " << (*edgeArray)[i].firstIndex << " -- " << (*edgeArray)[i].secondIndex
			<< " [label=" <<fixed<< (*edgeArray)[i].cost << "]" << endl;*/
		edgeFile << " " << listOfEdges->GetDataOfElement(i).x << " -> " << listOfEdges->GetDataOfElement(i).y
			//<<" [label=\"" << (*edgeArray)[i].cost
			//<<" taillabel="<< (*edgeArray)[i].firstIndex
			//<<" headlabel="<< (*edgeArray)[i].secondIndex
			<<"\"]" << endl;
	}
}
void Graph::DrawGraph()
{
	fstream points, edges, out;
	string line = "", outName;
	stringstream ss;

	_mkdir("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph");
	ss << "\"\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\neato.exe\" -Tpdf \"C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\out.dot\" -o \"C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\graph"<<graphNumber<<".pdf\"";
	//"C:\\Program Files (x86)\\Graphviz2.38\\bin\\neato.exe" -Tpdf "C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\out.dot" -o "C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\graph.pdf"
	outName = ss.str();
	//cout << outName << endl;
	points.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\nodes.txt",std::ios::out|std::ios::in|std::ios::trunc);
	edges.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\edges.txt",std::ios::out|std::ios::in|std::ios::trunc);
	out.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\out.dot",std::ios::out|std::ios::in|std::ios::trunc);

	if (!points.good()) cerr << "Open nodes.txt failed!" << endl;
	if (!edges.good()) cerr << "Open edges.txt failed!" << endl;
	if (!out.good()) cerr << "Open out.dot failed!" << endl;

	prepareFiles(points, edges);

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
	edges.seekg(0, std::ios::beg);
	while (getline(edges, line)) {
		out << line << std::endl;
	}
	points.close();
	edges.close();
	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\points.txt");
	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\edges.txt");
	out << "}" << std::endl;
	out.close();
	system(outName.c_str());
	graphNumber++;

	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\GrahamScan\\graph\\out.dot");
}