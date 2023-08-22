#include "MazeScene2.h"

Scene* MazeScene2::createScene()
{
    return MazeScene2::create();
}

bool MazeScene2::init()
{
  if (!MazeScene::init())
  {
    return false;
  }

  dfsVisited.resize((int)mapSize->width);

  for (int i = 0; i < (int)mapSize->width; ++i)
  {
    dfsVisited[i].resize((int)mapSize->height);
  }

  dfsPath.reserve((int)mapSize->width * (int)mapSize->height);

  bfsVisited.resize((int)mapSize->width);

  for (int i = 0; i < (int)mapSize->width; ++i)
  {
    bfsVisited[i].resize((int)mapSize->height);
  }

  bfsPath.reserve((int)mapSize->width * (int)mapSize->height);

  return true;
}

void MazeScene2::update(float dt)
{
  MazeScene::update(dt);
  drawNode->clear();

  Vec2 size = { tileSize->width, tileSize->height };

  if (dfsView)
  {
    reset(dfsVisited, dfsPath, false);
    if (int l = dfs(FlipY(enemyPosition), FlipY(playerPosition), 0); l != -1)
    {
      drawVisited(dfsVisited, Color4F::ORANGE, { 0.0f,0.0f }, size, false);
      drawPath(dfsPath, { 0.0f, 0.0f }, Color4F::RED);
    }
    else
    {
      drawVisited(dfsVisited, Color4F::ORANGE, { 0.0f,0.0f }, size, false);
    }
  }
  else if (bfsActive)
  {
    auto bfsOffset = std::pair{ 0.0f, 0.0f };

    reset(bfsVisited, bfsPath, { -1, -1 });
    if (bfs(FlipY(enemyPosition), FlipY(playerPosition)))
    {
      bfsBacktrack();
      if (bfsView)
      {
          drawVisited(bfsVisited, Color4F::GREEN, bfsOffset, size, { -1, -1 });
          drawPath(bfsPath, { 5.0f, -5.0f }, Color4F::BLUE);
      }
    }
    else
    {
      drawVisited(bfsVisited, Color4F::GREEN, bfsOffset, size, { -1, -1 });
    }
  }
}

int MazeScene2::dfs(std::pair<int, int> current, std::pair<int, int>const& target, int depth)
{
    if (current.first < 0 ||
        current.second < 0 ||
        current.first > mapSize->width - 1 ||
        current.second > mapSize->height - 1 ||
        dfsVisited[current.first][current.second] ||
        !canSetPosition(FlipY(current)))
        return -1;

    dfsVisited[current.first][current.second] = true;
    ++depth;

    if (current == target)
    {
        dfsPath.push_back({ current.first, current.second });
        return depth;
    }

    if (auto length = dfs({ current.first + 1, current.second }, target, depth) != -1)
    {
        dfsPath.push_back({ current.first, current.second });
        return length;
    }
    if (auto length = dfs({ current.first - 1, current.second }, target, depth) != -1)
    {
        dfsPath.push_back({ current.first, current.second });
        return length;
    }
    if (auto length = dfs({ current.first, current.second + 1 }, target, depth) != -1)
    {
        dfsPath.push_back({ current.first, current.second });
        return length;
    }
    if (auto length = dfs({ current.first, current.second - 1 }, target, depth) != -1)
    {
        dfsPath.push_back({ current.first, current.second });
        return length;
    }

  return -1;
}

bool MazeScene2::bfs(std::pair<int, int> current, std::pair<int, int>const& target)
{
  /// TODO: Fill in
    std::vector<std::pair<int, int>> parents = { current };
    while (parents.size() > 0)
    {
        std::vector<std::pair<int, int>> children = {};

        for (std::pair<int, int> parent : parents)
        {
            if (bfsVisitChild(parent, { parent.first + 1, parent.second }, target, children)) return true;
            if (bfsVisitChild(parent, { parent.first - 1, parent.second }, target, children)) return true;
            if (bfsVisitChild(parent, { parent.first, parent.second + 1 }, target, children)) return true;
            if (bfsVisitChild(parent, { parent.first, parent.second - 1 }, target, children)) return true;
        }
        parents = std::move(children);
    }
  return false;
}

bool MazeScene2::bfsVisitChild(std::pair<int, int> const& parent, std::pair<int, int> const& c, std::pair<int, int> const& t, std::vector<std::pair<int, int>>& children)
{
    if (c.first < 0 ||
        c.second < 0 ||
        c.first > mapSize->width - 1 ||
        c.second > mapSize->height - 1 ||
        bfsVisited[c.first][c.second] != std::pair(- 1, -1) ||
        !canSetPosition(FlipY(c)))
        return false;

    children.push_back(c);
    bfsVisited[c.first][c.second] = parent;
    if (c == t) return true;

  return false;
}

void MazeScene2::bfsBacktrack()
{
  /// TODO: Fill in
    bfsPath.push_back(FlipY(playerPosition));

    while (bfsPath.back() != FlipY(enemyPosition))
    {
        bfsPath.push_back(bfsVisited[bfsPath.back().first][bfsPath.back().second]);
    }
}