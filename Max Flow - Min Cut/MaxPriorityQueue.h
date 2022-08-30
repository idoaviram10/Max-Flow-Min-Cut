#pragma once
#include"Graph.h"

class MaxPriorityQueue
{
private:
	int* places;
	pair<int, int>* heap;
	int maxSize; //Max size of the heap
	int heapSize; //Current size of the heap
	bool allocated; //True if heap allocated memory
	static int Left(int ind);
	static int Right(int ind);
	static int Parent(int ind);
	void FixHeap(int ind);
	void FixHeapUp(int ind);
public:
	/*------------------------------ C'tors and D'tors ----------------------------------*/
	MaxPriorityQueue(Graph& G);
	~MaxPriorityQueue();
	/*-----------------------------------------------------------------------------------*/
	/*------------------------------ Other functions ------------------------------------*/
	void makeEmpty();
	bool isEmpty();
	pair<int, int> max();
	void insert(pair<int, int> newItem);
	void increaseKey(int v, int newKey);
	pair<int, int> deleteMax();
	void mySwap(int ind1, int ind2);
	void printHeap();
	/*-----------------------------------------------------------------------------------*/
};
