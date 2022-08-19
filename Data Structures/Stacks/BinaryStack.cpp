#include <iostream>
using namespace std;

struct node
{
       int data;
       int power;
       struct node *next;
};

bool pop(struct node *&top);
void push(int data, int power, struct node *&top);
void printList(struct node *&top);

int main()
{
    struct node *top = NULL;
	int choice = 0, divide = 0, remainder = 0, power = 0;
    
    cout << "Enter a number ";
	cin >> choice;
	divide = choice;
	
	while(divide > 0)
	{
		remainder = divide % 2;
		
		push(remainder, power, top);
		divide = divide / 2;
		
		power++;
	}
	
	printList(top);
	
	cout << endl << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool pop(struct node *&top)
{
	struct node *temp;
	
    if(top)
	{
        temp = top;
        top = top -> next;
        delete temp;
        return true;
    }
    
    return false;
}

void push(int data, int power, struct node *&top)
{
    struct node *newNode = new node;

    newNode -> data = data;
    newNode -> power = power;
    newNode -> next = top;
    top = newNode;
}

void printList(struct node *&top)
{
    while(top != NULL)
    {
        cout << "2^" << top -> power << ": " << top -> data << endl;
		pop(top);
	}
}
