#include<bits/stdc++.h>

using namespace std;

//NO MAIN FUNCTION IN THIS FILE.

//Delete below point class for compatibility.
struct Point
{
    int x,y;
};

class Event
{
    public:
	Point p; //!< Concerned point/co-ord on which we will operate

	/*! \brief Overloading the < operator
	 *
	 *  < operator overloaded here to be used in heap. This allows directly comparing 2 events with this operator in required fashion.
	 */

	bool operator < (const Event y)
	{
		return p.x < y.p.x or (p.x == y.p.x and p.y < y.p.y);
	}
};

class EventQueue
{
	vector <Event> events; //!< Stores all the event points the sweep line intersects.

public:

	/**
	*minHeapify to correct the event queue.
	*/
	void minHeapify(int i)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int smallest = i;
		int heapSize = events.size();
		if (left < heapSize and events[left] < events[smallest])
			smallest = left;
		if (right < heapSize and events[right] < events[smallest])
			smallest = right;
		if (smallest != i)
		{
			swap(events[i], events[smallest]);
			minHeapify(smallest);
		}
	}

	/**
	* Extract the minimum element from the event queue. This also removes the element from queue.
	*/

	Event extractMin()
	{
		if (events.size() <= 0)
		{
			cerr<<"Empty queue! Aborting!!"<<endl;
			assert(false);
		}
		else if (events.size() == 1)
        {
            Event p=events[0];
            events.pop_back();
            return p;
        }

		Event root = events[0];
		swap(events[0], events[events.size() - 1]);
		events.pop_back();
		minHeapify(0);

		return root;
	}

	/**
	* Only peek at the min element without deleting
	*/
	Event peek()
	{
		return events[0];
	}

	/**
	* Insert a new event in the event queue.
	*/

	void insert(Event k)
	{
		events.push_back(k);

		int i = events.size() - 1;
		while (i != 0 and events[i] < events[(i - 1) >> 1] ) // if Parent has more value than child
		{
			swap(events[i], events[(i - 1) >> 1]);
			i = (i - 1) >> 1;
		}
	}

	/**
	* Get size of the heap.
	*/
	int size()
	{
		return events.size();
	}

};
