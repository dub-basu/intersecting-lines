#include "EventQueue.h"
#include "LineSegmentIntersector.h"
using namespace std;

/**
*minHeapify to correct the event queue.
*/

//
//template <class T>
//void swap_(T& t12345, T& t2){
//	cout << "swappy" << "\n";
//	T& temp = t12345;
//	t12345 = t2;
//	t2 = temp;
//}


template <class T>
void EventQueue<T>::minHeapify(int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int smallest = i;
	int heapSize = events.size();
	if (left < heapSize and events[left] < events[smallest])
		smallest = left;
	if (right < heapSize and events[right] < events[smallest])
		smallest = right;
	if (smallest != i) {
		swap(events[i], events[smallest]);
		minHeapify(smallest);
	}
}

/**
* Extract the minimum element from the event queue. This also removes the element from queue.
*/
template <class T>
T EventQueue<T>::extractMin() {
	if (events.size() <= 0)
	{
		cerr<<"Empty queue! Aborting!!"<<endl;
		// assert(false);
	}
	else if (events.size() == 1)
	{
		T p=events[0];
		events.pop_back();
		return p;
	}

	T root = events[0];
	swap(events[0], events[events.size() - 1]);
	events.pop_back();
	minHeapify(0);

	return root;
}

/**
* Only peek at the min element without deleting
*/
template <class T>
T EventQueue<T>::peek()
{
	return events[0];
}

/**
* Insert a new event in the event queue.
*/
template <class T>
void EventQueue<T>::insert(T k) {
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
template <class T>
int EventQueue<T>::size(){
	return events.size();
}

// I have no fucking clue why this is needed,
// IT JUST WORKS
template class EventQueue<LineSegmentIntersector::LSIPoint>;

