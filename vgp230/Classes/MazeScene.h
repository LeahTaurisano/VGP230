#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MazeScene : public Scene
{
public:
  virtual bool init();

  virtual void update(float dt);

  void initialize(Sprite* spr, TMXLayer* layer, std::pair<int, int>& position, bool draw = true);

  std::pair<int, int> FlipY(std::pair<int, int> position);

  void setPosition(Sprite* spr, std::pair<int, int> playerPosition, std::pair<int, int>& oldPosition, bool draw = true);

  bool canSetPosition(std::pair<int, int> playerPosition);

  void changeActiveSprite(Sprite* newActive);

  TMXLayer* path;
  TMXLayer* collision;

  std::vector<std::pair<int, int>> dfsPath;
  std::vector<std::pair<int, int>> bfsPath;
  std::pair<int, int> playerPosition;
  std::pair<int, int> endPosition;
  std::pair<int, int> enemyPosition;

  const Size* mapSize;
  const Size* tileSize;

  DrawNode* drawNode;

  bool dfsView = false;
  bool bfsView = false;
  bool bfsActive = true;

  CREATE_FUNC(MazeScene)

private:
  enum GameState
  {
    Start,
    Running,
    FoundCheese,
    Victory,
    GameOver
  } gameState = Start;

  Sprite* active;
  Sprite* ratDown;
  Sprite* ratLeft;
  Sprite* ratUp;
  Sprite* ratRight;
  Sprite* enemy;
  int enemyMoveCD = 20;
  struct Cheese
  {
      Sprite* cheese;
  };
  Cheese Collect[200];
  int cheeseIter = 0;

  float cheeseAnimationTimer = 0;

  void ResetInput();

  bool down = false;
  bool left = false;
  bool up = false;
  bool right = false;
  float rot;
};