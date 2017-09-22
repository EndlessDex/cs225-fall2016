
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "png.h"
#include "dsets.h"
using namespace std;

class SquareMaze
{
public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
private:
    class square
    {
    public:
        //True means wall exists
        bool down = true;
        bool right = true;
        int dist = -1;
    };
    vector<vector<square>> maze;
    DisjointSets cycles;
};


#endif // MAZE_H
