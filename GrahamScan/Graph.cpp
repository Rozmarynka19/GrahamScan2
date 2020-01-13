#include <iostream>
//#include <iomanip>
#include <string>
#include <fstream>
#include <direct.h> //_mkdir
#include <sstream>
#include "DynamicArray.h"
#include "Edge.h"
#include "Node.h"
#include "Graph.h"
using namespace std;

int Graph::graphNumber=0;
Graph::Graph()
{
	nodeArray = new Dynamic_Array<Node>();
	edgeArray = new Dynamic_Array<Edge>();
}
Graph::Graph(const Graph* graph)
{
	nodeArray = graph->nodeArray;
	edgeArray = new Dynamic_Array<Edge>();
}
Graph::~Graph()
{
	delete nodeArray;
	delete edgeArray;
}
double Graph::CountSumOfCost()
{
	double result = 0;
	for (int i = 0; i < edgeArray->currentSize; i++)
		result += (*edgeArray)[i].cost;
	return result;
}
void Graph::Load(string filename)
{
	ifstream plik;

	plik.open(filename);

	if (plik.good())
	{
		string line;
		int number, i1, i2;
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
			nodeArray->addElement(*(new Node(x, y)));
		}
		//cout << nodeArray->currentSize << endl;

		plik >> line;
		//cout << line << endl;
		number = atoi(line.c_str());

		for (int i = 0; i < number; i++)
		{
			plik >> line;
			i1 = atoi(line.c_str());
			plik >> line;
			i2 = atoi(line.c_str());
			plik >> line;
			x = atof(line.c_str());

			//cout << i1 << "\t" << i2 << "\t" << x;
			//getchar();
			edgeArray->addElement(*(new Edge(i1, i2, x)));
		}
		//cout << edgeArray->currentSize << endl;
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

void Graph::prepareFiles(fstream& nodeFile, fstream& edgeFile)
{
	/*ofstream file;
	file.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\plik.txt", std::ios::out);
	if (!file.good()) cerr << "file corrupted" << endl;*/
	for (int i = 0; i < nodeArray->currentSize; i++)
	{
		nodeFile << "		" << i << " [pos=\"" << (*nodeArray)[i].x * 10 << "," << (*nodeArray)[i].y * 10 << "!\"]" << std::endl;
	}
	for (int i = 0; i < edgeArray->currentSize; i++)
	{
		/*file << " " << (*edgeArray)[i].firstIndex << " -- " << (*edgeArray)[i].secondIndex
			<< " [label=" <<fixed<< (*edgeArray)[i].cost << "]" << endl;*/
		edgeFile << " " << (*edgeArray)[i].firstIndex << " -- " << (*edgeArray)[i].secondIndex
			<<" [label=\"" << (*edgeArray)[i].cost
			//<<" taillabel="<< (*edgeArray)[i].firstIndex
			//<<" headlabel="<< (*edgeArray)[i].secondIndex
			<<"\"]" << endl;
	}
}
void Graph::DrawGraph()
{
	fstream nodes, edges, out;
	string line = "", outName;
	stringstream ss;

	_mkdir("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph");
	ss << "\"\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\neato.exe\" -Tpdf \"C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\out.dot\" -o \"C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\graph"<<graphNumber<<".pdf\"";
	//"C:\\Program Files (x86)\\Graphviz2.38\\bin\\neato.exe" -Tpdf "C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\out.dot" -o "C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\graph.pdf"
	outName = ss.str();
	//cout << outName << endl;
	nodes.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\nodes.txt",std::ios::out|std::ios::in|std::ios::trunc);
	edges.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\edges.txt",std::ios::out|std::ios::in|std::ios::trunc);
	out.open("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\out.dot",std::ios::out|std::ios::in|std::ios::trunc);

	if (!nodes.good()) cerr << "Open nodes.txt failed!" << endl;
	if (!edges.good()) cerr << "Open edges.txt failed!" << endl;
	if (!out.good()) cerr << "Open out.dot failed!" << endl;

	prepareFiles(nodes, edges);

	out << "graph D {" << std::endl;
	out << "	{" << std::endl;
	//out << "	 node [shape = circle, style=filled, fontsize=10]" << std::endl;
	out << "	 node [shape = circle, style=filled, width=0.2, fixedsize=true, fontsize=10]" << std::endl;
	//out << "	 node [shape = point]" << std::endl;

	nodes.seekg(0, std::ios::beg);
	while (getline(nodes, line)) {
		out << line << std::endl;
	}
	out << "	}" << std::endl;
	edges.seekg(0, std::ios::beg);
	while (getline(edges, line)) {
		out << line << std::endl;
	}
	nodes.close();
	edges.close();
	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\nodes.txt");
	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\edges.txt");
	out << "}" << std::endl;
	out.close();
	system(outName.c_str());
	graphNumber++;

	//remove("C:\\Users\\Lara\\Desktop\\Algorytmy2\\Laboratoria\\7.KruskalAndUF\\graph\\out.dot");
}