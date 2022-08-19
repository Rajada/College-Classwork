#include <iostream>
#include <fstream>
using namespace std;

ifstream in;

void readList(struct node *&front, struct node *&rear);
void enqueue(int item, struct node *&front, struct node *&rear);
void dequeue(struct node *&front, struct node *&rear);
void trimList(struct node *&front, struct node *&rear, struct node *&front2, struct node *&rear2);
void printList(struct node *&front);

struct node
{
       int data;
       struct node *next;
};

int main()
{
    struct node *front, *rear, *front2, *rear2;
    front = rear = front2 = rear2 = NULL;

	readList(front, rear);
	trimList(front, rear, front2, rear2);
	printList(front2);
	
	cout << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readList(struct node *&front, struct node *&rear)
{
	int tempData;

    in.open("input.txt");

    while (!in.eof())
    {
        in >> tempData;
        
        enqueue(tempData, front, rear);
	}
}

void enqueue(int data, struct node *&front, struct node *&rear)
{
    struct node *newNode = new node;

    newNode -> data = data;
    newNode -> next = NULL;
    
    if (rear)
	{
		rear -> next = newNode;
      	rear = newNode;
   	}
   	else
        front = rear = newNode;
}

void dequeue(struct node *&front, struct node *&rear)
{
    struct node *temp;

    if(front)
	{
        temp = front;
        front = front -> next;
        delete temp;
    }

    if(!front)
       	rear = NULL;
}

void trimList(struct node *&front, struct node *&rear, struct node *&front2, struct node *&rear2)
{
	int tempData;

	while(front != NULL)
	{
		tempData = front -> data;
		
		dequeue(front, rear);
		
		if(tempData >= 0)
		    enqueue(tempData, front2, rear2);
	}
}

void printList(struct node *&front)
{
    struct node *current = front;
    
    while(current != NULL)
    {
        cout << current -> data << endl;
		current = current -> next;
	}
}
