#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void readFile(int heapArray[]);
void insertItem(int item, int heapArray[]);
void reHeapUp(int position, int heapArray[]);
void reHeapDown(int heapArray[]);
int findParent(int position);
int findLeftChild(int position);
int findRightChild(int position);
int swap(int pos1, int pos2, int heapArray[]);
void printHeap(int heapArray[]);
void deleteSome(int num, int heapArray[]);
void deleteItem(int heapArray[]);

ifstream in;
const int MAX_SIZE = 15;

int main()
{
	int heapArray[MAX_SIZE] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	readFile(heapArray);
	
	cout << "INITIAL HEAP:" << endl << endl;
	
	printHeap(heapArray);

	cout << "NOW DELETING..." << endl << endl;
	
	deleteSome(5, heapArray);
    
    cout << endl << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}

void readFile(int heapArray[])
{
    int tempData;

	in.open("input.txt");

	while (!in.eof())
    {
        in >> tempData;
		insertItem(tempData, heapArray);
	}
	
	in.close();
}

void insertItem(int item, int heapArray[])
{
    int i = 0;

    while((heapArray[i] >= 0) && (i < MAX_SIZE))
		i++;

	heapArray[i] = item;
	reHeapUp(i, heapArray);
}

void reHeapUp(int position, int heapArray[])
{
	int slot = position;

	while((slot > 0) && (heapArray[slot] < heapArray[findParent(slot)]))
	    slot = swap(slot, findParent(slot), heapArray);
}

void reHeapDown(int heapArray[])
{
    int slot = 0;
    int rightSlot = findRightChild(slot);
	int leftSlot = findLeftChild(slot);
	bool bDone = false;

	if((rightSlot < 0) || (rightSlot >= MAX_SIZE))
	    	rightSlot = -1;
		else if(heapArray[rightSlot] == -1)
		    rightSlot = -1;

		if((leftSlot < 0) || (leftSlot >= MAX_SIZE))
	    	leftSlot = -1;
        else if(heapArray[leftSlot] == -1)
		    leftSlot = -1;

	while(!bDone)
	{
		if((rightSlot == -1) && (leftSlot == -1))
			bDone = true;
			
		else if((rightSlot != -1) && (leftSlot == -1))
	    {
			if((heapArray[slot] > heapArray[rightSlot]) && (heapArray[rightSlot] != -1))
				slot = swap(slot, rightSlot, heapArray);
			else
			    bDone = true;
		}
		else if((rightSlot == -1) && (leftSlot != -1))
	    {
            if((heapArray[slot] > heapArray[leftSlot]) && (heapArray[leftSlot] != -1))
				slot = swap(slot, leftSlot, heapArray);
			else
			    bDone = true;
		}
		else if((rightSlot != -1) && (leftSlot != -1))
		{
			if(heapArray[leftSlot] < heapArray[rightSlot])
			{
                if((heapArray[slot] > heapArray[leftSlot]) && (heapArray[leftSlot] != -1))
					slot = swap(slot, leftSlot, heapArray);
				else
			  	  	bDone = true;
			}
			else
			{
                if((heapArray[slot] > heapArray[rightSlot]) && (heapArray[rightSlot] != -1))
					slot = swap(slot, rightSlot, heapArray);
				else
			  	  	bDone = true;
			}
		}
		
		rightSlot = findRightChild(slot);
		leftSlot = findLeftChild(slot);
		
		if((rightSlot < 0) || (rightSlot >= MAX_SIZE))
	    	rightSlot = -1;
		else if(heapArray[rightSlot] == -1)
		    rightSlot = -1;

		if((leftSlot < 0) || (leftSlot >= MAX_SIZE))
	    	leftSlot = -1;
        else if(heapArray[leftSlot] == -1)
		    leftSlot = -1;
	}

    printHeap(heapArray);
}

int findParent(int position)
{
	return((position - 1)/2);
}

int findLeftChild(int position)
{
	return((2 * position) + 1);
}

int findRightChild(int position)
{
	return((2 * position) + 2);
}

int swap(int pos1, int pos2, int heapArray[])
{
	heapArray[pos1] = heapArray[pos1] ^ heapArray[pos2];
	heapArray[pos2] = heapArray[pos1] ^ heapArray[pos2];
	heapArray[pos1] = heapArray[pos1] ^ heapArray[pos2];
	
	return pos2;
}

void printHeap(int heapArray[])
{
	int i = 0;
	int level = 1;
	
	for(i = 0; i < MAX_SIZE; i++)
	{
		if(heapArray[i] >= 0)
			cout << heapArray[i];
		
		if(i == (pow(2.0, level) - 2))
		{
		    cout << endl;
		    level++;
		}
		else
		    cout << " ";
	}
	
	cout << endl << endl << endl;
}

void deleteSome(int num, int heapArray[])
{
	int i = 0;

	if(num > MAX_SIZE)
		num = MAX_SIZE;
		
	for(i = 0; i < num; i++)
		deleteItem(heapArray);
}

void deleteItem(int heapArray[])
{
	int i = 0;
	int temp = 0;
	
	while((heapArray[i] >= 0) && (i < MAX_SIZE))
		i++;
		
	i--;
		
	temp = heapArray[i];
	heapArray[i] = -1;
	heapArray[0] = temp;
	reHeapDown(heapArray);
}
