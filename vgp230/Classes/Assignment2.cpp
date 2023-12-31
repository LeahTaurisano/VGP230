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

    for (Bullets &it : bullets)
    {
        it.bullet = Sprite::create("bullet2.png");
        this->addChild(it.bullet, 0);
        it.bullet->setVisible(false);
    }

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
    if (movingLeft) sprite1->setPosition(Vec2(sprite1->getPosition().x - (dt * 200), sprite1->getPosition().y));
    if (movingRight) sprite1->setPosition(Vec2(sprite1->getPosition().x + (dt * 200), sprite1->getPosition().y));
    if (movingUp) sprite1->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y + (dt * 200)));
    if (movingDown) sprite1->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y - (dt * 200)));

    if (isFiring)
    {
        if (iter == 100) iter = 0;
        bullets[iter].fired = true;
        bullets[iter].bullet->setVisible(true);
        bullets[iter].bullet->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y + sprite1->getContentSize().height / 2));

        if (movingLeft && movingRight)
        {
            bullets[iter].firedLeft = false;
            bullets[iter].firedRight = false;
        }
        else if (movingLeft) bullets[iter].firedLeft = true;
        else if (movingRight) bullets[iter].firedRight = true;
        isFiring = false;
        ++iter;
    }

    for (Bullets &it : bullets)
    {
        if (it.fired)
        {
            if (it.firedRight) it.bullet->setPosition(Vec2(it.bullet->getPosition().x + (dt * 200), it.bullet->getPosition().y + it.speed * dt));
            else if (it.firedLeft) it.bullet->setPosition(Vec2(it.bullet->getPosition().x - (dt * 200), it.bullet->getPosition().y + it.speed * dt));
            else it.bullet->setPosition(Vec2(it.bullet->getPosition().x, it.bullet->getPosition().y + (it.speed * dt)));
            
            if (it.bullet->getPosition().y >= Director::getInstance()->getVisibleSize().height)
            {
                it.fired = false;
                it.firedLeft = false;
                it.firedRight = false;
                it.bullet->setVisible(false);
                it.bullet->setPosition(0, 0);
            }
        }
    }
    healthBar->setPosition(Vec2(sprite1->getPosition().x, sprite1->getPosition().y - sprite1->getContentSize().height / 2));
}