#ifndef STATUS
#define STATUS
/**
 * Status is a balanced tree, that allows for neighbour search
 * @tparam T : template class for which you want to build the status
 */
template <class T>
class Status {
private:
    /**
    * Internal node of the tree
    */
    typedef struct Node{
        T key;
        Node* left;
        Node* right;
        Node* parent;
        T rightmost;
        int height;
    } Node;
    Node *root= nullptr;
    Node* newNode(T key);
    Node* rightRotate(Node* );
    Node* leftRotate(Node* );
    int height(Node* );
    int getBalance(Node*);
    void __inorder(Node*);
    bool checkLeaf(Node*);
    Node* __insert(Node*, T);
    Node* minValueNode(Node*);
    Node* __remove(Node*, T);

public:
    /**
     * Prints inorder traversal
     * Requires that operator<< for ostream be
     * overloaded for < T > class
     */
    void inorder();
    /**
     * Insert an element into the tree
     * @param element to insert
     */
    void insert(T);

    /**
     * Removes element from tree
     * Does nothing is element is not present
     */
    void remove(T);

    /**
     * Searches for element to the left of the param
     * Returns null if no neighbour exists
     * If param doesnt exist, we search for the smallest element
     * greater than it
     * @param : Element who's left neighbour we want to search for
     */
    T* searchL(T);

    /**
     * Searches for element to the right of the param
     * Returns null if no neighbour exists
     * If param doesnt exist, we search for the smallest element
     * greater than it
     * @param : Element who's right neighbour we want to search for
     */
    T* searchR(T);

};

#endif