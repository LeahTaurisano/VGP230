#include "MazeScene.h"

bool MazeScene::init()
{
  auto map = TMXTiledMap::create("tmx/desert.tmx");
  path = map->getLayer("Path");
  collision = map->getLayer("Collision");
  auto playerStartLayer = map->getLayer("Player");
  auto playerEndLayer = map->getLayer("Player End");

  mapSize = &path->getLayerSize();
  tileSize = &path->getMapTileSize();

  this->addChild(map);

  map->setScale(1.5f);

  ratUp = Sprite::create("mouse-0.png");     //0, 1, 2
  ratUp->setVisible(false);
  ratRight = Sprite::create("mouse-3.png");  //3, 4, 5
  ratDown = Sprite::create("mouse-6.png");   //6, 7, 8
  ratDown->setVisible(false);
  ratLeft = Sprite::create("mouse-9.png");   //9, 10, 11
  ratLeft->setVisible(false);

  cheese = Sprite::create("Cheese.png");

  drawNode = DrawNode::create();

  map->addChild(ratUp, 5);
  map->addChild(ratRight, 5);
  map->addChild(ratDown, 5);
  map->addChild(ratLeft, 5);
  map->addChild(drawNode, 4);
  map->addChild(cheese, 4);

  active = ratRight;

  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
  {
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
      left = true;
      break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
      right = true;
      break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
      down = true;
      break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
      up = true;
      break;
    };
  };

  _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

  this->scheduleUpdate();

  initialize(active, playerStartLayer, playerPosition);
  initialize(cheese, playerEndLayer, endPosition, false);

  playerStartLayer->setVisible(false);
  playerEndLayer->setVisible(false);

  gameState = Running;

  return true;
}

void MazeScene::initialize(Sprite* spr, TMXLayer* layer, std::pair<int, int>& position, bool draw)
{
  /// TODO: Loop over all layer tiles, 
    /// check if is starting tile
      /// Call setPosition(spr, FlipY(std::make_pair(i, j)), position, draw); 
    for (int i = 0; i < layer->getLayerSize().width; ++i)
    {
        for (int j = 0; j < layer->getLayerSize().height; ++j)
        {
            if (layer->getTileAt(Vec2(i, j)) != NULL) setPosition(spr, FlipY(std::make_pair(i, j)), position, draw);
        }
    }
}

std::pair<int, int> MazeScene::FlipY(std::pair<int, int> position)
{
  /// TODO: Calculate tile location, -- Cocos2d-x rendering has bottom left as origin, -- while TMX grid map has it at top left
  return std::make_pair(position.first, mapSize->height - position.second - 1);
}

void MazeScene::setPosition(Sprite* spr, std::pair<int, int> newPosition, std::pair<int, int>& oldPosition, bool draw)
{
  oldPosition = newPosition;

  /// TODO: Calculate new x/y of sprite
  auto x = tileSize->width * newPosition.first + (tileSize->width / 2);
  auto y = tileSize->height * newPosition.second + (tileSize->height / 2);

  /// TODO: Add sprite bounding box offsets

  /// TODO: Set spr to that position
  spr->setPosition(Vec2(x, y));

  if (draw)
  {
    /// TODO: Add drawing of rectangle around "spr"
  }
}

bool MazeScene::canSetPosition(std::pair<int, int> p)
{
  /// TODO: determine if location can be walked on
  auto flippedP = FlipY(p);
  if (flippedP.first < 0 || flippedP.first >= path->getLayerSize().width) return false;
  if (flippedP.second < 0 || flippedP.second >= path->getLayerSize().height) return false;
  if (path->getTileAt(Vec2(flippedP.first, flippedP.second)) == NULL) return false;
  return true;
}

void MazeScene::update(float dt)
{
  /// TODO: Check if game state is running
  if (gameState == Running)
  {
    if (down)
    {
      /// TODO: fix line below and determine correct new location
      auto p = std::make_pair(playerPosition.first, playerPosition.second - 1);
      if (canSetPosition(p))
      {
        /// TODO: call Change Active Sprite
        changeActiveSprite(ratDown);
        setPosition(active, p, playerPosition);
      }
      else
      {
          changeActiveSprite(ratDown);
          setPosition(active, playerPosition, playerPosition);
      }
    }
    else if (left)
    {
      /// TODO: fix line below and determine correct new location
      auto p = std::make_pair(playerPosition.first - 1, playerPosition.second);
      if (canSetPosition(p))
      {
        /// TODO: call Change Active Sprite
        changeActiveSprite(ratLeft);
        setPosition(active, p, playerPosition);
      }
      else
      {
          changeActiveSprite(ratLeft);
          setPosition(active, playerPosition, playerPosition);
      }
    }
    else if (up)
    {
      /// TODO: fix line below and determine correct new location
      auto p = std::make_pair(playerPosition.first, playerPosition.second + 1);
      if (canSetPosition(p))
      {
        /// TODO: call Change Active Sprite
        changeActiveSprite(ratUp);
        setPosition(active, p, playerPosition);
      }
      else
      {
          changeActiveSprite(ratUp);
          setPosition(active, playerPosition, playerPosition);
      }
    }
    else if (right)
    {
      /// TODO: fix line below and determine correct new location
      auto p = std::make_pair(playerPosition.first + 1, playerPosition.second);
      if (canSetPosition(p))
      {
        /// TODO: call Change Active Sprite
        changeActiveSprite(ratRight);
        setPosition(active, p, playerPosition);
      }
      else
      {
          changeActiveSprite(ratRight);
          setPosition(active, playerPosition, playerPosition);
      }
    }

    /// TODO: check if player has reached the end position, and change game state
    if (active->getPosition() == cheese->getPosition())
    {
        ratUp->setScale(1.3);
        ratUp->setPosition(active->getPosition());
        ratDown->setPosition(active->getPosition());
        ratDown->setScale(1.5);
        ratLeft->setPosition(active->getPosition());
        ratLeft->setScale(1.5);
        ratRight->setPosition(active->getPosition());
        ratRight->setScale(1.5);
        gameState = FoundCheese;
    }
  }
  /// TODO: check if game state has found the cheese, and apply some victory effect
  if (gameState == FoundCheese)
  {
     if (rot > 0.5 && active == ratUp) changeActiveSprite(ratRight);
     else if (rot > 0.5 && active == ratRight) changeActiveSprite(ratDown);
     else if (rot > 0.5 && active == ratDown) changeActiveSprite(ratLeft);
     else if (rot > 0.5 && active == ratLeft) changeActiveSprite(ratUp);
     if (rot > 0.5) rot = 0;
     rot += dt;
  }
  ResetInput();
}

void MazeScene::changeActiveSprite(Sprite* newActive)
{
  /// hide "active", then assign active to newActive, then make visible!
    if (active == newActive) return;
    active->setVisible(false);
    active = newActive;
    active->setVisible(true);
}

void MazeScene::ResetInput()
{
  down = false;
  left = false;
  up = false;
  right = false;
}

