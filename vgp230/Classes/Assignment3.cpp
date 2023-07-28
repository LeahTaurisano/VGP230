#include "Assignment3.h"
#include "CollisionComponent.h"

Scene* Assignment3::createScene()
{
    return Assignment3::create();
}

bool Assignment3::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player.ship = Sprite::create("fighter.png");
    player.ship->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                  origin.y + player.ship->getContentSize().height / 2));
    player.speed = 200;
    player.ship->addComponent(CollisionComponent::createDot());
    this->addChild(player.ship, 0);

    enemy.ship = Sprite::create("carrier_01.png");
    enemy.ship->setScale(3);
    enemy.ship->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 visibleSize.height - (enemy.ship->getContentSize().height / 2) * enemy.ship->getScale()));
    enemy.speed = 100;
    enemy.maxHealth = 200;
    enemy.health = 200;
    enemy.movingLeft = true;
    enemy.ship->addComponent(CollisionComponent::createCircle(enemy.ship->getContentSize().width));
    this->addChild(enemy.ship, 0);

    healthBar = Sprite::create("bar_red.png");
    healthBar->setScale(healthScale, 1);
    healthBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - healthBar->getContentSize().height / 2));
    this->addChild(healthBar, 1);
    healthBarE = Sprite::create("bar_empty.png");
    healthBarE->setScale(healthScale, 1);
    healthBarE->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - healthBarE->getContentSize().height / 2));
    this->addChild(healthBarE, 0);

    for (Bullets& it : bullets)
    {
        it.bullet = Sprite::create("bullet2.png");
        it.bullet->addComponent(CollisionComponent::createCircle(it.bullet->getContentSize().width / 2));
        this->addChild(it.bullet, 0);
        it.bullet->setVisible(false);
    }

    debug = DrawNode::create(5);
    this->addChild(debug, 1);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_A:
            player.movingLeft = true;
            break;

        case EventKeyboard::KeyCode::KEY_D:
            player.movingRight = true;
            break;

        case EventKeyboard::KeyCode::KEY_W:
            player.movingUp = true;
            break;

        case EventKeyboard::KeyCode::KEY_S:
            player.movingDown = true;
            break;

        case EventKeyboard::KeyCode::KEY_SPACE:
            player.isFiring = true;
            break;
        case EventKeyboard::KeyCode::KEY_0:
            debugDrawOn = !debugDrawOn;
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
            player.movingLeft = false;
            break;

        case EventKeyboard::KeyCode::KEY_D:
            player.movingRight = false;
            break;

        case EventKeyboard::KeyCode::KEY_W:
            player.movingUp = false;
            break;

        case EventKeyboard::KeyCode::KEY_S:
            player.movingDown = false;
            break;

        case EventKeyboard::KeyCode::KEY_SPACE:
            player.isFiring = false;
            break;

        default:
            break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->scheduleUpdate();

    return true;
}

void Assignment3::Move(Ship toMove, float dt)
{
    if (toMove.movingLeft) toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x - (dt * toMove.speed), toMove.ship->getPosition().y));
    if (toMove.movingRight) toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x + (dt * toMove.speed), toMove.ship->getPosition().y));
    if (toMove.movingUp) toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x, toMove.ship->getPosition().y + (dt * toMove.speed)));
    if (toMove.movingDown) toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x, toMove.ship->getPosition().y - (dt * toMove.speed)));
}

void Assignment3::EnemyMove(Ship &toMove, float dt)
{
    if (toMove.movingLeft && toMove.ship->getPosition().x < Director::getInstance()->getVisibleOrigin().x + (toMove.ship->getContentSize().width / 2) * toMove.ship->getScale())
    {
        toMove.movingLeft = false;
        toMove.movingRight = true;
    }
    else if (toMove.movingRight && toMove.ship->getPosition().x > Director::getInstance()->getVisibleSize().width - (toMove.ship->getContentSize().width / 2) * toMove.ship->getScale())
    {
        toMove.movingRight = false;
        toMove.movingLeft = true;
    }
    Move(enemy, dt);
}

void Assignment3::ResetBullet(Bullets &bullet)
{
    bullet.fired = false;
    bullet.firedLeft = false;
    bullet.firedRight = false;
    bullet.bullet->setVisible(false);
    bullet.bullet->setPosition(0, 0);
}

void Assignment3::update(float dt)
{
    Move(player, dt); //Player Movement
    EnemyMove(enemy, dt); //Enemy Movement

    if (player.isFiring) //Player Firing
    {
        if (iter == 100) iter = 0;
        bullets[iter].fired = true;
        bullets[iter].bullet->setVisible(true);
        bullets[iter].bullet->setPosition(Vec2(player.ship->getPosition().x, player.ship->getPosition().y + player.ship->getContentSize().height / 2));

        if (player.movingLeft && player.movingRight)
        {
            bullets[iter].firedLeft = false;
            bullets[iter].firedRight = false;
        }
        else if (player.movingLeft) bullets[iter].firedLeft = true;
        else if (player.movingRight) bullets[iter].firedRight = true;
        player.isFiring = false;
        ++iter;
    }

    for (Bullets& it : bullets) //Bullet Movement
    {
        if (it.fired)
        {
            if (it.firedRight) it.bullet->setPosition(Vec2(it.bullet->getPosition().x + (dt * it.speed), it.bullet->getPosition().y + it.speed * 3 * dt));
            else if (it.firedLeft) it.bullet->setPosition(Vec2(it.bullet->getPosition().x - (dt * it.speed), it.bullet->getPosition().y + it.speed * 3 * dt));
            else it.bullet->setPosition(Vec2(it.bullet->getPosition().x, it.bullet->getPosition().y + (it.speed * 3 * dt)));

            if (it.bullet->getPosition().y >= Director::getInstance()->getVisibleSize().height)
            {
                ResetBullet(it);
            }
            auto bulletCollision = dynamic_cast<CollisionComponent*>((it.bullet)->getComponent("CollisionComponent"));
            auto shipCollision = dynamic_cast<CollisionComponent*>((enemy.ship)->getComponent("CollisionComponent"));

            if (bulletCollision->IsColliding(shipCollision))
            {
                ResetBullet(it);
                enemy.health -= it.damage;
                healthScale -= (4.0 / enemy.maxHealth);
                healthBar->setScale(healthScale, 1);
            }
        }
    }

    debug->clear();
    debug->setLineWidth(5);

    for (auto it : this->getChildren())
    {
        if (auto collision = dynamic_cast<CollisionComponent*>(it->getComponent("CollisionComponent")))
        {
            collision->SetColliding(false);
        }
    }

    auto& children = this->getChildren();

    /// Determine all colliding objects
    /// TODO: ADD CODE Here
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        for (auto it2 = it + 1; it2 != children.end(); ++it2)
        {
            auto collision = dynamic_cast<CollisionComponent*>((*it)->getComponent("CollisionComponent"));
            auto collision2 = dynamic_cast<CollisionComponent*>((*it2)->getComponent("CollisionComponent"));

            if (collision && collision2 && collision->IsColliding(collision2))
            {
                collision->SetColliding(true);
                collision2->SetColliding(true);
            }
        }
    }
    ///

    if (debugDrawOn)
    {
        for (auto it : this->getChildren())
        {
            if (it->isVisible())
            {
                auto collision = dynamic_cast<CollisionComponent*>(it->getComponent("CollisionComponent"));

                if (collision != NULL)
                {
                    auto position = it->getPosition();

                    auto color = collision->IsColliding() ? Color4F::RED : Color4F::GREEN;

                    switch (collision->GetCollisionType())
                    {
                    case CollisionComponent::Box:
                    {
                        auto dx = collision->GetWidth() / 2.0f;
                        auto dy = collision->GetHeight() / 2.0f;
                        debug->drawRect(Vec2(position.x - dx, position.y + dy), Vec2(position.x + dx, position.y + dy), Vec2(position.x + dx, position.y - dy), Vec2(position.x - dx, position.y - dy), color);
                    }
                    break;
                    case CollisionComponent::Circle:
                    {
                        auto radius = collision->GetRadius();
                        debug->drawCircle(position, radius, 10, 360, false, color);
                    }
                    break;
                    case CollisionComponent::Point:
                        debug->drawDot(position, 3, color);
                        break;
                    }
                }
            }
        }
    }
}
