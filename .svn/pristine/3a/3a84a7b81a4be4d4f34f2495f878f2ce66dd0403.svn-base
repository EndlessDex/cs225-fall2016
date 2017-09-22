#include "maze.h"
#include "dsets.h"
#include <tuple>
#include <random>
#include <queue>
#include <utility>
#include <map>
#include <iostream>
using namespace std;

SquareMaze::SquareMaze() {}

void SquareMaze::makeMaze(int width, int height)
{
    if(!maze.empty())
        maze.erase(maze.begin(), maze.end());

    vector<tuple<int, int, bool>> walls;

    for(int y = 0; y < height; y++) {
        maze.push_back(vector<square>());
        for (int x = 0; x < width; x++) {
            maze[y].push_back(square());
            //0 is right, 1 is down
            walls.push_back(make_tuple(x, y, 0));
            walls.push_back(make_tuple(x, y, 1));
        }
    }

    random_shuffle(walls.begin(), walls.end());
    cycles.addelements(width * height);

    while(!walls.empty()) {
        int x = get<0>(walls.back());
        int y = get<1>(walls.back());
        bool dir = get<2>(walls.back());
        walls.pop_back();

        if((y >= height - 1 && dir) || (x >= width - 1 && !dir))
            continue;
        int idx = width * y + x;
        int newIdx = width * (y + dir) + (x + !dir);

        if(cycles.find(idx) == cycles.find(newIdx)) //If in same cycle dont make wall
            continue;
        cycles.setunion(idx, newIdx);
        setWall(x,y,dir,false);
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if(dir == 0) {
        if(x >= (int)maze[0].size() - 1 || maze[y][x].right)
            return false;
    } else if(dir == 1) {
        if(y >= (int)maze.size() - 1 || maze[y][x].down)
            return false;
    } else if(dir == 2) {
        if(x == 0 || maze[y][x-1].right)
            return false;
    } else {
        if(y == 0 || maze[y-1][x].down)
            return false;
    }
    return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
        if(dir)
            maze[y][x].down = exists;
        else
            maze[y][x].right = exists;
}

vector<int> SquareMaze::solveMaze()
{
    map<pair<int,int>, pair<int,int>> bestPath;
    pair<int,int> bestEnd;
    int bestDist = 0;
    maze[0][0].dist = 0;

    for(size_t xit = 0; xit < maze[0].size(); xit++) {
        queue<pair<int, int>> bfs;
        bfs.push(make_pair(0, 0));

        pair<int,int> target(xit,maze.size() - 1);

        map<pair<int,int>, pair<int,int>> path;
        path[make_pair(0, 0)] = make_pair(0, 0);

        // cout << "Target: " << target.first << ','<< target.second << "\n";
        while (!bfs.empty()) {
            if(bfs.front() == target) {
                if(maze[target.second][target.first].dist > bestDist) {
                    bestDist = maze[target.second][target.first].dist;
                    bestPath = path;
                    bestEnd = bfs.front();
                }
                break;
            }
            pair<int,int> curr = bfs.front();
            bfs.pop();

            // cout << "Curr: "<< curr.first<< ',' << curr.second  << "\n";
            if(canTravel(curr.first, curr.second, 0)){
                pair<int,int> right(curr.first + 1, curr.second);
                if(path.find(right) == path.end()) {
                    path[right] = curr;
                    bfs.push(right);
                    maze[right.second][right.first].dist =
                        maze[curr.second][curr.first].dist + 1;
                }
            }
            if(canTravel(curr.first, curr.second, 1)){
                pair<int,int> down(curr.first, curr.second + 1);
                if(path.find(down) == path.end()) {
                    path[down] = curr;
                    bfs.push(down);
                    maze[down.second][down.first].dist =
                        maze[curr.second][curr.first].dist + 1;
                }
            }
            if(canTravel(curr.first, curr.second, 2)) {
                pair<int,int> left(curr.first - 1, curr.second);
                if(path.find(left) == path.end()) {
                    path[left] = curr;
                    bfs.push(left);
                    maze[left.second][left.first].dist =
                        maze[curr.second][curr.first].dist + 1;
                }
            }
            if(canTravel(curr.first, curr.second, 3)) {
                pair<int,int> up(curr.first, curr.second - 1);
                if(path.find(up) == path.end()) {
                    path[up] = curr;
                    bfs.push(up);
                    maze[up.second][up.first].dist =
                        maze[curr.second][curr.first].dist + 1;
                }
            }
        }
    }
    vector<int> ret;
    auto curr = bestEnd;
    pair<int,int> prev;

    // cout << "bestEnd: " << bestEnd.first << "," << bestEnd.second << '\n';
    // cout << "bestDist: " << bestDist << '\n';
    while ((int)ret.size() < bestDist) {
        prev = bestPath.at(curr);
        // cout << "curr: " << curr.first << "," << curr.second<< "\t\t" << ret.size()<< '\n';
        if (curr.first > prev.first) {
            ret.push_back(0);
        } else if (curr.second > prev.second) {
            ret.push_back(1);
        } else if (curr.first < prev.first) {
            ret.push_back(2);
        } else {
            ret.push_back(3);
        }
        curr = prev;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

PNG* SquareMaze::drawMaze() const
{
    PNG* ret = new PNG(maze[0].size()*10 + 1, maze.size()*10 + 1);

    for(size_t i = 0; i < ret->height(); i++)
        *(*ret)(0, i) = RGBAPixel(0, 0, 0);

    for(size_t i = 10; i < ret->width(); i++)
        *(*ret)(i, 0) = RGBAPixel(0, 0, 0);

    for(size_t y = 0; y < maze.size(); y++) {
        for(size_t x = 0; x < maze[0].size(); x++) {
            if(maze[y][x].right) {
                for(int i = 0; i <= 10; i++)
                    *(*ret)((x + 1) * 10, (y * 10) + i) = RGBAPixel(0,0,0);
            }
            if(maze[y][x].down) {
                for(int i = 0; i <=10; i++)
                    *(*ret)((x * 10) + i, (y + 1) * 10) = RGBAPixel(0,0,0);
            }
        }
    }
    return ret;
}

PNG* SquareMaze::drawMazeWithSolution()
{
    PNG* ret = drawMaze();
    vector<int> path = solveMaze();

    pair<int,int> pen(5,5);

    while(!path.empty()) {
        // cout << "pen: " << pen.first << ',' << pen.second <<"\t\t"<<path.front() << "\n";


        if(path.front() == 0) {
            for(int i = 0; i < 10; i++) {
                *(*ret)(pen.first, pen.second) = RGBAPixel(255, 0, 0);
                pen.first++;
            }
        } else if(path.front() == 1) {
            for(int i = 0; i < 10; i++) {
                *(*ret)(pen.first, pen.second) = RGBAPixel(255, 0, 0);
                pen.second++;
            }
        } else if(path.front() == 2) {
            for(int i = 0; i < 10; i++) {
                *(*ret)(pen.first, pen.second) = RGBAPixel(255, 0, 0);
                pen.first--;
            }
        } else {
            for(int i = 0; i < 10; i++) {
                *(*ret)(pen.first, pen.second) = RGBAPixel(255, 0, 0);
                pen.second--;
            }
        }
        path.erase(path.begin());
    }

    *(*ret)(pen.first, pen.second) = RGBAPixel(255, 0, 0);

    pen.first -=4;
    pen.second +=5;
    for(int i = 1; i < 10; i++) {
        *(*ret)(pen.first, pen.second) = RGBAPixel(255, 255, 255);
        pen.first++;
    }

    return ret;
}
