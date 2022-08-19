#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in;

struct node* addNode(struct node*& nextNode, struct node*& prevNode, char data[16]);
int makeList(struct node*& head, struct node*& tail);
int deleteNodes(int amount, int max, struct node*& head, struct node*& tail);
void showList(struct node*& start);

struct node
{
       char data[16];
       struct node* next;
       struct node* prev;
};

int main()
{
	struct node *tail = NULL, *head = NULL;
	int choice = 0, max = 0;
	
	max = makeList(head, tail);

	cout << "How many nodes to delete? (max: " << max << ") ";
	cin >> choice;
	
	cout << deleteNodes(choice, max, head, tail) << " node(s) deleted..." << endl << endl;

	if(choice != max)
		showList(head);
	
	cout << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
	return 0;
}

struct node* addNode(struct node*& nextNode, struct node*& prevNode, char data[16])
{
    struct node *newNode = new node;

    strcpy(newNode -> data, data);
    newNode -> next = NULL;
	newNode -> prev = prevNode;
	nextNode = newNode;

    return nextNode;
}

int makeList(struct node*& head, struct node*& tail)
{
	char tempData[16];
	int max = 0;
	
	in.open("input.txt");

    while (!in.eof())
    {
    	in >> tempData;

    	if(!head)
    	{
    	    tail = addNode(tail, tail, tempData);
			head = tail;
		}
	 	else
	 	    tail = addNode(tail -> next, tail, tempData);
	 	    
		max++;
	}

	in.close();

	head -> prev = tail;
	tail -> next = head;
	
	return max;
}

int deleteNodes(int amount, int max, struct node*& head, struct node*& tail)
{
	int i = 0;
	struct node *current = head, *toDelete = head;
	
	if(amount < 0)
	    amount *= -1;
	    
	if(amount > max)
		amount = max;
	
	if(amount != max)
	{
		for(i = 0; i < amount; i++)
		{
			current = current -> next;
		}
	
		head = current;
		head -> prev = tail;
		tail -> next = head;

	}
	
	current = toDelete;

    for(i = 0; i < amount; i++)
	{
		toDelete = current -> next;
		delete[] current;
		current = toDelete;
	}
	
	return i;
}

void showList(struct node*& start)
{
	struct node *current = NULL;

	current = start;
	
    do
	{
		cout << current -> data << endl;
		current = current -> next;
	}
	while((current != NULL) && (current != start));
	
	cout << endl;
}
