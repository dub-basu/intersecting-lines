#ifndef STATUS
#define STATUS

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
    void inorder();
    void insert(T);
    void remove(T);
    T* searchL(T);
    T* searchR(T);
};

#endif