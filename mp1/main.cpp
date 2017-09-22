#include "rgbapixel.h"
#include "png.h"

int main()
{
    PNG imageIn("in.png");
    PNG imageOut(imageIn);

    for(int y = 0; y < (int)imageIn.height(); y++)
    {
        for(int x = 0; x < (int)imageIn.width(); x++)
        {
           *imageOut(imageIn.width()-1 - x, imageIn.height()-1 - y) = *imageIn(x, y);
        }
    }
    imageOut.writeToFile("out.png");
}
