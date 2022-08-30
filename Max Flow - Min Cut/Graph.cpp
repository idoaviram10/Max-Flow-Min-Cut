#include "Graph.h"


/*------------------------------ C'tors and D'tors ----------------------------------*/
Graph::Graph(int n, int m)
{
	setNumOfVertices(n);
	setNumOfEdges(m);
	makeEmptyGraph(n);
	degreeArray = new int[n + 1];
	parentArray = new int[n + 1];
	visitedArray = new int[n + 1];
}

Graph::Graph(const Graph& other)
{
	this->numOfVertices = other.numOfVertices;
	this->numOfEdges = other.numOfEdges;

	this->makeEmptyGraph(numOfVertices);
	for (int i = 1; i <= numOfVertices; i++)
	{
		this->graph[i] = other.graph[i];
	}

	this->degreeArray = new int[numOfVertices + 1];
	this->parentArray = new int[numOfVertices + 1];
	this->visitedArray = new int[numOfVertices + 1];
}

Graph::~Graph()
{
	delete[] degreeArray;
	delete[] parentArray;
	delete[] visitedArray;
}
/*-----------------------------------------------------------------------------------*/

int Graph::getFlowOfEdge(int u, int v)
{
	for (Edge x : graph[u])
	{
		if (x.vertex == v)
		{
			return x.flow;
		}
	}

	return 0;
}

int Graph::getCapacityOfEdge(int u, int v)
{
	for (Edge x : graph[u])
	{
		if (x.vertex == v)
			return x.capacity;
	}

	return -1;
}

void Graph::makeEmptyGraph(int n)
{
	graph.resize(n + 1);
}

list<Edge> Graph::getAdjList(int u)
{
	return graph[u];
}

void Graph::addEdge(int u, int v, int c)
{
	if (alreadyExists(u, v))
		return;
	Edge tempEdge{ v, c, 0 };
	graph[u].push_back(tempEdge);
}

void Graph::addEdge(int u, int v, int c, int f)
{
	if (alreadyExists(u, v))
		return;
	Edge tempEdge{ v, c, f };
	graph[u].push_back(tempEdge);
}

void Graph::removeEdge(int u, int v, int value, char flowOrCapacity)
{
	for (Edge e : graph[u])
	{
		if (flowOrCapacity == 'f')
		{
			if (e.vertex == v && e.flow == value)
			{
				graph[u].remove(e);
				break;
			}
		}
		else
		{
			if (e.vertex == v && e.capacity == value)
			{
				graph[u].remove(e);
				break;
			}
		}
	}
}

void Graph::updateFlowOfEdge(int u, int v, int newFlow)
{
	Edge tempEdge;
	auto itr = graph[u].begin();
	//if (itr != nullptr)
	for (itr = graph[u].begin(); itr != graph[u].end(); itr++)
	{
		if ((*itr).vertex == v) {
			tempEdge = (*itr);
			break;
		}
	}
	if (itr != graph[u].end())
	{
		if (newFlow != (*itr).flow)
		{
			tempEdge.flow = newFlow;
			graph[u].emplace(itr, tempEdge);
			removeEdge(u, v, (*itr).flow, 'f');
		}
	}
}

void Graph::updateCapacityOfEdge(int u, int v, int newCapacity)
{
	Edge tempEdge;
	auto itr = graph[u].begin();
	//if (itr != nullptr)
	for (itr = graph[u].begin(); itr != graph[u].end(); itr++)
	{
		if ((*itr).vertex == v) {
			tempEdge = (*itr);
			break;
		}
	}
	if (itr != graph[u].end())
	{
		if (newCapacity != (*itr).capacity)
		{
			tempEdge.capacity = newCapacity;
			graph[u].emplace(itr, tempEdge);
			removeEdge(u, v, (*itr).capacity, 'c');
		}
	}
}

void Graph::updateVisitedArray(int u, bool visit)
{
	visitedArray[u] = visit;
}

void Graph::removeAllFullEdges(Graph& G)
{
	list<Edge> adjList;
	for (int i = 1; i <= G.getNumOfVertices(); i++)
	{
		adjList = G.getAdjList(i);
		for (auto x : adjList)
		{
			if (x.capacity == x.flow && x.capacity != 0)
			{
				removeEdge(i, x.vertex, x.capacity - x.flow, 'c');
			}
		}
	}
}

void Graph::printGraph(bool isResidual)
{
	int i = 0;
	for (auto v : graph)
	{
		if (i != 0)
		{
			cout << i << ":  ";
			for (auto e : v)
			{
				if (isResidual)
					cout << e.vertex << "(" << e.capacity << ")  ";
				else
					cout << e.vertex << "(" << e.flow << "\\" << e.capacity << ")  ";
			}
			cout << endl;
		}
		i++;
	}
}

bool Graph::alreadyExists(int u, int v)
{
	for (auto x : graph[u])
	{
		if (x.vertex == v)
			return true;
	}
	return false;
}