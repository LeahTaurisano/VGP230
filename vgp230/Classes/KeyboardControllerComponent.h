#pragma once

#include "cocos2d.h"

USING_NS_CC;

class KeyboardControllerComponent : public Component
{
public:
  typedef int KeyboardInputType;
  static constexpr int WASD = 0;
  static constexpr int ARROWS = 1;

  static KeyboardControllerComponent* create(const KeyboardInputType& type)
  {
    auto controller = new KeyboardControllerComponent(type);
    controller->init();
    controller->autorelease();
    return controller;
  }

  KeyboardControllerComponent(const KeyboardInputType& type)
  {
    if (type == WASD)
    {
      leftKeyCode = EventKeyboard::KeyCode::KEY_A;
      rightKeyCode = EventKeyboard::KeyCode::KEY_D;
      upKeyCode = EventKeyboard::KeyCode::KEY_W;
      downKeyCode = EventKeyboard::KeyCode::KEY_S;
    }
    else
    {
      leftKeyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
      rightKeyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
      upKeyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
      downKeyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
    }
  }

  virtual bool init()
  {
    _name = "KeyboardControllerComponent";
    return true;
  }

  void initInput()
  {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
      if (keyCode == leftKeyCode)
      {
        left = true;
      }
      else if (keyCode == rightKeyCode)
      {
        right = true;
      }
      else if (keyCode == upKeyCode)
      {
        up = true;
      }
      else if (keyCode == downKeyCode)
      {
        down = true;
      }
    };
    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
      if (keyCode == leftKeyCode)
      {
        left = false;
      }
      else if (keyCode == rightKeyCode)
      {
        right = false;
      }
      else if (keyCode == upKeyCode)
      {
        up = false;
      }
      else if (keyCode == downKeyCode)
      {
        down = false;
      }
    };

    auto scene = this->getOwner()->getScene();
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, scene);
  }

  bool IsLeftPressed()
  {
    return left;
  }

  bool IsRightPressed()
  {
    return right;
  }

  bool IsUpPressed()
  {
    return up;
  }

  bool IsDownPressed()
  {
    return down;
  }
private:
  EventKeyboard::KeyCode leftKeyCode;
  EventKeyboard::KeyCode rightKeyCode;
  EventKeyboard::KeyCode upKeyCode;
  EventKeyboard::KeyCode downKeyCode;
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
};