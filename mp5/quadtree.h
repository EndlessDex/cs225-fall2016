/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
public:
    Quadtree();
    Quadtree(PNG const &source, int resolution);
    Quadtree(Quadtree const &other);
    ~Quadtree();

    Quadtree const & operator=(Quadtree const &other);
    void buildTree(PNG const &source, int resolution);
    RGBAPixel getPixel(int x, int y) const;
    PNG decompress() const;
    void clockwiseRotate();
    void prune(int tolerance);
    int pruneSize(int tolerance) const;
    int idealPrune(int numLeaves) const;
private:
    class QuadtreeNode
    {
    public:
        QuadtreeNode* nwChild = NULL; /**< pointer to northwest child */
        QuadtreeNode* neChild = NULL; /**< pointer to northeast child */
        QuadtreeNode* swChild = NULL; /**< pointer to southwest child */
        QuadtreeNode* seChild = NULL; /**< pointer to southeast child */

        int resolution; //Size of block attached to node
        RGBAPixel element; /**< the pixel stored as this node's "data" */

        QuadtreeNode(int res, RGBAPixel e = RGBAPixel()):resolution(res), element(e) {}
    };
//--------------------------------------
//Helper Functions
//--------------------------------------
    void deleteTree(QuadtreeNode* & subRoot);
    void buildTreeHelper(PNG const &src, int res, int x, int y,
                                  QuadtreeNode* &subRoot);
    void copy(QuadtreeNode* & curr, QuadtreeNode* const & other);
    RGBAPixel average(QuadtreeNode* node);
    void rotate(QuadtreeNode* & subroot);
    bool leafDifference(int tolerance, QuadtreeNode* root, QuadtreeNode* curr) const;
    void arborist(int tolerance, QuadtreeNode* subRoot);
    int botanist(int tolerance, QuadtreeNode* subRoot) const;
//--------------------------------------
//Member Variables
//--------------------------------------
    QuadtreeNode* root = NULL; /**< pointer to root of quadtree */

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
