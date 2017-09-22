#include "linkedlist.h"

void merge(LinkedList* lst1,
           LinkedList* lst2,
           LinkedList* mrg)
{
	Node* temp1 = lst1.head;
	Node* temp2 = lst2.head;
	while(temp1 != NULL && temp2 !=NULL)
{
	if(temp1 == NULL)
		;
	else if(temp1->data < temp2->data)
	{
		mrg.append(temp1->data);
		temp1 = temp1->next;
	}
	else
	{
		mrg.append(temp2.data);
		temp2 = temp2->next;
}
	return;
}
