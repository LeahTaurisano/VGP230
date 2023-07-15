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

    speed1 = (Vec2(RandomHelper::random_real(-1000.f, 1000.f), RandomHelper::random_real(-1000.f, 1000.f)));
    speed2 = (Vec2(RandomHelper::random_real(-1000.f, 1000.f), RandomHelper::random_real(-1000.f, 1000.f)));
    //speed1 = Vec2(-2000, -2000); Uncomment these speed values for a fun laugh.
    //speed2 = Vec2(2000, 2000);
    sprite1 = Sprite::create("bullet2.png");
    sprite2 = Sprite::create("bullet2.png");

    Label* newLabel = Label::createWithSystemFont("Bounce", "arial.ttf", 75.f);

    MenuItemImage* newMenu = MenuItemImage::create("qmark.png", "stone.png");
    Menu* menu = Menu::create(newMenu, NULL);
    menu->setPosition(Vec2::ZERO);

    newMenu->setPosition(Vec2(origin.x + newMenu->getContentSize().width / 2, visibleSize.height - newMenu->getContentSize().height / 2));

    sprite1->setPosition(Vec2(RandomHelper::random_real(origin.x + sprite1->getContentSize().width / 2, visibleSize.width - sprite1->getContentSize().width / 2),
                              RandomHelper::random_real(origin.y + sprite1->getContentSize().height / 2, visibleSize.height - sprite1->getContentSize().height / 2)));
    sprite2->setPosition(Vec2(RandomHelper::random_real(origin.x + sprite2->getContentSize().width / 2, visibleSize.width - sprite2->getContentSize().width / 2),
                              RandomHelper::random_real(origin.y + sprite2->getContentSize().height / 2, visibleSize.height - sprite2->getContentSize().height / 2)));
    newLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(sprite1, 0);
    this->addChild(sprite2, 0);
    this->addChild(newLabel, -1);
    this->addChild(menu, 1);

    this->scheduleUpdate();

    return true;
}

Vec2 Assignment1::nextPos(Sprite* sprite, Vec2 speed, float dt)
{
    return Vec2(sprite->getPosition().x + speed.x * dt, sprite->getPosition().y + speed.y * dt);
}

void Assignment1::move(Sprite* sprite, Vec2& speed, float dt)
{
    if (nextPos(sprite, speed, dt).x < Director::getInstance()->getVisibleOrigin().x + sprite->getContentSize().width / 2)
    {
        speed = Vec2(-speed.x, speed.y);
    }
    if (nextPos(sprite, speed, dt).y < Director::getInstance()->getVisibleOrigin().y + sprite->getContentSize().height / 2)
    {
        speed = Vec2(speed.x, -speed.y);
    }
    if (nextPos(sprite, speed, dt).y > Director::getInstance()->getVisibleSize().height - sprite->getContentSize().height / 2)
    {
        speed = Vec2(speed.x, -speed.y);
    }
    if (nextPos(sprite, speed, dt).x > Director::getInstance()->getVisibleSize().width - sprite->getContentSize().width / 2)
    {
        speed = Vec2(-speed.x, speed.y);
    }
    sprite->setPosition(Vec2(sprite->getPosition().x + speed.x * dt, sprite->getPosition().y + speed.y * dt));
}

void Assignment1::update(float dt)
{
    move(sprite1, speed1, dt);
    move(sprite2, speed2, dt);
}