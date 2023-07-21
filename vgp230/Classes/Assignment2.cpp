#include "Assignment2.h"

bool movingLeft = false, movingRight = false, movingUp = false, movingDown = false, isFiring = false;

Scene* Assignment2::createScene()
{
    return Assignment2::create();
}

bool Assignment2::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    sprite1 = Sprite::create("fighter.png");
    sprite1->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(sprite1, 0);

    healthBar = Sprite::create("bar_red.png");
    healthBar->setScale(.5);
    healthBar->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y - sprite1->getContentSize().height / 2));
    this->addChild(healthBar, 0);



    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_A:
            movingLeft = true;
            break;

        case EventKeyboard::KeyCode::KEY_D:
            movingRight = true;
            break;

        case EventKeyboard::KeyCode::KEY_W:
            movingUp = true;
            break;

        case EventKeyboard::KeyCode::KEY_S:
            movingDown = true;
            break;

        case EventKeyboard::KeyCode::KEY_SPACE:
            isFiring = true;
            break;

        default:
            break;
        }
    };

    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_A:
            movingLeft = false;
            break;

        case EventKeyboard::KeyCode::KEY_D:
            movingRight = false;
            break;

        case EventKeyboard::KeyCode::KEY_W:
            movingUp = false;
            break;

        case EventKeyboard::KeyCode::KEY_S:
            movingDown = false;
            break;

        case EventKeyboard::KeyCode::KEY_SPACE:
            isFiring = false;
            break;

        default:
            break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->scheduleUpdate();

    return true;
}

void Assignment2::update(float dt)
{
    if (movingLeft)
    {
        sprite1->setPosition(Vec2(sprite1->getPosition().x - (dt * 200), sprite1->getPosition().y));
    }
    if (movingRight)
    {
        sprite1->setPosition(Vec2(sprite1->getPosition().x + (dt * 200), sprite1->getPosition().y));
    }
    if (movingUp)
    {
        sprite1->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y + (dt * 200)));
    }
    if (movingDown)
    {
        sprite1->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y - (dt * 200)));
    }
    if (isFiring)
    {
        
    }

    healthBar->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y - sprite1->getContentSize().height / 2));
}