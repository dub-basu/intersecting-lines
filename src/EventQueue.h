#ifndef EVENT_QUEUE
#define EVENT_QUEUE
#include<vector>

using namespace std;

template <class T>
class EventQueue
{
	vector <T> events; //!< Stores all the event points the sweep line intersects.

public:
	/**
	*minHeapify to correct the event queue.
	*/
	void minHeapify(int i);

	/**
	* Extract the minimum element from the event queue. This also removes the element from queue.
	*/

	T extractMin();

	T peek();


	/**
	* Insert a new event in the event queue.
	*/

	void insert(T k);

	/**
	* Get size of the heap.
	*/
	int size();

};

#endif