/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    int rowNum = theSource.getRows();
    int colNum = theSource.getColumns();
    auto mc = new MosaicCanvas(rowNum, colNum);
    vector<Point<3>> pts;
    map<Point<3>, TileImage> dict;

    for(auto it : theTiles) {
        Point<3> myPt(it.getAverageColor().red,
                      it.getAverageColor().green,
                      it.getAverageColor().blue);
        pts.push_back(myPt);
        dict[myPt] = it;
    }

    KDTree<3> kd(pts);

    for (int y = 0; y < colNum; y++) {
        for (int x = 0; x < rowNum; x++) {
            RGBAPixel pxl = theSource.getRegionColor(x, y);
            Point<3> query(pxl.red, pxl.green, pxl.blue);
            TileImage img = dict.at(kd.findNearestNeighbor(query));
            mc->setTile(x, y, img);
        }
    }
    return mc;
}
