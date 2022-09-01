/*---------------------------------------------------------*/
/*                Ford-Fulkerson Algorithm                 */
/*                                                         */
/*                 Oshri Fadlon 208437046                  */
/*                  Ido Aviram 318599834                   */
/*---------------------------------------------------------*/


#include <limits.h>
#include "Graph.h"
#include "MaxPriorityQueue.h"



/*----------------------------------------- Explanation for running the program: -------------------------------------------------*/
// - First, you must enter an integer (n) that represents the number of vertices in the graph.
// - Then, an integer (m) that represents the number of edges in the graph.
// - After that, two numbers must be inserted (each in a separate line), 
//   the first number represents the starting vertex of the algorithm and the second number represents the ending vertex.
// - Finally, m triples (the number of edges inserted earlier) must be taken in, each triple in a separate line, 
//   where each triple is built like this:
//   First number - origin vertex of the edge, second number - end vertex of the edge and third number - the capacity of the edge.
/*---------------------------------------------------------------------------------------------------------------------------------*/


#define BFS 'B'
#define DIJKSTRA 'D'

/*----------------- All the functions we will use in this program: ------------------*/
void fordFulkerson(Graph& G, int s, int t, char alg);
bool isPathFromVToU(Graph& G, int v, int u);
void BFSAlgorithm(Graph& G, int v);
void DijkstraAlgorithm(Graph& G, int s);
void init(Graph& G, int s, char alg);
void printResult(int maxFlow, Graph& G);
bool isBetween(int numToCheck, int small, int big);
/*-----------------------------------------------------------------------------------*/

constexpr static int infinity = INT_MAX; // Set infinity to the maximum integer.

int main()
{
	int numOfVertices = 0, numOfEdges = 0;
	int startVer_S, endVer_T;
	int fromVer, toVer, weightVer;
	try
	{
		cin >> numOfVertices;
		cin >> numOfEdges;

		if (!(numOfVertices >= 0 && numOfEdges >= 0))
			throw "error";

		Graph GBFS(numOfVertices, numOfEdges);
		Graph GDijkstra(numOfVertices, numOfEdges);

		cin >> startVer_S;
		cin >> endVer_T;

		if (!(isBetween(startVer_S, 1, numOfVertices) && isBetween(endVer_T, 1, numOfVertices)))
			throw "error";

		for (int i = 0; i < numOfEdges; i++)
		{
			cin >> fromVer;

			cin >> toVer;

			cin >> weightVer;

			if (!(isBetween(fromVer, 1, numOfVertices) && isBetween(toVer, 1, numOfVertices) && weightVer >= 0))
				throw "error";

			if (GBFS.alreadyExists(fromVer, toVer))
			{
				GBFS.removeEdge(fromVer, toVer, 0, 'c');
				GBFS.addEdge(fromVer, toVer, weightVer, 0);

				GDijkstra.removeEdge(fromVer, toVer, 0, 'c');
				GDijkstra.addEdge(fromVer, toVer, weightVer, 0);
			}
			else
			{
				GBFS.addEdge(fromVer, toVer, weightVer, 0);
				GBFS.addEdge(toVer, fromVer, 0, 0);
				GDijkstra.addEdge(fromVer, toVer, weightVer, 0);
				GDijkstra.addEdge(toVer, fromVer, 0, 0);
			}
		}

		fordFulkerson(GBFS, startVer_S, endVer_T, BFS);
		fordFulkerson(GDijkstra, startVer_S, endVer_T, DIJKSTRA);
	}

	catch (...)
	{
		cout << "invalid input";
	}

	return 0;
}

void fordFulkerson(Graph& G, int s, int t, char alg)
{
	int u, v;
	int maxFlow = 0, pathFlow = infinity;

	Graph rG(G); // Copy G to the Residual Graph.

	if (alg == BFS)
		BFSAlgorithm(rG, s);
	else
		DijkstraAlgorithm(rG, s);


	while (isPathFromVToU(rG, s, t))
	{ // Find the minimum capacity in the path.
		pathFlow = infinity;

		for (v = t; v != s; v = rG.getParentAtI(v))
		{
			u = rG.getParentAtI(v);
			pathFlow = min(pathFlow, rG.getCapacityOfEdge(u, v));
		}

		if (pathFlow != -1)
		{ // Update the flow.

			for (v = t; v != s; v = rG.getParentAtI(v))
			{
				u = rG.getParentAtI(v);
				G.updateFlowOfEdge(u, v, G.getFlowOfEdge(u, v) + pathFlow);
				if (rG.alreadyExists(v, u))
					G.updateFlowOfEdge(v, u, -G.getFlowOfEdge(u, v));
			}

			for (v = t; v != s; v = rG.getParentAtI(v))
			{
				u = rG.getParentAtI(v);
				rG.updateCapacityOfEdge(u, v, G.getCapacityOfEdge(u, v) - G.getFlowOfEdge(u, v));
				if (rG.alreadyExists(v, u))
				{
					rG.updateCapacityOfEdge(v, u, G.getCapacityOfEdge(v, u) - G.getFlowOfEdge(v, u));
				}
			}

			maxFlow += pathFlow; // Add path flow to the overall flow.

			rG.removeAllFullEdges(G); // Remove all full flow edge
		}

		if (alg == BFS)
			BFSAlgorithm(rG, s);
		else
			DijkstraAlgorithm(rG, s);

	}
	if (alg == BFS)
	{
		cout << "BFS Method:" << endl;
		printResult(maxFlow, rG);
	}
	else
	{
		cout << "Greedy Method:" << endl;
		printResult(maxFlow, rG);
	}

}

bool isPathFromVToU(Graph& G, int u, int v)
{
	int currParentVer = G.getParentAtI(v);
	while (currParentVer != -1)
	{
		if (currParentVer == u)
			return true;

		currParentVer = G.getParentAtI(currParentVer);
	}
	return false;
}

void BFSAlgorithm(Graph& G, int v)
{
	queue<int> Q;
	int u;
	list<Edge> adjList;

	init(G, v, BFS);

	Q.push(v);

	while (!Q.empty())
	{
		u = Q.front();
		Q.pop();

		adjList = G.getAdjList(u);

		for (auto x : adjList)
		{
			if (G.getDegreeAtI(x.vertex) == infinity && x.capacity != 0)
			{
				G.insertToDegreeArray(x.vertex, G.getDegreeAtI(u) + 1);
				G.insertToParentArray(x.vertex, u);
				Q.push(x.vertex);
				G.updateVisitedArray(x.vertex, true);
			}
		}
	}
}

void DijkstraAlgorithm(Graph& G, int s)
{
	pair<int, int> currMax(0, 0);
	int newDist = 0;

	init(G, s, DIJKSTRA);

	MaxPriorityQueue mpq(G);

	while (!mpq.isEmpty())
	{
		currMax = mpq.deleteMax();

		if (G.getDegreeAtI(currMax.second) == (-infinity))
			break;

		for (auto v : G.getAdjList(currMax.second))
		{
			G.updateVisitedArray(currMax.second, true);
			if (v.capacity != 0)
			{
				newDist = max(G.getDegreeAtI(v.vertex), min(G.getDegreeAtI(currMax.second), v.capacity));

				if (newDist > G.getDegreeAtI(v.vertex))
				{
					G.insertToDegreeArray(v.vertex, newDist);
					G.insertToParentArray(v.vertex, currMax.second);
					mpq.increaseKey(v.vertex, newDist);
				}
			}
		}
	}

}

void init(Graph& G, int v, char alg)
{
	for (int i = 1; i <= G.getNumOfVertices(); i++)
	{
		if (alg == BFS)
			G.insertToDegreeArray(i, infinity);
		else // (alg == DIJKSTRA)
			G.insertToDegreeArray(i, -(infinity));
		G.insertToParentArray(i, -1);
		G.updateVisitedArray(i, false);
	}

	if (alg == BFS)
		G.insertToDegreeArray(v, 0);
	else // (alg == DIJKSTRA)
		G.insertToDegreeArray(v, infinity);
	G.insertToParentArray(v, -1);
	G.updateVisitedArray(v, true);
	
}

void printResult(int maxFlow, Graph& G)
{
	vector<int> S, T;

	cout << "Max flow = " << maxFlow << endl;

	for (int i = 1; i <= G.getNumOfVertices(); i++)
	{
		if (G.getVisitAtI(i))
			S.push_back(i);
		else
			T.push_back(i);
	}

	cout << "Min cut: S = ";
	for (int i = 0; i < S.size(); i++)
	{
		cout << S[i];
		if (i < S.size() - 1)
			cout << ", ";
	}
	cout << ". ";
	cout << "T = ";
	for (int i = 0; i < T.size(); i++)
	{
		cout << T[i];
		if (i < T.size() - 1)
			cout << ", ";
	}
	cout << endl;
}

bool isBetween(int numToCheck, int small, int big)
{
	return (small <= numToCheck && numToCheck <= big);
}


/*--------------------------------------- Tests -------------------------------------*/
/*
Max flow = 24
S = {1,2,3,4,5} T = {6}

6
11
1
6
1 2 16
1 3 13
2 3 10
3 2 4
2 4 12
4 3 9
3 5 14
5 4 7
5 6 4
4 6 20
3 4 3
*/
/*-----------------------------------------------------------------------------------*/