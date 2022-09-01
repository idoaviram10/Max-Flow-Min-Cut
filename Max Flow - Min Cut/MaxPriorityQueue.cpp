#include "MaxPriorityQueue.h"

/*------------------------------ C'tors and D'tors ----------------------------------*/
MaxPriorityQueue::MaxPriorityQueue(Graph& G)
{
	int n = G.getNumOfVertices();
	places = new int[n];
	heap = new pair<int, int>[n];
	maxSize = n;
	heapSize = 0;
	allocated = true;
	for (int v = 1; v <= n; v++)
	{

		heap[v - 1].first = G.getDegreeAtI(v);
		heap[v - 1].second = v;
		places[v - 1] = v - 1;
		heapSize++;
	}

	for (int i = n / 2 - 1; i >= 0; i--)
	{
		FixHeap(i);
	}
}

MaxPriorityQueue::~MaxPriorityQueue()
{
	if (allocated)
	{
		delete[] heap;
		delete[] places;
	}

	heap = nullptr;
	places = nullptr;
}
/*-----------------------------------------------------------------------------------*/

/*------------------------------ Private functions ----------------------------------*/
int MaxPriorityQueue::Left(int ind)
{
	return (2 * ind + 1);
}

int MaxPriorityQueue::Right(int ind)
{
	return (2 * ind + 2);
}

int MaxPriorityQueue::Parent(int ind)
{
	return (ind - 1) / 2;
}

void MaxPriorityQueue::FixHeap(int ind) {
	int max;
	int left = Left(ind);
	int right = Right(ind);

	if (left < heapSize && heap[left].first > heap[ind].first)
		max = left;
	else
		max = ind;

	if (right < heapSize && heap[right].first > heap[max].first)
		max = right;

	if (max != ind) {
		mySwap(ind, max);
		FixHeap(max);
	}
}

void MaxPriorityQueue::FixHeapUp(int ind)
{
	while ((ind > 0) && heap[Parent(ind)].first < heap[ind].first)
	{
		mySwap(ind, Parent(ind));
		ind = Parent(ind);
	}
}
/*-----------------------------------------------------------------------------------*/


void MaxPriorityQueue::makeEmpty()
{
	if (allocated)
	{
		delete[] heap;
		delete[] places;
	}

	places = new int[maxSize];
	heap = new pair<int, int>[maxSize];
	allocated = true;
	heapSize = 0;
}

bool MaxPriorityQueue::isEmpty()
{
	if (heapSize == 0)
		return true;
	return false;
}

pair<int, int> MaxPriorityQueue::max()
{
	return heap[0];
}

void MaxPriorityQueue::insert(pair<int, int> newItem)
{
	if (heapSize == maxSize)
		exit(1);

	int i = heapSize;
	heapSize++;

	// Fix heap up
	while (i > 0 && heap[Parent(i)].first < newItem.first)
	{
		heap[i] = heap[Parent(i)];
		i = Parent(i);
	}

	heap[i] = newItem;
}

void MaxPriorityQueue::increaseKey(int v, int newKey)
{
	int i = places[v - 1];
	if (heap[i].first < newKey)
	{
		heap[i].first = newKey;
		FixHeapUp(i);
	}
}

pair<int, int> MaxPriorityQueue::deleteMax()
{
	if (heapSize < 1)
		exit(1);

	pair<int, int> max = heap[0];
	heapSize--;
	heap[0] = heap[heapSize];
	FixHeap(0);

	return max;
}

void MaxPriorityQueue::mySwap(int ind1, int ind2)
{
	int u = heap[ind1].second;
	int v = heap[ind2].second;
	places[u - 1] = ind2;
	places[v - 1] = ind1;
	pair<int, int> tempPair = heap[ind1];
	heap[ind1] = heap[ind2];
	heap[ind2] = tempPair;
}

void MaxPriorityQueue::printHeap()
{
	for (int i = 0; i < maxSize; i++)
	{
		cout << i << ". (" << heap[i].second << "," << heap[i].first << ")" << "\t" << heap[i].second << " is #" << places[heap[i].second - 1] + 1 << " in heap arr" << endl;
	}
}