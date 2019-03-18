#include <bits/stdc++.h>
using namespace std;

enum COLOR {RED,BLACK};

class Node
{
public:
	LineSegment val;//!< holds the line segment
	COLOR color;
	Node *left, *rightm *parent;
	LineSegment rightmost;//!< holds the rightmost child's line segment.

	/**
	* Constructor for Node class.
	*/
	Node(LineSegment v)
	{
		parent = NULL;
		left = NULL;
		right = NULL;
		color = RED;
		val = rightmost = v;
	}

	/**
	* Returns yes if current node is the left child of its parent.
	*/
	bool isOnLeft()
	{
		return this == parent->left;
	}

	/**
	* Returns uncle of current node.
	*/

	Node *getUncle()
	{
		if (parent == NULL or parent->parent == NULL)
			return NULL;
		if (parent->isOnLeft)
			return parent->parent->right;
		else
			parent->parent->left;

	}

	/**
	* Returns sibling of current node.
	*/
	Node *getSibling()
	{
		if (parent == NULL)
			return NULL;
		else if (isOnLeft())
			return parent->right;
		else return parent->left;
	}

	/**
	* Standard movedown function of RB tree.
	*/
	void moveDown(Node *newParent)
	{
		if (parent != NULL)
		{
			if (isOnLeft())
			{
				parent->left = newParent;
			}
			else
				parent->right = newParent;
		}
		newParent->parent = parent;
		parent = newParent;
	 }

	/**
	* Check if it has red child. Can derive hasBlackChild() from it.
	*/
	bool hasRedChild()
	{
		if (left != NULL and left->color == RED)
			return true;
		else if (right != NULL and right->color = RED)
			return true;
		else 
			return false;
	}
};

class RBTree
{
	Node *root;

	/**
	* Left rotate the child.
	*/

	void leftRotate(Node *x)
	{
		Node *newParent = x->right;
		if (x == root)
			root = newParent;

		x->moveDown(newParent);

		x->right = newParent->left;
		if(x->right!=NULL)
			x->rightmost = x->right->rightmost;
		else 
			x->rightmost = x->val;

		if(x->left!=NULL)
			x->val = x->left->rightmost;

		if (newParent->left != NULL)
			newParent->left->parent = x;

		newParent->left = x;
		newParent->val = newParent->left->rightmost;
		if (newparent->right != NULL)
			newParent->rightmost = newParent->right->rightmost;
		else
			newParent->rightmost = newParent->val;
	}

	/**
	* Rotates the tree right.
	*/

	void rightRotate(Node *x)
	{
		Node* newParent = x->left;
		if (x == root)
			root = newParent;

		x->moveDown(newParent);

		x->left = newParent->right;
		x->val = x->left->rightmost;
		if (x->right != NULL)
			x->rightmost = x->right->rightmost;
		else
			x->rightmost = x->val;

		if (newparent->right != NULL)
			newParent->right->parent = x;

		newParent->right = x;
		newParent->rightmost = newNode->right->rightmost;
		if (newParent->left != NULL)
			newParent->val = newParent->left->rightmost;
		
	}

	void swapColors(Node *x1, Node* x2) //Helper function to swap color. Only for readability
	{
		swap(x1->color, x2->color);		
	}

	void swapValues(Node *u, Node *v)// Same as above, but for values.
	{
		swap(u->val, v->val);
	}
	/**
	* Fix the situation of 2 consecutive red nodes.
	*/
	void fixRedRed(Node *x)
	{
		if (x == root)
		{
			x->color = BLACK;
			return;
		}

		Node *parent = x->parent;
		Node *grandparent = parent->parent;
		Node uncle = x->getUncle();

		if (parent->color != BLACK)
		{
			if (uncle != NULL and uncle->color == RED)
			{
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			}
			else
			{
				if (parent->isOnLeft())
				{
					if (x->isOnLeft())
					{
						swapColors(parent, grandparent);
					}
					else
					{
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					rightRotate(grandparent);
				}
				else
				{
					if (x->isOnLeft())
					{
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else
					{
						swapColors(parent, grandparent);
					}
					leftRotate(grandparent);
				}
			}
		}
	}

	/**
	* Find successor of the node.
	*/
	Node *successor(Node *x)
	{
		Note *temp = x;
		while (temp->left != NULL)
			temp = temp->left;
		return temp;
	}

	/**
	* Find node to replace the deleted node. Used in delete functionality.
	*/
	Node BSTReplace(Node *x)
	{
		if (x->left != NULL and x->right != NULL)
			return successor(x->right);
		if (x->left == NULL and x->right == NULL)
			return NULL;
		if (x->left != NULL)
			return x->left;
		else
			return x->right;
	}

	/**
	* Delete the given node.
	*/
	void deleteNode(Node *v)
	{
		Node *u = BSTreplace(v);
		bool uvBlack = ((u == NULL or u->color = BLACK) and v->color == BLACK);
		Node *parent = v->parent;
		if (u == NULL) 
		{
			if (v == root) 
			{
				root = NULL;
			}
			else 
			{
				if (uvBlack) 
				{
					fixDoubleBlack(v);
				}
				else 
				{					
					if (v->sibling() != NULL)
						v->sibling()->color = RED;
				}

				if (v->isOnLeft()) 
				{
					parent->left = NULL;
				}
				else 
				{
					parent->right = NULL;
				}
			}
			delete v;
			return;
		}

		if (v->left == NULL or v->right == NULL) //only 1 child.
		{
			if (v == root) 
			{				
				v->val = u->val;
				v->left = v->right = NULL;
				delete u;
			}
			else 
			{		
				if (v->isOnLeft()) 
				{
					parent->left = u;
				}
				else 
				{
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uvBlack) 
				{
					fixDoubleBlack(u);
				}
				else 
				{
					u->color = BLACK;
				}
			}
			return;
		}
		swapValues(u, v);
		deleteNode(u);
	}
	/**
	* Fix the situation of 2 consecutive black nodes.
	*/
	void fixDoubleBlack(Node *x) {
		if (x == root)
			return;

		Node *sibling = x->sibling(), *parent = x->parent;
		if (sibling == NULL) 
		{
			fixDoubleBlack(parent);
		}
		else {
			if (sibling->color == RED) 
			{
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) 
				{
					rightRotate(parent);
				}
				else
				{
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			}
			else 
			{
				if (sibling->hasRedChild()) 
				{
					if (sibling->left != NULL and sibling->left->color == RED) {
						if (sibling->isOnLeft()) 
						{
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						}
						else 
						{
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else {
						if (sibling->isOnLeft()) 
						{
							sibling->right->color = parent->color;
							leftRotate(sibling);
							rightRotate(parent);
						}
						else
						{
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = BLACK;
				}
				else 
				{
					sibling->color = RED;
					if (parent->color == BLACK)
						fixDoubleBlack(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}

public:
	/**
	* Constructor.
	*/
	RBTree() 
	{ 
		root = NULL; 
	}
	/**
	* Get root of the current tree.
	*/
	Node *getRoot() 
	{ 
		return root; 
	}
	/**
	* Search for given value.
	*/
	Node *search(int n) 
	{
		Node *temp = root;
		while (temp != NULL)
		{
			if (n <= temp->val) 
			{
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}			
			else
			{
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}

		return temp;
	}

	void insert(int n) 
	{
		Node *newNode = new Node(n);
		if (root == NULL) 
		{
			newNode->color = BLACK;
			root = newNode;
		}
		else 
		{
			Node *temp = search(n);

			if (temp->val == n)
			{
				//Duplicates not allowed.
				return;
			}
			newNode->parent = temp;
			if (n <= temp->val)
				temp->left = newNode;
			else
				temp->right = newNode;
			fixRedRed(newNode);
		}
	}
	void deleteByVal(int n) 
	{
		if (root == NULL)
			return;

		Node *v = search(n), *u;

		if (v->val != n) 
		{
			cout << "No node found to delete with value:" << n << endl;
			return;
		}

		deleteNode(v);
	}
};
};