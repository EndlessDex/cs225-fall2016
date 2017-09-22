#include "linkedlist.h"
#include <iostream>
using namespace std;

bool append(LinkedList &mylist, int newdata)
{
	if(myList.head != NULL)
        {
                Node * temp = head;
                while(temp->next != NULL)
                {
                        temp = temp->next;
                }
                temp->next = new Node(newData);
        }
        else
        {
                myList.head = new Node(newData);
        }
        return 1;
}
