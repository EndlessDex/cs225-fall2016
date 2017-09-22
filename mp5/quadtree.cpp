/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include <cmath>
#define diffMax 195075
Quadtree::Quadtree():root(NULL) {}
Quadtree::Quadtree(PNG const &source, int resolution) { buildTree(source, resolution); }
Quadtree::~Quadtree() { deleteTree(root); }
Quadtree::Quadtree(Quadtree const &other) { copy(root, other.root); }
Quadtree const & Quadtree::operator=(Quadtree const &other)
{
    // Check for self-assignment!
    if (this == &other)
        return *this;
    deleteTree(this->root);
    copy(this->root, other.root);
    return *this;
}

void Quadtree::buildTree(PNG const &source, int resolution)
{
//Clear the Quadtree of data
    deleteTree(root);
//Initialize new tree
    buildTreeHelper(source, resolution, 0, 0, root);
}

RGBAPixel Quadtree::getPixel(int x, int y) const
{
    if (!root)
        return RGBAPixel();
    QuadtreeNode* curr = root;
    int subRes = curr->resolution;
    if (x<0 || y<0 || x >= subRes || y >= subRes)
        return RGBAPixel();
    while(curr->resolution > 1) {
        subRes /= 2;
        if (!curr->seChild) {
            break;
        }
        if (x < subRes) {
            if (y < subRes)
                curr = curr->nwChild;
            else {
                curr = curr->swChild;
                y -= subRes;
            }
        } else {
            if (y < subRes) {
                curr = curr->neChild;
                x -= subRes;
            } else {
                curr = curr->seChild;
                x -= subRes;
                y -= subRes;
            }
        }
    }
    return curr->element;
}

PNG Quadtree::decompress() const
{
    PNG out(root->resolution, root->resolution);
    for(int y = 0; y < root->resolution; y++) {
        for(int x = 0; x < root->resolution; x++) {
            *out(x,y) = getPixel(x, y);
        }
    }
    return out;
}

void Quadtree::clockwiseRotate()
{
    rotate(root);
}

void Quadtree::prune(int tolerance)
{
    if(!root)
        return;
    arborist(tolerance, root);
}

int Quadtree::pruneSize(int tolerance) const
{
    if(!root)
        return 0;
    return pow(root->resolution,2) - botanist(tolerance, root);
}

int Quadtree::idealPrune(int numLeaves) const
{
    if(!root)
        return 0;
    int max = 195075;
    int min = 0;
    while(min <= max) {
        int middle = min + (max - min) / 2;
        int midSize = pruneSize(middle);
        // std::cout << '\n' <<min << ',' << middle << ',' << max << '\t' << midSize <<  endl;
        if (midSize == numLeaves) {
            if (pruneSize(middle - 1) > numLeaves)
                return middle;
            else
                max = middle - 1;
        }
        else if (midSize < numLeaves) {
            if (pruneSize(middle - 1) > numLeaves)
                return middle;
            else
                max = middle - 1;
        } else
            min = middle + 1;
    }
    return 0;
}
//--------------------------------------
//Helper Functions
//--------------------------------------
void Quadtree::arborist(int tolerance, QuadtreeNode* subRoot)
{
    if(!subRoot->nwChild) //If subRoot is a leaf node
        return;
    else if (leafDifference(tolerance, subRoot, subRoot)) {
        deleteTree(subRoot->nwChild);
        deleteTree(subRoot->neChild);
        deleteTree(subRoot->swChild);
        deleteTree(subRoot->seChild);
    } else {
        arborist(tolerance, subRoot->nwChild);
        arborist(tolerance, subRoot->neChild);
        arborist(tolerance, subRoot->swChild);
        arborist(tolerance, subRoot->seChild);
    }
}
//Returns the number of leaves that would be cut
int Quadtree::botanist(int tolerance, QuadtreeNode* subRoot) const
{
    if(!subRoot->nwChild) //If subRoot is a leaf node
        return 0;
    else if (leafDifference(tolerance, subRoot, subRoot)) {
        return pow(subRoot->resolution, 2) - 1;
    } else {
        return botanist(tolerance, subRoot->nwChild) +
            botanist(tolerance, subRoot->neChild) +
            botanist(tolerance, subRoot->swChild) +
            botanist(tolerance, subRoot->seChild);
    }
}

bool Quadtree::leafDifference(int tolerence, QuadtreeNode* subtreeRoot, QuadtreeNode* curr) const
{
    if(!curr->nwChild) { //If curr is a leaf node
        int difference = pow(curr->element.red - subtreeRoot->element.red, 2) +
            pow(curr->element.green - subtreeRoot->element.green, 2) +
            pow(curr->element.blue - subtreeRoot->element.blue, 2);
        return difference <= tolerence;
    } else {
        return leafDifference(tolerence, subtreeRoot, curr->nwChild) &&
            leafDifference(tolerence, subtreeRoot, curr->neChild) &&
            leafDifference(tolerence, subtreeRoot, curr->swChild) &&
            leafDifference(tolerence, subtreeRoot, curr->seChild);
    }
}

void Quadtree::rotate(QuadtreeNode* & subroot)
{
    if(!subroot)
        return;
    rotate(subroot->nwChild);
    rotate(subroot->neChild);
    rotate(subroot->swChild);
    rotate(subroot->seChild);
    QuadtreeNode* t = subroot->nwChild;
    subroot->nwChild = subroot->swChild;
    subroot->swChild = subroot->seChild;
    subroot->seChild = subroot->neChild;
    subroot->neChild = t;
}

void Quadtree::buildTreeHelper(PNG const &src, int res,
                                  int x, int y, QuadtreeNode* &subRoot)
{
    if(res > 1) {
        subRoot = new QuadtreeNode(res);
        buildTreeHelper(src, res/2, x, y, subRoot->nwChild);
        buildTreeHelper(src, res/2, x+res/2, y, subRoot->neChild);
        buildTreeHelper(src, res/2, x, y+res/2, subRoot->swChild);
        buildTreeHelper(src, res/2, x+res/2, y+res/2, subRoot->seChild);
        subRoot->element = average(subRoot);
    } else {
        subRoot = new QuadtreeNode(res, *src(x,y));
    }
}

void Quadtree::deleteTree(QuadtreeNode* & subRoot)
{
//Base Case: If subRoot is NULL, return
    if(!subRoot) return;
//Recursivly delete eash of the four children of subRoot
    deleteTree(subRoot->nwChild);
    deleteTree(subRoot->neChild);
    deleteTree(subRoot->swChild);
    deleteTree(subRoot->seChild);
//Delete rubRoot
    delete subRoot;
    subRoot = NULL;
}

void Quadtree::copy(QuadtreeNode* & curr, QuadtreeNode* const & other)
{
    if(curr == other)
        return;
    if(!other)
        curr = NULL;
    else {
        curr = new QuadtreeNode(other->resolution, other->element);
        copy(curr->nwChild,other->nwChild);
        copy(curr->neChild,other->neChild);
        copy(curr->swChild,other->swChild);
        copy(curr->seChild,other->seChild);
    }
}

RGBAPixel Quadtree::average(QuadtreeNode* node)
{
    if (!node->nwChild || !node) return RGBAPixel();
    return RGBAPixel((node->nwChild->element.red + node->neChild->element.red +
                      node->swChild->element.red + node->seChild->element.red) / 4,

                     (node->nwChild->element.green + node->neChild->element.green +
                      node->swChild->element.green + node->seChild->element.green) / 4,

                     (node->nwChild->element.blue + node->neChild->element.blue +
                      node->swChild->element.blue + node->seChild->element.blue) / 4);
}
