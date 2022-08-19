#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

void readIn(struct node *&front, struct node *&rear, struct node *&top);                                    //Converting to postfix, reading in file
int sortCharacter(char inChar);                                                                             //Returns the priority of a character
void operatorCompare(char curChar, struct node *&front, struct node *&rear, struct node *&top);             //Compares top of stack and current character, then pushes and pops as needed
void parentheticalPop(struct node *&front, struct node *&rear, struct node *&top);                          //Pops all chars up to the open parenthesis
void enqueue(char data, struct node *&front, struct node *&rear);                                           //Insert into queue
char dequeue(struct node *&front, struct node *&rear);                                                      //Remove from queue, returns removed value
bool convert(struct node *&top, int number);                                                                //Dec to hex stored on stack, also returns true if negative
void push(char data, struct node *&top);                                                                    //Push onto stack
char pop(struct node *&top);                                                                                //Pop off of stack, returns popped value
int evaluateQueue(struct node *&front, struct node *&rear, struct node *&top);                              //Do the math
void printQueue(struct node *&front, struct node *&rear);                                                   //Print the postfix equation (of off queue)
void printResult(struct node *&top);                                                                        //Print the hex result (off of stack)

struct node                                                                                                 //Data structure for my queue and stack
{
       char data;
       struct node *next;
};                                                                                                          //Oh, man, so that's why they call the class that. Did you know that? I feel this should have been covered in day one. Maybe this is all day one should have been about, because this is blowing my mind right now. Its probably just the lack of sleep.

ifstream in;

int main()
{
    struct node *top = NULL, *front = NULL, *rear = NULL;
    
    readIn(front, rear, top);                                                                               //Convert input text file to postfix
    
    cout << " = ";
    
    if(convert(top, evaluateQueue(front, rear, top)))                                                       //If true, we have a negative number, also, puts hex result into stack
        cout << "-";
	
	printResult(top);                                                                                       //Show the result by printing off the stack
    
    cout << endl << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}

void readIn(struct node *&front, struct node *&rear, struct node *&top)
{
	char tempChar;
	int priority = -1;
	
	in.open("input.txt");
	
	in >> tempChar;                                                                                         //Prime read
	
	while (!in.eof())
    {
		priority = sortCharacter(tempChar);                                                                 //Get the priority, used to determine type of character in this case
		
		switch(priority)
		{
			case 0:                                                                                         //A number or letter (letters will not evaluate, but can be used to test postfix conversion)
				enqueue(tempChar, front, rear);                                                             //Put the operand into the queue
			break;
			case 1:                                                                                         //An operator ^,*,/,+,-
			case 2:
			case 3:
				if(!top)
				    push(tempChar, top);                                                                    //If stack is empty, push operator into stack
				else
					operatorCompare(tempChar, front, rear, top);                                            //If stack is not empty, compare
			break;
			case 4:                                                                                         //Open parenthesis
                push(tempChar, top);                                                                        //Push onto the stack
            break;
			case 5:                                                                                         //Closed parenthesis
				parentheticalPop(front, rear, top);                                                         //Pop all the way back to the open parenthesis
            break;
		}
		
		in >> tempChar;                                                                                     //Read in the next character
	}
	
 	while(top != NULL)                                                                                      //When done, pop anything left on the stack and add it to the queue
	{
		tempChar = pop(top);
		enqueue(tempChar, front, rear);
	}

	in.close();
	
	printQueue(front, rear);                                                                                //Show postfix notation
}

int sortCharacter(char inChar)                                                                              //Returns priority of a character
{
    if(((inChar >= '0') && (inChar <= '9')) || ((inChar >= 'a') && (inChar <= 'z')) || ((inChar >= 'A') && (inChar <= 'Z')))
	    return 0;
    else if(inChar == '^')
        return 1;
	else if((inChar == '*') || (inChar == '/'))
	    return 2;
 	else if((inChar == '+') || (inChar == '-'))
	    return 3;
    else if(inChar == '(')
        return 4;
    else if(inChar == ')')
	    return 5;
	else
	    return -1;
}

void operatorCompare(char curChar, struct node *&front, struct node *&rear, struct node *&top)              //Compares top of stack and current character, then pushes and pops as needed
{
	char tempChar;
	
	if(sortCharacter(curChar) < sortCharacter(top -> data))                                                 //Current character is higher priority (smaller number = higher priority)
	    push(curChar, top);                                                                                 //Push it
	else
	{
		while((top != NULL) && (sortCharacter(curChar) >= sortCharacter(top -> data)))                      //Otherwise, iterate through the stack, as long as the top character is lower priority, pop it, queue it and check the next one
		{
            tempChar = pop(top);
            enqueue(tempChar, front, rear);
		}
		
		push(curChar, top);                                                                                 //When we finally hit a character with higher priority (or the end of the list) we push the current character
	}
}

void parentheticalPop(struct node *&front, struct node *&rear, struct node *&top)                           //Pops all chars up to the matching open parenthesis
{
    char tempChar;
    
    while((top != NULL) && (top -> data != '('))                                                            //As long as we're not at a NULL or (
	{
		tempChar = pop(top);                                                                                //Pop the character, and queue it
		enqueue(tempChar, front, rear);
	}
	
	pop(top);                                                                                               //Also get rid of the (
}

void enqueue(char data, struct node *&front, struct node *&rear)                                            //Add item to queue
{
    struct node *newNode = new node;

    newNode -> data = data;                                                                                 //Initialize newNode
    newNode -> next = NULL;

    if (rear)                                                                                               //If we have at least one node
	{
		rear -> next = newNode;                                                                             //Add newNode to the end of the queue
      	rear = newNode;
   	}
   	else
        front = rear = newNode;                                                                             //Otherwise, first node in the queue, it is both front and rear
}

char dequeue(struct node *&front, struct node *&rear)                                                       //Remove an item from queue
{
    struct node *temp;
    char data;

    if(front)                                                                                               //Check to see if we even have a queue
	{
        temp = front;                                                                                       //set temp = front of queue
        data = front -> data;                                                                               //Copy the data out of front
        front = front -> next;                                                                              //Find the next item in queue
        delete temp;                                                                                        //Delete front of queue
    }

    if(!front)                                                                                              //If there is no front, there should be no rear, NULL it
       	rear = NULL;
       	
	return data;                                                                                            //Return the data
}

bool convert(struct node *&top, int number)                                                                 //Convert from a decimal to hex and put it onto the stack
{
	int divide = 0, remainder = 0;
	char item;
	bool bNeg = false;

	if(number < 0)                                                                                          //I don't want to work with a negative number, but I will need to notify display that the number is negative
	{
	    number = number * -1;
		bNeg = true;
	}
	
	divide = number;

    while(divide > 0)
	{
		remainder = divide % 16;                                                                            //Modulo by base to get the least undiscovered digit
		
		if(remainder > 9)                                                                                   //Convert a digit > 9 to a letter
			item = ('A' + (remainder - 10));
		else                                                                                                //Oherwise, just convert it to a character version of the digit
		    item = ('0' + remainder);
		    
		push(item, top);                                                                                    //Push the character
		divide = divide / 16;                                                                               //Reduce to find the next digit
	}
	
	return bNeg;                                                                                            //Tells display to put a - in front of the result
}

void push(char data, struct node *&top)                                                                     //Push item onto stack
{
    struct node *newNode = new node;

    newNode -> data = data;                                                                                 //Initialize newNode
    newNode -> next = top;
    top = newNode;                                                                                          //newNode is now top item
}

char pop(struct node *&top)                                                                                 //Pop item off stack
{
	struct node *temp;
	char ret;

    if(top)                                                                                                 //Do we even have a stack?
	{
        temp = top;                                                                                         //temp = top of stack
        top = top -> next;                                                                                  //Top of stack is now the next item
        ret = temp -> data;                                                                                 //Get the data from temp
        delete temp;                                                                                        //Delete item
        
        return ret;                                                                                         //Return data
    }
}

int evaluateQueue(struct node *&front, struct node *&rear, struct node *&top)                               //Iterate through queue (postfix) and add it up
{
	int result = 0, op1 = 0, op2 = 0;
	char inChar;

	while(front != NULL)                                                                                    //Iterate through the queue
	{
		inChar = dequeue(front, rear);                                                                      //Remove an item from the queue and save the character within
		
		if((inChar >= '0') && (inChar <= '9'))                                                              //If it is a number, throw it into the stack
		    push(inChar, top);
		else if((inChar == '+') || (inChar == '-') || (inChar == '*') || (inChar == '/') || (inChar == '^'))//If it is an operator...
		{
			op2 = (pop(top) - '0');                                                                         //Pop two numbers off the stackshizzle
			op1 = (pop(top) - '0');

			if(inChar == '+')                                                                               //Addition
			{
			    result = (op1 + op2);
			    push('0' + result, top);
			}
			else if(inChar == '-')                                                                          //Subtraction
			{
			    result = (op1 - op2);
			    push('0' + result, top);
			}
   			else if(inChar == '*')                                                                          //Multiplication
   			{
			    result = (op1 * op2);
			    push('0' + result, top);
			}
			else if(inChar == '/')                                                                          //Does this amount of commenting seem a little excessive to you? Division
			{
			    result = (op1 / op2);
			    push('0' + result, top);
			}
            else if(inChar == '^')                                                                          //Power
            {
			    result = (pow(op1, op2));
			    push('0' + result, top);                                                                    //After doing the respective math, each operator pushes the result back on top of the stack for later use
			}
		}
	}

	result = (pop(top) - '0');                                                                              //Finally, pop off the result one last time and return it
	return result;
}

void printQueue(struct node *&front, struct node *&rear)                                                    //Print postfix queue to screen
{
	struct node *current = front;

    while(current != NULL)                                                                                  //Iterate through queue
    {
	    cout << current -> data;                                                                            //Print the data of the node
		current = current -> next;                                                                          //Advance
	}
}

void printResult(struct node *&top)                                                                         //Print the stack (only called when the stack has the hex number in it) to the screen
{
    while(top != NULL)                                                                                      //Iterate through stack
    {
	    cout << top -> data;                                                                                //Print out the data in the node
		pop(top);                                                                                           //Pop the top item, advancing top to the next node
	}
}
																											//Tell me, did you really read every single one of these? I was just about losing my mind trying to
																											//imagine the need for comments like "Advance" and "Iterate through the queue". Well, as you can see
																											//I've finally lost it. If you don't see me Monday, check the nearest mental institution.
