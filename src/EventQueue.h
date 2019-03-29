#ifndef EVENT_QUEUE
#define EVENT_QUEUE
#include<vector>

using namespace std;

/**
 * The event queue is a min heap
 * @tparam T class needs < function and defined
 */
template <class T>
class EventQueue
{
	vector <T> events; //!< Stores all the event points the sweep line intersects.
	/**
	* minHeapify to correct the event queue.
	*/
	void minHeapify(int i);

public:

	/**
	 * Extract the minimum element from the event queue.
	 * This also removes the element from queue.
	 * @return min element in the heap
	 */
	T extractMin();

	/**
	 *
	 * @return
	 */
	T peek();


	/**
	 * Insert a new event in the event queue.
	 * @param element to insert
	 */
	void insert(T k);

	/**
	 * Get size of the heap.
	 * @return number of elements in the event queue
	 */
	int size();

};

#endif