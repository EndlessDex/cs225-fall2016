#include "image.h"
#include <cmath>

using namespace std;

void Image::flipleft()
{
    RGBAPixel temp;

    for(int y = 0; y < (int) height(); y++)
    {
        for(int x = 0; x < (int) floor(width()/2); x++)
        {
            temp = *((*this)(x,y));
            *((*this)(x,y)) = *((*this)(width()-1-x,y));
            *((*this)(width()-1-x,y)) = temp;
        }
    }
}

void Image::adjustbrightness(int r, int g, int b)
{
    for(int y = 0; y < (int) height(); y++)
    {
        for(int x = 0; x < (int) width(); x++)
        {
            (*this)(x,y)->red = max(min((*this)(x,y)->red + r, 255),0);
            (*this)(x,y)->green = max(min((*this)(x,y)->green + g, 255),0);
            (*this)(x,y)->blue = max(min((*this)(x,y)->blue + b, 255),0);
        }
    }
}

void Image::invertcolors()
{
    for(int y = 0; y < (int) height(); y++)
    {
        for(int x = 0; x < (int) width(); x++)
        {
            (*this)(x,y)->red = 255 - (*this)(x,y)->red;
            (*this)(x,y)->green = 255 - (*this)(x,y)->green;
            (*this)(x,y)->blue = 255 - (*this)(x,y)->blue;
        }
    }
}
