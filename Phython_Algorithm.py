# Athor guinot Almenar, F.c.o Javier

import heapq
from typing import List, Tuple

def aStar(grid: List[List[int]], startX: int, startY: int, goalX: int, goalY: int) -> List[Tuple[int, int]]:
    n = len(grid)
    m = len(grid[0])
    visited = [[False] * m for _ in range(n)]
    prev = [[(-1, -1) for _ in range(m)] for _ in range(n)]

    q = []
    heapq.heappush(q, (0, 0, startX, startY))
    while q:
        _, g, x, y = heapq.heappop(q)
        if x == goalX and y == goalY:
            path = []
            while (x, y) != (startX, startY):
                path.append((x, y))
                x, y = prev[x][y]
            path.append((startX, startY))
            return path[::-1]
        if visited[x][y]:
            continue
        visited[x][y] = True

        for dx, dy in [(-1, 0), (0, 1), (1, 0), (0, -1)]:
            nx, ny = x + dx, y + dy
            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                continue
            if grid[nx][ny] or visited[nx][ny]:
                continue
            h = abs(nx - goalX) + abs(ny - goalY)
            heapq.heappush(q, (g + 1 + h, g + 1, nx, ny))
            prev[nx][ny] = (x, y)
    return []

grid = [
    [0, 0, 0, 1, 0],
    [0, 1, 0, 0, 0],
    [0, 1, 0, 1, 0],
    [0, 0, 0, 1, 0],
    [1, 1, 1, 1, 0]
]
startX, startY, goalX, goalY = 0, 0, 4, 4
path = aStar(grid, startX, startY, goalX, goalY)

if not path:
    print("No path found!")
else:
    print(f"Shortest path from ({startX}, {startY}) to ({goalX}, {goalY}):")
    for x, y in path:
        print(f"({x}, {y}) ->", end=" ")
    print("DONE!")
