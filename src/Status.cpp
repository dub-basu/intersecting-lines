#include "Status.h"
#include "LineSegmentIntersector.h"
using namespace std;

/**
* Get height of the current node.
*/
template<class T>
int Status<T>::height(Node *n)
{
	if (n == NULL)
		return 0;
	else return n->height;
}

/**
* Constructor for a new node.
*/
template<class T>
typename Status<T>::Node* Status<T>::newNode(T key){
	Node* node = (Node *)malloc(sizeof(Node));
	node->left = node->right = NULL;
	node->height = 1;//!< Added at leaf initially.
	node->key = key;
	node->rightmost=key;
	return node;
}

/**
* Performs right rotation
*/
template<class T>
typename Status<T>::Node* Status<T>::rightRotate(Node *y){
	Node *x = y->left;
	Node *t2 = x->right;

	x->right = y;
	y->left = t2;

	//Update heights
	y->height = max(height(y->left), height(y->right)) + 1; //!< height is 1+max possible heights possible by both subtrees.
	x->height = max(height(x->right), height(x->left)) + 1;

	return x;
}

/**
* Left rotate a tree.
*/
template<class T>
typename  Status<T>::Node* Status<T>::leftRotate(Node *x)
{
    //cout<<"Left"<<endl;
	Node *y = x->right;
	Node *t2 = y->left;

	//Rotate now!!
	y->left = x;
	x->right = t2;
	x->height = max(height(x->right), height(x->left)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

/**
* Get balance paramenter for Node N.
*/
template <class T>
int Status<T>::getBalance(Node *n)
{
	if (n == NULL)return 0;
	else return height(n->left) - height(n->right);
}

/**
* Check if given node is leaf.
*/
template <class T>
bool Status<T>::checkLeaf(Node *n)
{
    if(n==NULL)return false;
    return (n->right==n->left and n->left==NULL and n->rightmost==n->key);
}
/**
* Insert into AVL node
*/
template <class T>
typename Status<T>::Node* Status<T>::__insert(Node* node, T key) {
    int left=0;
	if (node == NULL)
		return newNode(key);
	if (key < node->key)
    {
        node->left = __insert(node->left, key),++left;
    }

	else if (key > node->key)
    {
        node->right = __insert(node->right, key),--left;
    }
	else
		return node; //!< We are not allowing duplicates

	node->height = 1 + max(height(node->left), height(node->right));
	int bal = getBalance(node);

	if (bal > 1 and key < node->left->key)
		return rightRotate(node);
	else if (bal < -1 and key> node->right->key)
		return leftRotate(node);
	else if (bal > 1 and key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	else if (bal < -1 and key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

/**
* Get leftmost leaf of the tree.
*/
template <class T>
typename Status<T>::Node* Status<T>::minValueNode(Node *node)
{
	Node *current = node;
	while (current->left != NULL)current = current->left;
	return current;
}
template <class T>
typename Status<T>::Node* Status<T>::__remove(Node* root, T key){
    int left=0;
	if (root == NULL)return root;
	if (key < root->key)
    {
        root->left = __remove(root->left, key),left++;
    }
	else if (key > root->key)
    {
        root->right = __remove(root->right, key),left--;
    }
	else

	{
	    if(key!= root->key and checkLeaf(root))return root;
		if (root->left == NULL or root->right == NULL)
		{
			Node *temp = root->left ? root->left : root->right;
			if (temp == NULL)//Node is a leaf
			{
				temp = root;
				root = NULL;

			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = __remove(root->right, temp->key);
		}
	}

	if (root == NULL)return root;

	root->height = 1 + max(height(root->left), height(root->right));
	int bal = getBalance(root);

	if (bal > 1 and getBalance(root->left) >= 0)
		return rightRotate(root);
	else if (bal > 1 and getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	else if (bal < -1 and getBalance(root->right) <= 0)
		return leftRotate(root);
	else if (bal < -1 and getBalance(root->right)>0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

template <class T>
void Status<T>::__inorder(typename Status<T>::Node *n){
	if (n != NULL){
		__inorder(n->left);
		cout << n->key << " ";
		__inorder(n->right);
	}
}

/**
* Search the tree for left sibling of node with value key.
*/
template <class T>
T* Status<T>::searchL(T key){
    Node *curr=root;
    while(curr->left != NULL)
    	curr = curr->left;
    if(curr->key == key)
    	return NULL;

    Node *ans = newNode(curr->key);
    curr = root;


    while(curr != NULL)
    {
        if(curr->key<key and ans->key <=curr->key)
            ans=curr;
        if(key <= curr->key)
            curr=curr->left;
        else
            curr=curr->right;
    }
    return &(ans->key);
}

/**
* Search the tree for right sibling of node with value key.
*/
template <class T>
T* Status<T>::searchR(T key)
{
    Node *curr=root;
	while(curr->right != NULL)
		curr = curr->right;
	if (curr->key == key)
		return NULL;

	Node *ans = newNode(curr->key);
	curr = root;
    while(curr != NULL)
    {
        if(curr->key>key and curr->key <ans->key)
            ans=curr;
        if(key < curr->key)
            curr=curr->left;
        else
            curr=curr->right;
    }
    return &(ans->key);
}

template <class T>
void Status<T>::inorder() {
	__inorder(root);
}

template <class T>
void Status<T>::insert(T key) {
	root = __insert(root, key);
}

template <class T>
void Status<T>::remove(T key){
	root = __remove(root, key);
}

template <class T>
T* Status<T>::getRoot(){
	if(root == NULL) return NULL;
	else return &(root->key);
}
// Another instance of me not knowing wtf is happening;
template class Status<LineSegmentIntersector::LSISegment>;
template class Status<int>;