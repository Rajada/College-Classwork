#include <iostream>
#include <fstream>

using namespace std;

void readFile(int hashArray[]);
void insertItem(int item, int hashArray[]);
void searchItem(int item, int hashArray[]);
int moduloInsert(int item, int hashArray[], bool bSearch);
int doubleInsert(int item, int hashArray[], bool bSearch);
int linearInsert(int item, int start, int hashArray[], bool bSearch);

ifstream in;
int lastSlot;
int collisions = 0;

int main()
{
	int hashArray[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int sItem = 0;

	readFile(hashArray);
	
	cout << endl << "[" << hashArray[0] << "," << hashArray[1] << "," << hashArray[2] << "," << hashArray[3] << "," << hashArray[4] << "," << hashArray[5] << "," << hashArray[6] << "," << hashArray[7] << "," << hashArray[8] << "," << hashArray[9] << "]" << endl << endl;
	
	cout << "Enter item to search for: ";
	cin >> sItem;
	searchItem(sItem, hashArray);

    cout << endl << "Press [ENTER] to exit...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}

void readFile(int hashArray[])
{
    int tempData;

	in.open("input.txt");

	while (!in.eof())
    {
        in >> tempData;
		insertItem(tempData, hashArray);
	}

	in.close();
}

void insertItem(int item, int hashArray[])
{
	collisions = 0;

	if(moduloInsert(item, hashArray, false) < 0)
	{
		collisions++;

        if(doubleInsert(item, hashArray, false) < 0)
        {
            collisions++;
           	linearInsert(item, lastSlot, hashArray, false);
		}
	}
	
	cout << collisions << " collisions" << endl;
}

void searchItem(int item, int hashArray[])
{
	int slot = -1;

	slot = moduloInsert(item, hashArray, true);

	if(slot < 0)
	{
		slot = doubleInsert(item, hashArray, true);

        if(slot < 0)
        {
           	slot = linearInsert(item, lastSlot, hashArray, true);
		}
	}

	if(slot == -1)
		cout << "Item not found" << endl;
	else
	    cout << "Item found in slot " << slot << endl;
}

int moduloInsert(int item, int hashArray[], bool bSearch)
{
	int slot = (item % 10);
	
	if(hashArray[slot] >= 0)
	{
		if((bSearch) && (hashArray[slot] == item))
			return slot;
		else
	    	return -1;
	}
	else
	{
        if(!bSearch)
		{
			hashArray[slot] = item;
			return slot;
		}
	}
}
int doubleInsert(int item, int hashArray[], bool bSearch)
{
    int slot = (item % 10);
    
    slot = (slot - (item % slot));
    
    if(hashArray[slot] >= 0)
    {
		lastSlot = slot;
		
		if((bSearch) && (hashArray[slot] == item))
			return slot;
		else
	    	return -1;
	}
	else
	{
        if(!bSearch)
		{
			hashArray[slot] = item;
			return slot;
		}
	}
}
int linearInsert(int item, int start, int hashArray[], bool bSearch)
{
	int i = 0;
	int tempSlot = start;
	bool bDone = false;
	
	while((i < 10) && (!bDone))
	{
		if(hashArray[tempSlot] < 0)
		{
			if(!bSearch)
			{
				hashArray[tempSlot] = item;
		    	bDone = true;
			}
		}
		else
		{
            if((bSearch) && (hashArray[tempSlot] == item))
            {
				bDone = true;
				return tempSlot;
			}

			tempSlot++;
		
			if(tempSlot > 9)
        		tempSlot = 0;

			i++;
			collisions++;
		}
	}
	
	if(!bDone)
	    return -1;
 	else
		return i;
}
