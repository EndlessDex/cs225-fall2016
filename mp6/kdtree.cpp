// #include "kdtree.h"
/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <cmath>
#include <random>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    return first[curDim]==second[curDim] ? first<second : first[curDim]<second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int curDif = 0, potDif = 0;
    for (int d = 0; d < Dim; d++) {
        curDif += pow(target[d] - currentBest[d], 2);
        potDif += pow(target[d] - potential[d], 2);
    }
    return potDif==curDif ? potential<currentBest : potDif<curDif;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    points = newPoints;
    if (newPoints.size() > 1)
        sort(0, 0, points.size()-1);
}

template <int Dim>
void KDTree<Dim>::sort(int dim, int min, int max)
{
    if (max <= min)
        return;

    int mIdx = floor((min+max)/2);
    select(dim, min, max, mIdx);

    sort((dim + 1) % Dim, min, mIdx - 1);
    sort((dim + 1) % Dim, mIdx + 1, max);
}

template< int Dim>
void KDTree<Dim>::select(int dim, int min, int max, int mIdx)
{
    if (min >= max)
        return;

    std::random_device rDev;
    std::mt19937 gen(rDev());
    std::uniform_int_distribution<int> distr(min, max);

    int pIdx = partition(dim, min, max, distr(gen));

    if (mIdx == pIdx)
        ;
    else if (mIdx < pIdx)
        select(dim, min, pIdx - 1, mIdx);
    else
        select(dim, pIdx + 1, max, mIdx);
}

template <int Dim>
int KDTree<Dim>::partition(int dim, int min, int max, int pIdx)
{
    auto pVal = points[pIdx];

    auto swap = points[max];
    points[max] = points[pIdx];
    points[pIdx] = swap;

    for (int i = min; i < max; i++) {
        if (smallerDimVal(points[i], pVal, dim)) {
            swap = points[i];
            points[i] = points[min];
            points[min] = swap;
            min++;
        }
    }
    swap = points[min];
    points[min] = points[max];
    points[max] = swap;

    return min;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return dingDong(query, (points.size()-1)/2, 0, points.size()-1, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::dingDong(const Point<Dim>& query, int curMed,
                                 int left, int right, int curDim) const
{
    Point<Dim> curBest;
    bool leftVisited = false;

    if (left>=right)//If at leaf
        return points[left];

    if (smallerDimVal(query, points[curMed], curDim)) {//Going left
        curBest = dingDong(query, (left+curMed-1)/2, left, curMed-1, (curDim+1) % Dim);
        leftVisited = true;
    } else //Going right
        curBest = dingDong(query, (curMed+1+right)/2, curMed+1, right, (curDim+1) % Dim);

    if (shouldReplace(query, curBest, points[curMed]))
        curBest = points[curMed];

    int bestDist = 0;
    for (int d = 0; d < Dim; d++) {
        bestDist += pow(query[d] - curBest[d], 2);
    }
    Point<Dim> pot;
    if (bestDist >= abs((int)pow(query[curDim] - points[curMed][curDim], 2))) {
        if (leftVisited)
            pot = dingDong(query, (curMed+1+right)/2, curMed+1, right, (curDim+1) % Dim);
        else
            pot = dingDong(query, (left+curMed-1)/2, left, curMed-1, (curDim+1) % Dim);

        if (shouldReplace(query, curBest, pot))
            curBest = pot;
    }

    return curBest;
}
