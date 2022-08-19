#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

struct node
{
    int data;
    int height;
    node *left;
    node *right;
};

struct qnode
{
	node *n;
	qnode *next;
};

void readFile(node *&root);
struct node * rebalance(struct node *node);
int getBalance(struct node *node);
node * insertNode(node *&root, int data);
struct node *leftRotate(struct node *x);
struct node *rightRotate(struct node *x);
void printLevel(struct node *root);
void enqueue(node *&data, struct qnode *&front, struct qnode *&rear);
int dequeue(struct qnode *&front, struct qnode *&rear);

ifstream in;

int main()
{
    node *root = NULL;

    readFile(root);
    
    printLevel(root);

    cout << endl << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	return 0;
}

void readFile(node *&root)
{
	char tempData[16];
	int tempNum;

    in.open("input.txt");

    while (!in.eof())
    {
        in >> tempData;

		tempNum = atoi(tempData);
		insertNode(root, tempNum);
	}
}

//This is not a recursive algorithm
struct node * rebalance(struct node *node)
{
    //node -> height = max(node -> left -> height, (node -> right -> height + 1));
    int balance = getBalance(node);
    
    cout << ">>" << balance << "<<" << endl;

    /*
        rotation conditions based on balance
       	node right heavy  <-1
                  child is left heavy >0
                       //double rotation  right, left    case  #3
                       node->right=rotate right on child
                       return rotate left on node
                   else
                       return rotate left on node      //single left rotation  case #2
              node is left heavy> 1
                   child is right heavy < 0
                       //double rotation left, right  case #4
                       node->left=rotate left on child
                       return rotate right on node
                    else
                       return rotate right on node   //single right rotation case #1


The numbers in paranthesis are the balance factors
case 1 ============== single right rotation
         5 (2)                          3
      3(1)                            1   5
    1
case 2 =============== left rotation
    5(-2)                            6
      6 (-1)                       5   7
        7

case 3 ===============           right (inside),  left (outside) rotation (Double)
         5 (-2)                 7               7
            8 (1)                 8          5     8
         7
case 4 =============             left (inside),   right (outside) rotation  (Double)
        5(2)                3                 3
    2(-1)               2                  2    5
       3

    */
}

int getBalance(struct node *node)//node->left - node->right
{
	return(node -> left - node -> right);
}

node * insertNode(node *&root, int data)
{
	bool bFoundSpot = false;
	node *newNode = NULL, *leaf = root;

	if(root == NULL)
	{
		newNode = new node;

		newNode -> data = data;
		newNode -> left = NULL;
		newNode -> right = NULL;

		root = newNode;

		return newNode;
	}
	else
	{
        while((leaf != NULL) && (!bFoundSpot))
        {
			if(data == leaf -> data)
				leaf = NULL;
			else if(data < leaf -> data)
			    if(leaf -> left != NULL)
			    	leaf = leaf -> left;
				else
					bFoundSpot = true;
			else
			    if(leaf -> right != NULL)
			        leaf = leaf -> right;
                else
					bFoundSpot = true;
		}
	}

	if(leaf != NULL)
	{
        newNode = new node;

		newNode -> data = data;
		newNode -> left = NULL;
		newNode -> right = NULL;
		newNode -> height = 0;

		if(data < leaf -> data)
		    leaf -> left = newNode;
		else
		    leaf -> right = newNode;

        rebalance(newNode);
		return newNode;
	}
}


struct node *leftRotate(struct node *x)
{
   struct node *y=x->right;
   //add more code to rotate to the left, update heights for x and y
   //return root of the tree
}

struct node *rightRotate(struct node *x)
{
   struct node *y=x->left;
   //add more code to rotate to the right, update heights for x and y
   //return root of the tree
}

void printLevel(struct node *root)
{
	qnode *front = NULL, *rear = NULL;
	node *leaf = root;
	int nextNodes = 0, currentNodes = 0;

	enqueue(root, front, rear);
	currentNodes++;

	while(currentNodes != 0)
	{
		leaf = front -> n;
		cout << dequeue(front, rear);
		currentNodes--;

		if(leaf -> left != NULL)
		{
			enqueue(leaf -> left, front, rear);
			nextNodes++;
		}

		if(leaf -> right != NULL)
		{
			enqueue(leaf -> right, front, rear);
			nextNodes++;
		}

		if(currentNodes == 0)
		{
			currentNodes = nextNodes;
			nextNodes = 0;
			cout << endl;
		}
	}
}


void enqueue(node *&data, struct qnode *&front, struct qnode *&rear)
{
    struct qnode *newNode = new qnode;

    newNode -> n = data;
    newNode -> next = NULL;

    if (rear)
	{
		rear -> next = newNode;
      	rear = newNode;
   	}
   	else
        front = rear = newNode;
}

int dequeue(struct qnode *&front, struct qnode *&rear)
{
    struct qnode *temp;
    int tempData;

	tempData = front -> n -> data;

    if(front)
	{
        temp = front;
        front = front -> next;
        delete temp;
    }

    if(!front)
       	rear = NULL;

	return tempData;
}
