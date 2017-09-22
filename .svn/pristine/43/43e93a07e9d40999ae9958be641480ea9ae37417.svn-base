#include "common.h"
#include <iostream>
#include <queue>

/*
  As a reminder, useful STL queue methods include:
  empty : Test whether container is empty (public member function)
  size : Return size (public member function)
  front : Access next element (public member function)
  push : Insert element (public member function)
  pop : Remove next element (public member function)
*/

using namespace std;

int insertAt(queue<int> &q, int data, int pos)
{
    if(pos < 0 || pos > q.size())
        return -1;

	for(size_t i = 0; i < pos; i++)
	{
        q.push(q.front());
        q.pop();
    }
    q.push(data);
    for(size_t i = 0; i < q.size() - pos-1; i++)
    {
        q.push(q.front());
        q.pop();
    }
    return 1;	
}
