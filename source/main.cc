/// @file main.cc
/// @author guinot Almenar, F.c.o Javier <whitewholffox@gmail.com>

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

std::vector<std::pair<int, int>> aStar(std::vector<std::vector<int>> &grid, int startX, int startY, int goalX, int goalY);

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0}
    };
    int startX = 0, startY = 0, goalX = 4, goalY = 4;
    std::vector<std::pair<int, int>> path = aStar(grid, startX, startY, goalX, goalY);

    if (path.empty()) {
        std::cout << "No path found!" << std::endl;
        return 0;
    }
    std::cout << "Shortest path from (" << startX << ", " << startY << ") to (" << goalX << ", " << goalY << "):" << std::endl;
    for (auto [x, y] : path) {
        std::cout << "(" << x << ", " << y << ") -> ";
    }
    std::cout << "DONE!" << std::endl;
    return 0;
}

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct Node {
    int x, y;
    double g, h;

    bool operator<(const Node &other) const {
        return g + h > other.g + other.h;
    }
};

double heuristic(int x1, int y1, int x2, int y2) {
    // Manhattan distance
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::vector<std::pair<int, int>> aStar(std::vector<std::vector<int>> &grid, int startX, int startY, int goalX, int goalY) {
    int n = grid.size();
    int m = grid[0].size();
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));
    std::vector<std::vector<std::pair<int, int>>> prev(n, std::vector<std::pair<int, int>>(m, {-1, -1}));

    std::priority_queue<Node> q;
    q.push({startX, startY, 0, heuristic(startX, startY, goalX, goalY)});

    while (!q.empty()) {
        Node curr = q.top();
        q.pop();
        if (curr.x == goalX && curr.y == goalY) {
            std::vector<std::pair<int, int>> path;
            for (std::pair<int, int> curr = {goalX, goalY}; curr != std::make_pair(startX, startY); curr = prev[curr.first][curr.second]) {
                path.push_back(curr);
            }
            path.push_back({startX, startY});
            reverse(path.begin(), path.end());
            return path;
        }
        if (visited[curr.x][curr.y]) {
            continue;
        }
        visited[curr.x][curr.y] = true;

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            if (grid[nx][ny] || visited[nx][ny]) {
                continue;
            }
            double ng = curr.g + 1;
            double nh = heuristic(nx, ny, goalX, goalY);
            q.push({nx, ny, ng, nh});
            prev[nx][ny] = {curr.x, curr.y};
        }
    }

    return {};
}
