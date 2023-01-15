/// @author F.c.o Javier guinot Almenar <guinotal@esat-alumni.com>
/// @file astar_2d.cc

#include <astar_2d.h>

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct Node
{
  int x, y;
  double g, h;

  bool operator<(const Node &other) const
  {
    return g + h > other.g + other.h;
  }
};

double heuristic(int x1, int y1, int x2, int y2)
{
  // Manhattan distance
  return std::abs(x1 - x2) + std::abs(y1 - y2);
}

aStar2D::aStar2D()
{
  path_ = {};
  startX_ = startY_ = endX_ = endY_ = 0;
}

void aStar2D::takePath(std::vector<std::vector<int>> &grid, int startX, int startY, int endX, int endY)
{
  startX_ = startX;
  startY_ = startY;
  endX_ = endX;
  endY_ = endY;

  int n = grid.size();
  int m = grid[0].size();
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));
  std::vector<std::vector<std::pair<int, int>>> prev(n, std::vector<std::pair<int, int>>(m, {-1, -1}));

  std::priority_queue<Node> q;
  q.push({startX, startY, 0, heuristic(startX, startY, endX, endY)});

  while (!q.empty())
  {
    Node curr = q.top();
    q.pop();
    if (curr.x == endX && curr.y == endY)
    {
      // std::vector<std::pair<int, int>> path;
      for (std::pair<int, int> curr = {endX, endY}; curr != std::make_pair(startX, startY); curr = prev[curr.first][curr.second])
      {
        path_.push_back(curr);
      }
      path_.push_back({startX, startY});
      std::reverse(path_.begin(), path_.end());
      return;
    }
    if (visited[curr.x][curr.y])
    {
      continue;
    }
    visited[curr.x][curr.y] = true;

    for (int i = 0; i < 4; i++)
    {
      int nx = curr.x + dx[i];
      int ny = curr.y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m)
      {
        continue;
      }
      if (grid[nx][ny] || visited[nx][ny])
      {
        continue;
      }
      double ng = curr.g + 1;
      double nh = heuristic(nx, ny, endX, endY);
      q.push({nx, ny, ng, nh});
      prev[nx][ny] = {curr.x, curr.y};
    }
  }

  path_ = {};
}

void aStar2D::printPath()
{
  if (path_.empty())
  {
    std::cout << "Path is empty" << std::endl;
    return;
  }

  std::cout << "Shortest path from (" << startX_ << ", " << startY_ << ") to (" << endX_ << ", " << endY_ << "):" << std::endl;
  for (std::pair<int, int> cell : path_)
  {
    std::cout << "(" << cell.first << ", " << cell.second << ") -> ";
  }
}