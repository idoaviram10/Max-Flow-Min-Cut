#pragma once
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
#include <iostream>

using namespace std;

struct Edge
{
	int vertex;
	int capacity;
	int flow;

	bool operator==(const Edge& edge) const {
		return this->vertex == edge.vertex && this->capacity == edge.capacity && this->flow == edge.flow;
	}

	void operator=(const Edge edge) {
		this->vertex = edge.vertex;
		this->capacity = edge.capacity;
		this->flow = edge.flow;
	}
};

class Graph
{
private:
	int numOfVertices;
	int numOfEdges;
	vector< list<Edge> > graph;
	int* degreeArray;
	int* parentArray;
	int* visitedArray;
public:
	/*------------------------------ C'tors and D'tors ----------------------------------*/
	Graph(int n, int m);
	Graph(const Graph& other); //Copy C'tor
	~Graph();
	/*-----------------------------------------------------------------------------------*/
	/*---------------------------- Set and insert functions -----------------------------*/
	void setNumOfVertices(int n) { numOfVertices = n; }
	void setNumOfEdges(int m) { numOfEdges = m; }
	void insertToDegreeArray(int v, int val) { degreeArray[v] = val; }
	void insertToParentArray(int v, int parent) { parentArray[v] = parent; }
	/*-----------------------------------------------------------------------------------*/
	/*-------------------------------- Get and functions --------------------------------*/
	int getNumOfVertices() { return numOfVertices; }
	int getNumOfEdges() { return numOfEdges; }
	int getDegreeAtI(int i) { return  degreeArray[i]; }
	int getParentAtI(int i) { return  parentArray[i]; }
	int getFlowOfEdge(int v, int u);
	int getCapacityOfEdge(int v, int u);
	bool getVisitAtI(int i) { return visitedArray[i]; }
	/*-----------------------------------------------------------------------------------*/
	/*--------------------------------- Other functions ---------------------------------*/
	void makeEmptyGraph(int n);
	list<Edge> getAdjList(int u);
	void addEdge(int u, int v, int c);
	void addEdge(int u, int v, int c, int f);
	void removeEdge(int u, int v, int value, char flowOrCapacity);
	void updateFlowOfEdge(int u, int v, int newFlow);
	void updateCapacityOfEdge(int u, int v, int newCapacity);
	void updateVisitedArray(int u, bool visit);
	void removeAllFullEdges(Graph& G);
	/*-----------------------------------------------------------------------------------*/
	/*-------------------------------- Utility functions --------------------------------*/
	bool alreadyExists(int u, int v);
	void printGraph(bool isShiuri);
	/*-----------------------------------------------------------------------------------*/
};