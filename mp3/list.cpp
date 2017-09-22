/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
// #include "list.h"
#include <iostream>
using namespace std;
template <class T>
List<T>::~List()
{
/// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
// @todo Graded in MP3.1
    if(head != NULL)
    {
        ListNode* currNode = NULL;
        ListNode* nextNode = head;
        while(nextNode != NULL)
        {
            currNode = nextNode;
            nextNode = currNode->next;
            delete currNode;
        }
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
/// @todo Graded in MP3.1
    if(head != NULL)
    {
        head->prev = new ListNode(ndata);
        head->prev->next = head;
        head = head->prev;
    }
    else
        head = tail = new ListNode(ndata);
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
/// @todo Graded in MP3.1
    if(head != NULL)
    {
        tail->next = new ListNode(ndata);
        tail->next->prev = tail;
        tail = tail->next;
    }
    else
        tail = head = new ListNode(ndata);
    length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}
/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
/// @todo Graded in MP3.1
    if(startPoint != NULL && endPoint != NULL && startPoint != endPoint)
    {
        ListNode* curr = startPoint->next;
        ListNode* temp = NULL;
        while(curr != endPoint) {
            temp = curr->next;
            curr->next = curr->prev;
            curr->prev = temp;
            curr = temp;
        }

        temp = startPoint->prev;
        startPoint->prev = startPoint->next;
        startPoint->next = endPoint->next;
        endPoint->next = endPoint->prev;
        endPoint->prev = temp;

        if(temp)
            temp->next = endPoint;
        if(startPoint->next)
            startPoint->next->prev = startPoint;
        temp = startPoint;
        startPoint = endPoint;
        endPoint = temp;
    }
}
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
/// @todo Graded in MP3.1
    ListNode* start = head;
    ListNode* end = head;
    ListNode* nextBlock = head;
    if(head)
    {
        do{
            for(int i = 0; i < n - 1; i++)
            {
                nextBlock = end->next;
                if(nextBlock == NULL)
                    break;
                end = nextBlock;
            }
            nextBlock = end->next;

            reverse((head == start ? head : start), (tail == end ? tail : end));
            start = end = nextBlock;
        } while(nextBlock != NULL);
    }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
/// @todo Graded in MP3.1
    ListNode* curr = head;
    ListNode* next = NULL;
    while(curr != tail && curr->next != tail)
    {
        curr = curr->next;
        next = curr->next;
        //Remove the node from the list
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        //insert the node at the back
        tail->next = curr;
        curr->prev = tail;
        curr->next = NULL;
        tail = curr;

        curr= next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
// current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
// set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

// set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
/// @todo Graded in MP3.2
    ListNode* secondHead = start;
    for(int i = 0; i < splitPoint; i++)
    {
        secondHead = secondHead->next;
    }
    secondHead->prev->next = NULL;
    secondHead->prev = NULL;
    return secondHead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
// set up the current list
    head = merge(head, otherList.head);
    tail = head;

// make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

// empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
/// @todo Graded in MP3.2

    ListNode* nextNode = first;
    ListNode* prevNode = NULL;
    while (1) {
        if (first == NULL) {
            first = second;
            break;
        }
        else if (second == NULL) {
            break;
        }
        else if (nextNode == NULL) {
            prevNode->next = second;
            second->prev = prevNode;
            break;
        }
        else if (nextNode->data < second->data) {
            prevNode = nextNode;
            nextNode = nextNode->next;
        }
        else {
            if(prevNode)
                prevNode->next = second;
            else
                first = second;
            second->prev = nextNode->prev;
            nextNode->prev = second;
            prevNode = second;
            second = second->next;
            prevNode->next = nextNode;
        }
    }
    return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
// @todo Graded in MP3.2
    if(chainLength <= 1)
        return start;
    else
    {
        ListNode* secondStart = split(start, chainLength/2);
        start = mergesort(start, chainLength/2);
        secondStart = mergesort(secondStart, chainLength - chainLength / 2);
        start = merge(start, secondStart);
        return start;
    }
}


template <class T>
void List<T>::printReverse(ostream& os) const
{
    os << "<";
    ListNode* curr = tail;
    while (curr != NULL) {
        os << " " << curr->data;
        curr = curr->prev;
    }
    os << " >";
}
