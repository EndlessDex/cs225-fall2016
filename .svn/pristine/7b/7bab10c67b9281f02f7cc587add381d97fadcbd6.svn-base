/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
// #include "filler.h"

animation filler::dfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                                 int tolerance, int frameFreq)
{
    solidColorPicker arbitrary(fillColor);
    return filler::dfs::fill(img, x, y, arbitrary, tolerance, frameFreq);
}

animation filler::dfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                                int gridSpacing, int tolerance, int frameFreq)
{
    gridColorPicker arbitrary(gridColor, gridSpacing);
    return filler::dfs::fill(img, x, y, arbitrary, tolerance, frameFreq);
}

animation filler::dfs::fillGradient(PNG& img, int x, int y,
                                    RGBAPixel fadeColor1, RGBAPixel fadeColor2,
                                    int radius, int tolerance, int frameFreq)
{
    gradientColorPicker arbitrary(fadeColor1, fadeColor2, radius, x, y);
    return filler::dfs::fill(img, x, y, arbitrary, tolerance, frameFreq);
}

animation filler::dfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
                            int tolerance, int frameFreq)
{
    return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                                 int tolerance, int frameFreq)
{
    solidColorPicker arbitrary(fillColor);
    return filler::bfs::fill(img, x, y, arbitrary, tolerance, frameFreq);
}

animation filler::bfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                                int gridSpacing, int tolerance, int frameFreq)
{
    gridColorPicker arbitrary(gridColor, gridSpacing);
    return filler::bfs::fill(img, x, y, arbitrary, tolerance, frameFreq);
}

animation filler::bfs::fillGradient(PNG& img, int x, int y,
                                    RGBAPixel fadeColor1, RGBAPixel fadeColor2,
                                    int radius, int tolerance, int frameFreq)
{
    gradientColorPicker arbitrary(fadeColor1, fadeColor2, radius, x, y);
    return filler::bfs::fill(img, x, y, arbitrary, tolerance, frameFreq);
}

animation filler::bfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
                            int tolerance, int frameFreq)
{
    return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

class pixel
{
public:
    pixel():pxPtr(NULL), posX(-1), posY(-1), visited(false) {}
    RGBAPixel* pxPtr;
    int posX;
    int posY;
    bool visited;
    void print() { printf("(%d,%d) %s\n", posX, posY, visited ? "t" : "f"); }
};

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       int tolerance, int frameFreq)
{
// Creating 2D array of pixel type
    pixel** pxlArray = new pixel*[img.height()];
    for (int i = 0; i < (int)img.height(); i++) {
        pxlArray[i] = new pixel[img.width()];
    }
// Initializing pxlArray with pointers to img and location information
    for(int k = 0; k < (int)img.height(); k++){
        for (int j = 0; j < (int)img.width(); j++) {
            pxlArray[k][j].pxPtr = img(j,k);
            pxlArray[k][j].posX = j;
            pxlArray[k][j].posY = k;
            pxlArray[k][j].visited = false;
        }
    }
// Place the starting pixel into the structure and
    // initialize counter, origColor, and animation
    OrderingStructure<pixel*> myList;
    myList.add(&pxlArray[y][x]);
    int counter = 0;
    RGBAPixel origColor = *img(x,y);
    animation coolness;

    while(!myList.isEmpty()) {
        pixel* curr = myList.remove();
        // curr->print();
        // curr->print();
        int colorDist =
            pow(curr->pxPtr->red - origColor.red, 2) +
            pow(curr->pxPtr->green - origColor.green, 2) +
            pow(curr->pxPtr->blue - origColor.blue, 2);

        if(!curr->visited && colorDist <= tolerance) {
            curr->visited = true;
            *curr->pxPtr = fillColor(curr->posX,curr->posY);
            counter++;
            if(counter % frameFreq == 0)
                coolness.addFrame(img);

            if(curr->posX + 1 < (int)img.width())
                myList.add(&pxlArray[curr->posY][curr->posX + 1]);

            if(curr->posY + 1 < (int)img.height())
                myList.add(&pxlArray[curr->posY + 1][curr->posX]);

            if(curr->posX - 1 >= 0)
                myList.add(&pxlArray[curr->posY][curr->posX - 1]);

            if(curr->posY - 1 >= 0)
                myList.add(&pxlArray[curr->posY - 1][curr->posX]);
        }
    }

    for(int i = 0; i < (int)img.height(); i++){
        delete [] pxlArray[i];
    }
    delete [] pxlArray;

    return coolness;
}
