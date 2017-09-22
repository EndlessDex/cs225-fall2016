#include "common.h"
#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

int h(Node<int> *n)
{
  if(!n)
    return -1;
  if(!n->left && !n->right)
    return 0;
  return max(h(n->left),h(n->right)) + 1;
}

using namespace std;

bool isBalanced(Node<int> *&root)
{
  if (!root)
    return true;
  if (!root->left && !root->right)
    return true;
  return isBalanced(root->left) && isBalanced(root->right) &&
    abs(h(root->left) - h(root->right)) <= 1;
}



