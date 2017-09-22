#include "scene.h"
#include <algorithm>
#include <iostream>
using namespace std;
//----------------------------Constructor/Deconstructor
Scene::Scene(int max)
{
    maxSize = max;
    imageArray = new data[maxSize];
    nullify();
}

Scene::~Scene()
{
    clear();
}

Scene::Scene(const Scene &source)
{
    maxSize = source.maxSize;
    copy(source);
}
//----------------------------Helper Functions
void Scene::copy(const Scene &source)
{
    imageArray = new data[maxSize];
    //Initialize all elements to null
    nullify();
    //Copy active source elements to target
    for(int i = 0; i < source.maxSize; i++)
    {
        if(source.imageArray[i].pic == NULL)
            continue;
        imageArray[i].pic = new Image;
        *(imageArray[i].pic) = *(source.imageArray[i].pic);
        imageArray[i].x = source.imageArray[i].x;
        imageArray[i].y = source.imageArray[i].y;
    }
}

void Scene::nullify()
{
    for(int i = 0; i < maxSize; i++)
    {
        imageArray[i].pic = NULL;
        imageArray[i].x = -1;
        imageArray[i].y = -1;
    }
}

void Scene::clear()
{
    for(int i = 0; i < maxSize; i++)
        delete imageArray[i].pic;
    delete [] imageArray;
}
//----------------------------Overload Operators
const Scene& Scene::operator=(const Scene &source)
{
    if(imageArray != source.imageArray)
    {
        clear();
        maxSize = source.maxSize;
        copy(source);
    }
    return *this;
}
//----------------------------Methods
void Scene::changemaxlayers(int newmax)
{
    //If newmax < maxSize, check if any cut-off images are non-NULL
    if(newmax < maxSize)
    {
        for(int i = newmax; i < maxSize; i++)
        {
            if(imageArray[i].pic != NULL)
            {
                cout << "invalid newmax" << endl;
                return;
            }
        }
    }

    Scene temp(*this);
    clear();
    maxSize = newmax;
    copy(temp);
}

void Scene::addpicture(const char* FileName, int index, int x, int y)
{
    if(index < 0 || index > maxSize-1)
    {
        cout << "index out of bounds" << endl;
        return;
    }

    imageArray[index].pic = new Image;
    imageArray[index].pic->readFromFile(FileName);
    imageArray[index].x = x;
    imageArray[index].y = y;
}

void Scene::changelayer(int index, int newindex)
{
    if(index < 0 || index > maxSize-1 || newindex < 0 || newindex > maxSize-1)
    {
        std::cout << "invalid index" << endl;
        return;
    }
    if(index == newindex)
        return;
    if(imageArray[newindex].pic != NULL)
        delete imageArray[newindex].pic;

    imageArray[newindex] = imageArray[index];
    imageArray[index].pic = NULL;
    imageArray[index].x = -1;
    imageArray[index].y = -1;
}

void Scene::translate(int index, int xcoord, int ycoord)
{
    if(index < 0 || index > maxSize-1 || imageArray[index].pic == NULL)
    {
        cout << "invalid index" << endl;
        return;
    }
    imageArray[index].x = xcoord;
    imageArray[index].y = ycoord;
}

void Scene::deletepicture(int index)
{
    if(index < 0 || index > maxSize-1 || imageArray[index].pic == NULL)
    {
        cout << "invalid index" << endl;
        return;
    }

    delete imageArray[index].pic;
    imageArray[index].pic = NULL;
    imageArray[index].x = -1;
    imageArray[index].y = -1;
}

Image* Scene::getpicture(int index) const
{
    if(index < 0 || index > maxSize-1)
    {
        cout << "invalid index" << endl;
        return NULL;
    }
    return imageArray[index].pic;
}

Image Scene::drawscene() const
{
    int maxWidth = 0;
    int maxHeight = 0;
    for(int i = 0; i < maxSize; i++)
    {
        if(imageArray[i].pic == NULL)
            continue;
        int currWidth = imageArray[i].x + imageArray[i].pic->width();
        maxWidth = max(maxWidth, currWidth);
        int currHeight = imageArray[i].y + imageArray[i].pic->height();
        maxHeight = max(maxHeight, currHeight);
    }
    Image out;
    out.resize(maxWidth, maxHeight);

    for(int i = 0; i < maxSize; i++)
    {
        if(imageArray[i].pic == NULL)
            continue;
        for(int y = 0; y < (int)imageArray[i].pic->height(); y++)
        {
            for(int x = 0; x < (int)imageArray[i].pic->width(); x++)
            {
                *out(x+imageArray[i].x, y+imageArray[i].y) = *(imageArray[i].pic->operator()(x, y));
            }

        }
    }
    return out;
}
