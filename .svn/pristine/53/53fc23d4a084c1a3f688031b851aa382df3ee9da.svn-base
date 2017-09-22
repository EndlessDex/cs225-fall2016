#include "common.h"
#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

int updateMaxHelper(Node<int> *&subRoot)
{
//If empty children are 0, use this section
    if(subRoot == NULL)
        return 0;
//------------------

    if(subRoot->left == NULL && subRoot->right == NULL)
        ;

//If empty children are disregarded use this section (comment out previous section)
/*
    else if(subRoot->right == NULL)
        subRoot->data = subRoot->data + updateMaxHelper(subRoot->left);
    else if(subRoot->left == NULL)
        subRoot->data = subRoot->data + updateMaxHelper(subRoot->right);
*/
    else
        subRoot->data = subRoot->data + max(updateMaxHelper(subRoot->left),
                                            updateMaxHelper(subRoot->right));
    
    return subRoot->data;
}

void updateMax(Node<int> *&root)
{
    updateMaxHelper(root);
}


