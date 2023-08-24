#include "Week7_HelloMarioSolution.h"
#include "Week6_AnimationDemo.h"


Scene* HelloMarioSolution::createScene()
{
  auto ret = new (std::nothrow) HelloMarioSolution();
  if (ret && ret->initWithPhysics() && ret->init())
  {
    ret->autorelease();
    return ret;
  }
  else
  {
    CC_SAFE_DELETE(ret);
    return nullptr;
  }

  return ret;
}

bool HelloMarioSolution::init()
{
  if (!cocos2d::Scene::init())
  {
    return false;
  }

  auto visibleSize = _director->getVisibleSize();
  auto origin = _director->getVisibleOrigin();

  auto level = TMXTiledMap::create("Mario/tmx/MarioSampleLevel.tmx");

  this->addChild(level);

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Mario/mario.plist");
  walkingFrames = AnimationDemo::getAnimation("mario_walk_%02d", 3);
  idleFrames = AnimationDemo::getAnimation("mario_idle_%02d", 2);
  fallingFrames = AnimationDemo::getAnimation("mario_fall_%02d", 1);
  jumpingFrames = AnimationDemo::getAnimation("mario_jump_%02d", 1);

  mario = Sprite::createWithSpriteFrame(idleFrames.front());
  addChild(mario);
  //mario->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
  mario->setPosition(startPosition.x, startPosition.y);
  mario->setScale(scale);

  auto animation = Animation::createWithSpriteFrames(idleFrames, 1.0f);
  mario->runAction(RepeatForever::create(Animate::create(animation)));

  controller = KeyboardControllerComponent::create(KeyboardControllerComponent::ARROWS);
  mario->addComponent(controller);
  controller->initInput();

  auto physicsWorld = getPhysicsWorld();
  physicsWorld->setGravity(cocos2d::Vec2(0, -980));
  physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

  marioPhysicsBody = cocos2d::PhysicsBody::createBox(mario->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
  marioPhysicsBody->setRotationEnable(false);
  marioPhysicsBody->setDynamic(true);
  mario->setPhysicsBody(marioPhysicsBody);
  marioPhysicsBody->setCategoryBitmask(1);
  marioPhysicsBody->setCollisionBitmask(2);
  marioPhysicsBody->setContactTestBitmask(2);

  contacts.reserve(5);

  auto collisionLayer = level->getLayer("Collision");
  for (int row = 0; row < level->getMapSize().height; ++row) 
  {
    for (int col = 0; col < level->getMapSize().width; ++col) 
    {
      auto tile = collisionLayer->getTileAt(cocos2d::Vec2(col, row));
      if (tile) 
      {
        auto physicsBody = cocos2d::PhysicsBody::createBox(tile->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
        physicsBody->setDynamic(false);
        physicsBody->setCategoryBitmask(2);
        physicsBody->setCollisionBitmask(1);
        physicsBody->setContactTestBitmask(1);
        tile->setPhysicsBody(physicsBody);
      }
    }
  }

  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool
  {
    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();

    auto other = marioPhysicsBody == a ? b : a;

    if (marioPhysicsBody->getPosition().y > other->getPosition().y && abs(contact.getContactData()->normal.y) > 0.9f)
    {
      contacts.push_back(other);
    }

    return true;
  };
  contactListener->onContactSeparate = [=](PhysicsContact& contact)
  {
    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();

    auto separate = marioPhysicsBody == a ? b : a;

    for (int i = 0; i < contacts.size(); ++i)
    {
      if (contacts[i] == separate)
      {
        contacts[i] = contacts[contacts.size() - 1];
        contacts.pop_back();
        break;
      }
    }
  };
  _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

  scheduleUpdate();

  return true;
}

void HelloMarioSolution::update(float dt)
{
  auto contact = contacts.size() > 0;

  if (contact)
  {
    if (controller->IsLeftPressed())
    {
      auto pos = mario->getPosition() - Vec2{ walkSpeed * dt, 0.0f };
      mario->setPosition(pos);
      mario->setScaleX(-scale);

      if (animationState != Walking)
      {
        animationState = Walking;
        mario->stopAllActions();
        mario->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(walkingFrames, walkFrameDelay))));
      }
    }
    else if (controller->IsRightPressed())
    {
      auto pos = mario->getPosition() + Vec2{ walkSpeed * dt, 0.0f };
      mario->setPosition(pos);
      mario->setScaleX(scale);

      if (animationState != Walking)
      {
        animationState = Walking;
        mario->stopAllActions();
        mario->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(walkingFrames, walkFrameDelay))));
      }
    }
    
    if (controller->IsDownPressed())
    {

    }
    
    if (controller->IsUpPressed())
    {
      if (animationState != Jumping)
      {
        mario->getPhysicsBody()->applyImpulse({ 0.0f, jumpSpeed * mario->getPhysicsBody()->getMass() });
        animationState = Jumping;
        mario->stopAllActions();
        mario->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(jumpingFrames, jumpFrameDelay))));
      }
    }

    if (!controller->IsLeftPressed() && !controller->IsRightPressed() && !controller->IsDownPressed() && !controller->IsUpPressed())
    {
      if (animationState != Idle)
      {
        animationState = Idle;
        mario->stopAllActions();
        mario->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(idleFrames, idleFrameDelay))));
      }
    }
  }
  else
  {
    if (controller->IsLeftPressed())
    {
      auto pos = mario->getPosition() - Vec2{ walkSpeed * dt, 0.0f };
      mario->setPosition(pos);
      mario->setScaleX(-scale);
    }
    else if (controller->IsRightPressed())
    {
      auto pos = mario->getPosition() + Vec2{ walkSpeed * dt, 0.0f };
      mario->setPosition(pos);
      mario->setScaleX(scale);
    }

    if (animationState != Falling && mario->getPhysicsBody()->getVelocity().y < 0)
    {
      animationState = Falling;
      mario->stopAllActions();
      mario->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(fallingFrames, fallFrameDelay))));
    }
  }

  auto& position = mario->getPosition();
  this->_defaultCamera->setPosition(position);
}