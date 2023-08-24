#pragma once

#include "cocos2d.h"
#include "KeyboardControllerComponent.h"

USING_NS_CC;

class HelloMarioSolution : public Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  virtual void update(float dt);

  CREATE_FUNC(HelloMarioSolution)
protected:
  float walkSpeed = 256.0f;
  float walkFrameDelay = 1.0f / 16.0f;
  float idleFrameDelay = 1.5f;
  float jumpFrameDelay = 1.5f;
  float fallFrameDelay = 1.5f;
  float jumpSpeed = 640.0f;
  float scale = 2.0f;
  Vec2 startPosition {512.0f, 384.0f};

  Vec2 GetMarioPosition() const
  {
    return mario->getPosition();
  }
private:
  enum AnimationState
  {
    Idle,
    Walking,
    Jumping,
    Falling
  } animationState = Idle;

  Vector<SpriteFrame*> idleFrames;
  Vector<SpriteFrame*> walkingFrames;
  Vector<SpriteFrame*> jumpingFrames;
  Vector<SpriteFrame*> fallingFrames;
  Sprite* mario;
  PhysicsBody* marioPhysicsBody;
  std::vector<PhysicsBody*> contacts;
  KeyboardControllerComponent* controller;
  bool contact = false;
};