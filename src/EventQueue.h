#include<bits/stdc++.h>

using namespace std;

struct Point {
int x,y;
};
class Event
{
    public:
	Point p;
	bool operator < (const Event y);

};

class EventQueue
{
	vector <Event> events; //!< Stores all the event points the sweep line intersects.

public:

	/**
	*minHeapify to correct the event queue.
	*/
	void minHeapify(int i);

	/**
	* Extract the minimum element from the event queue. This also removes the element from queue.
	*/

	Event extractMin();

	Event peek();


	/**
	* Insert a new event in the event queue.
	*/

	void insert(Event k);

	/**
	* Get size of the heap.
	*/
	int size();

};
