#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in;
ofstream out;
bool bQuit = false;

struct node* addNode(struct node*& nextNode, struct node*& prevNode, int data);
void removeHead(int num, struct node*& current);
void removeTail(int num, struct node*& current);

struct node
{
       int data;
       struct node* next;
       struct node* prev;    
};

int main()
{
	struct node *theList, *current;
	struct node temp;
	int tempData;
	int choice;
	int max = 0;

 	temp.next = NULL;
	temp.prev = NULL;
    struct node *tail = &temp;

    in.open("input.txt");

	while (!in.eof())
    {
    	in >> tempData;
        tail = addNode(tail -> next, tail, tempData);
        max++;
    }
    
    theList = temp.next;
    
    in.close();

    while(!bQuit)
    {
		cout << "Delete from head [1]" << endl << "Delete from tail [2]" << endl << "Quit [3]" << endl << endl;
		cin >> choice;
		
        switch(choice)
		{
			case 1:
				cout << "Which item do you want to delete from the beginning? ";
				cin >> choice;
				
				if(choice <= 0)
				{
				    cout << "Node number must be greater than 0" << endl << endl;
					cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
				}
				else if (choice > max)
				{
                    cout << "Node number must be less than " << (max + 1) << endl << endl;
					cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
				}
				else
				{
					removeHead(choice, theList);
                	max--;
				}
			break;
            case 2:
				cout << "Which item do you want to delete from the end? ";
				cin >> choice;
				
				if(choice <= 0)
				{
				    cout << "Node number must be greater than 0" << endl << endl;
					cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
				}
				else if (choice > max)
				{
                    cout << "Node number must be less than " << (max + 1) << endl << endl;
					cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
				}
				else
				{
					removeTail(choice, tail);
					max--;
				}
			break;
			case 3:
				bQuit = true;
			break;
			default:
				system("cls");
				cout << "Invalid choice" << endl << endl;
				cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
			break;
		}
    }
    
    out.open("output.txt");

    current = theList;
    
    do
    {
		out << current -> data;
		out << endl;
		current = current -> next;
    }
    while((current -> next != NULL) || (current -> prev != NULL));

    //current = current -> next;
    //out << current -> prev -> data << "   "  << current -> data << "   "  << current -> next -> data << endl;
    
    out.close();
    
    return 0;   
}

void removeHead(int num, struct node*& current)
{
	int count = 0;
	
	for(count = 0; count < (num - 1); count++)
	{
		current = current -> next;
	}
	
	current -> prev -> next = current -> next;
	current -> next -> prev = current -> prev;
	delete[] current;
}

void removeTail(int num, struct node*& current)
{
    int count = 0;

	for(count = 0; count < (num - 1); count++)
	{
		current = current -> prev;
	}

	current -> prev -> next = current -> next;
	current -> next -> prev = current -> prev;
	delete[] current;
}

struct node* addNode(struct node*& nextNode, struct node*& prevNode, int data)
{
    struct node *newNode = new node;
    
    newNode -> data = data;
    newNode -> next = NULL;
    newNode -> prev = NULL;
	newNode -> prev = prevNode;
	nextNode = newNode;
	
    return nextNode;
}
