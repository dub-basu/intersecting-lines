#include <bits/stdc++.h>
using namespace std;
#define LineSegment pair<int,int>

/**
* Defining Node to have value, left & right children and height &etc.
*/
struct Node
{
	LineSegment key;
	Node *left;
	Node *right;
	Node *parent;
    LineSegment rightmost;
	int height;
};

/**
* Get height of the current node.
*/
int height(Node *n)
{
	if (n == NULL)
		return 0;
	else return n->height;
}

/**
* Constructor for a new node.
*/

Node* newNode(LineSegment key)
{
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

Node* rightRotate(Node *y)
{
    //cout<<"Right"<<endl;
	Node *x = y->left;
	Node *t2 = x->right;

	//Rotate now.
	x->right = y;
	y->left = t2;

	//Update heights.
	y->height = max(height(y->left), height(y->right)) + 1; //!< height is 1+max possible heights possible by both subtrees.
	x->height = max(height(x->right), height(x->left)) + 1;
	//Update node invariants for rightmost property.
	/*
	if(y->right!=NULL)
        y->rightmost=y->right->rightmost;
    if(y->left!=NULL)
        y->key=y->left->rightmost;
    if(x->right!=NULL)
        x->rightmost=x->right->rightmost;
    if(x->left!=NULL)
        x->key=x->left->rightmost;
    */

	return x;
}

/**
* Left rotate a tree.
*/

Node *leftRotate(Node *x)
{
    //cout<<"Left"<<endl;
	Node *y = x->right;
	Node *t2 = y->left;

	//Rotate now!!
	y->left = x;
	x->right = t2;
	x->height = max(height(x->right), height(x->left)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

    /*
	if(y->right!=NULL)
        y->rightmost=y->right->rightmost;
    if(y->left!=NULL)
        y->key=y->left->rightmost;
    if(x->right!=NULL)
        x->rightmost=x->right->rightmost;
    if(x->left!=NULL)
        x->key=x->left->rightmost;
    */


	return y;
}

/**
* Get balance paramenter for Node N.
*/

int getBalance(Node *n)
{
	if (n == NULL)return 0;
	else return height(n->left) - height(n->right);
}

/**
* Check if given node is leaf.
*/
bool checkLeaf(Node *n)
{
    if(n==NULL)return false;
    return (n->right==n->left and n->left==NULL and n->rightmost==n->key);
}
/**
* Insert into AVL node
*/
Node *insert(Node* node, LineSegment key)
{
    int left=0;
	if (node == NULL)
		return newNode(key);
	if (key < node->key)
    {
        node->left = insert(node->left, key),++left;
    }

	else if (key > node->key)
    {
        node->right = insert(node->right, key),--left;
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

Node* minValueNode(Node *node)
{
	Node *current = node;
	while (current->left != NULL)current = current->left;
	return current;
}

Node *deleteNode(Node* root, LineSegment key)
{
    int left=0;
	if (root == NULL)return root;
	if (key < root->key)
    {
        root->left = deleteNode(root->left, key),left++;
    }
	else if (key > root->key)
    {
        root->right = deleteNode(root->right, key),left--;
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
            root->right = deleteNode(root->right, temp->key);
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

void inorder(Node *n)
{
	if (n != NULL)
	{
		inorder(n->left);
		cout << n->key.first << "-" << n->key.second << " ";
		inorder(n->right);
	}
}

/**
* Search the tree for left sibling of node with value key.
*/

Node *searchL(Node *root,LineSegment key)
{
    //cout<<"In the func!!"<<endl;
    Node *curr=root;
    /*Replace below code with appropriate constructor for min line seg*/
    LineSegment mini;
    mini.first=mini.second=INT_MIN;
    Node *ans = newNode(mini);
    /*Till here needs to be replaced.*/
    //cout<<"Starting loop!!"<<endl;
    while(curr != NULL)
    {
        cout<<"Curr="<<curr->key.first<<" "<<curr->key.second<<endl;
        if(curr->key<key and ans->key <=curr->key)
            ans=curr;
        if(key <= curr->key)
            curr=curr->left;
        else
            curr=curr->right;
    }
    return ans;
}

/**
* Search the tree for right sibling of node with value key.
*/

Node *searchR(Node *root,LineSegment key)
{
    Node *curr=root;
    /*Replace below code with appropriate constructor for min line seg*/
    LineSegment mini;
    mini.first=mini.second=INT_MAX;
    Node *ans = newNode(mini);
    /*Till here needs to be replaced.*/
    while(curr != NULL)
    {
        if(curr->key>key and curr->key <ans->key)
            ans=curr;
        if(key < curr->key)
            curr=curr->left;
        else
            curr=curr->right;
    }
    return ans;
}

int main()
{
	Node *root = NULL;
	LineSegment temp;
	while (true)
	{
		cin >> temp.first >> temp.second;
		if (temp.first == -1)break;
		root=insert(root, temp);
		cout << "Inorder Trversal: ";
		inorder(root);
		cout<<endl;
	}

	while (true)
	{
		cin >> temp.first >> temp.second;
		if (temp.first == -1)break;
		root=deleteNode(root, temp);
		cout << "Inorder Trversal(Deletion): ";
		inorder(root);
		cout<<endl;
	}

	while(true)
    {
        cout<<"Which node to search?"<<endl;
        cin>>temp.first>>temp.second;
        if(temp.first==-1)break;
        Node *leftN= searchL(root,temp);
        Node *rightN=searchR(root,temp);
        cout<<"L Sibl. = "<<leftN->key.first<<"-"<<leftN->key.second<<endl;
        cout<<"R Sibl. = "<<rightN->key.first<<"-"<<rightN->key.second<<endl;
    }

	return 0;
}
