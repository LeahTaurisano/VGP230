#include "Assignment1.h"

Scene* Assignment1::createScene()
{
    return Assignment1::create();
}

bool Assignment1::init()
{
    if (!Scene::init())
    {
        return false;
    }
     
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    sprite1 = Sprite::create("bullet2.png");
    sprite1->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(sprite1, 0);
    this->scheduleUpdate();

    return true;
}

void Assignment1::update(float dt)
{
    sprite1->setPosition(Vec2(sprite1->getPosition().x + 1, sprite1->getPosition().y + 1));
}