#include "common.h"
#include "quadtree.h"

#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

int Quadtree::tallyNeighbors(RGBAPixel const & target, 
			     QuadtreeNode const * curNode, int tolerance) const
{
  if (!curNode)
    return 0;
  if (!curNode->nwChild)
    return maxDev(target, curNode) < tolerance;
  
  return tallyNeighbors(target, curNode->nwChild, tolerance) +
    tallyNeighbors(target, curNode->neChild, tolerance) +
    tallyNeighbors(target, curNode->swChild, tolerance) +
    tallyNeighbors(target, curNode->seChild, tolerance);
}

void Quadtree::prunish(int tolerance, double percent) {
  prunish(root, tolerance, resolution, percent);
}

void Quadtree::prunish(QuadtreeNode * curNode, int tolerance, int res, double percent) {
  if (!curNode)
    return;
  if (tallyNeighbors(curNode->element, curNode, tolerance) >= res*res*percent) {
    clear(curNode->nwChild);
    clear(curNode->neChild);
    clear(curNode->swChild);
    clear(curNode->seChild);
  } else {
    prunish(curNode->nwChild, tolerance, res / 2, percent);
    prunish(curNode->neChild, tolerance, res / 2, percent);
    prunish(curNode->swChild, tolerance, res / 2, percent);
    prunish(curNode->seChild, tolerance, res / 2, percent);
  }
}
