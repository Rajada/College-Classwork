#include <fstream>
#include <iostream>

using namespace std;

ifstream in;

struct treeNode
{
	int data;
	treeNode *left;
	treeNode *right;
};

struct node
{
	treeNode *tn;
	node *next;
};

void readFile(treeNode *&root);
treeNode * insertNode(treeNode *&root, int data);
void deleteNode(treeNode *&root, int data);
void preOrder(struct treeNode *root);
void inOrder(struct treeNode *root);
void postOrder(struct treeNode *root);
void printLevel(struct treeNode *root);
void enqueue(treeNode *&data, struct node *&front, struct node *&rear);
int dequeue(struct node *&front, struct node *&rear);

int main()
{
	treeNode *root = NULL;

    readFile(root);

	cout << endl << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}

void readFile(treeNode *&root)
{
	char tempData[16];
	int tempNum;

    in.open("input.txt");

    while (!in.eof())
    {
        in >> tempData;

        if(strcmp(tempData, "delete") == 0)
        {
			in >> tempNum;
			deleteNode(root, tempNum);
			cout << "<<<<<<<<<<<<<<<<<<<<<<PRE>>>>>>>>>>>>>>>>>>>>>>" << endl;
			preOrder(root);
    		cout << endl << endl;
    		cout << "<<<<<<<<<<<<<<<<<<<<<<IN>>>>>>>>>>>>>>>>>>>>>>" << endl;
    		inOrder(root);
    		cout << endl << endl;
    		cout << "<<<<<<<<<<<<<<<<<<<<<<POST>>>>>>>>>>>>>>>>>>>>>>" << endl;
    		postOrder(root);
    		cout << endl << endl;
    		cout << "<<<<<<<<<<<<<<<<<<<<<<LEVEL>>>>>>>>>>>>>>>>>>>>>>" << endl;
    		printLevel(root);
    		cout << endl << endl << endl << endl;
		}
		else
		{
			tempNum = atoi(tempData);
			insertNode(root, tempNum);
		}
	}
}

treeNode * insertNode(treeNode *&root, int data)
{
	bool bFoundSpot = false;
	treeNode *newNode = NULL, *leaf = root;
	
	if(root == NULL)
	{
		newNode = new treeNode;
		
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
        newNode = new treeNode;

		newNode -> data = data;
		newNode -> left = NULL;
		newNode -> right = NULL;
		
		if(data < leaf -> data)
		    leaf -> left = newNode;
		else
		    leaf -> right = newNode;

		return newNode;
	}
}

void deleteNode(treeNode *&root, int data)
{
    treeNode *leaf = root, *parent = NULL, *leftmost = NULL;
    bool bDone = false;
    int temp;
    
	while((leaf -> data != data) && (!bDone))
	{
		if(data < leaf -> data)
		{
		    if(leaf -> left != NULL)
		    {
				parent = leaf;
				leaf = leaf -> left;
			}
		}
		else if(data > leaf -> data)
		{
		    if(leaf -> right != NULL)
		    {
				parent = leaf;
		        leaf = leaf -> right;
			}
		}
		else if(data == leaf -> data)
		    bDone = true;
		else
		{
		    bDone = true;
		    leaf = NULL;
			parent = NULL;
		}
	}
	
	if(leaf != NULL)
	{
		if((leaf -> left == NULL) && (leaf -> right == NULL))
		{
            if(parent != NULL)
			{
				if(parent -> left == leaf)
			 	   parent -> left = NULL;
				else
				    parent -> right = NULL;
			}
			delete leaf;
		}
		else if((leaf -> left == NULL) && (leaf -> right != NULL))
		{
            if(parent != NULL)
			{
            	if(parent -> left == leaf)
			  	  parent -> left = leaf -> right;
				else
			   	 	parent -> right = leaf -> right;
			}
			delete leaf;
		}
		else if((leaf -> left != NULL) && (leaf -> right == NULL))
		{
			if(parent != NULL)
			{
				if(parent -> left == leaf)
				    parent -> left = leaf -> left;
				else
				    parent -> right = leaf -> left;
			}
			delete leaf;
		}
		else if((leaf -> left != NULL) && (leaf -> right != NULL))
		{
			leftmost = leaf -> right;
			
			while(leftmost -> left != NULL)
			    leftmost = leftmost -> left;
			    
			temp = leftmost -> data;
			deleteNode(root, leftmost -> data);
			leaf -> data = temp;
		}
	}
}

void preOrder(struct treeNode *root)
{
    if(root != NULL)
    {
        cout <<  root -> data << "  ";
        preOrder(root -> left);
        preOrder(root -> right);
    }
}

void inOrder(struct treeNode *root)
{
    if(root != NULL)
    {
        inOrder (root -> left);
        cout <<  root -> data << "  ";
        inOrder (root -> right);
    }
}

void postOrder(struct treeNode *root)
{
    if(root != NULL)
    {
        postOrder (root -> left);
        postOrder (root -> right);
        cout <<  root -> data << "  ";
    }
}

void printLevel(struct treeNode *root)
{
	node *front = NULL, *rear = NULL;
	treeNode *leaf = root;
	int nextNodes = 0, currentNodes = 0;
	
	enqueue(root, front, rear);
	currentNodes++;
	
	while(currentNodes != 0)
	{
		leaf = front -> tn;
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

void enqueue(treeNode *&data, struct node *&front, struct node *&rear)
{
    struct node *newNode = new node;

    newNode -> tn = data;
    newNode -> next = NULL;

    if (rear)
	{
		rear -> next = newNode;
      	rear = newNode;
   	}
   	else
        front = rear = newNode;
}

int dequeue(struct node *&front, struct node *&rear)
{
    struct node *temp;
    int tempData;

	tempData = front -> tn -> data;

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

