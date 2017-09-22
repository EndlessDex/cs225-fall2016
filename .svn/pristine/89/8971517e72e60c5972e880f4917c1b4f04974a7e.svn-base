#include "dsets.h"

void DisjointSets::addelements(int num)
{
    for (int i = 0; i < num; i++)
        set.push_back(-1);
}

int DisjointSets::find(int elem)
{
    if(set[elem] < 0)
        return elem;
    else
        return find(set[elem]);
}

void DisjointSets::setunion(int a, int b)
{
    int A = find(a);
    int B = find(b);
    int newSize = set[A] + set[B];

    if(set[A] == set[B])
        set[B] = A;

    if(set[A] < set[B]) {
        set[B] = A;
        set[A] = newSize;
    } else {
        set[A] = B;
        set[B] = newSize;
    }
}
