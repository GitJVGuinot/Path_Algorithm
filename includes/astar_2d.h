/// @author F.c.o Javier guinot Almenar <guinotal@esat-alumni.com>
/// @file astar_2d.h

//////////////////////
#ifndef __ASTAR_2D_H__
#define __ASTAR_2D_H__
//////////////////////

#include <iostream>
#include <queue>
#include <algorithm>

class aStar2D
{
private:
  int startX_, startY_;
  int endX_, endY_;

public:
  std::vector<std::pair<int, int>> path_;

  aStar2D();
  void takePath(std::vector<std::vector<int>> &grid, int startX, int startY, int endX, int endY);

  void printPath();

  static void example()
  {
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0}};

    int startX = 0, startY = 0, goalX = 4, goalY = 4;
    
    aStar2D algorithm;
    algorithm.takePath(grid, startX, startY, goalX, goalY);

    algorithm.printPath();
  }
};

#endif /* __ASTAR_2D_H__ */