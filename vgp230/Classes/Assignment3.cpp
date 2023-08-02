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

    background = Sprite::create("space.jpg");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setRotation(270);
    background->setScale(2);
    this->addChild(background, -2);

    bombEffect = LayerColor::create(Color4B::GRAY);
    this->addChild(bombEffect, -3);
    bombEffect->setVisible(false);

    //Sprite* test1 = Sprite::create("carriergun1_01.png");
    //test1->setScale(3);
    //test1->setPosition(Vec2(visibleSize.width - test1->getContentSize().width * test1->getScale(), visibleSize.height - test1->getContentSize().height * test1->getScale()));
    //this->addChild(test1, 1);

    //Sprite* test2 = Sprite::create("carriergun2_01.png");
    //test2->setScale(3);
    //test2->setPosition(Vec2(origin.x + test2->getContentSize().width * test2->getScale(), visibleSize.height - test2->getContentSize().height * test2->getScale()));
    //this->addChild(test2, 1);

    startOption = Label::createWithSystemFont("Play", "arial.ttf", 20.f);
    startOption->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.5));
    startOption->setColor(Color3B::WHITE);
    this->addChild(startOption, -1);

    controlsOption = Label::createWithSystemFont("Controls", "arial.ttf", 20.f);
    controlsOption->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
    controlsOption->setColor(Color3B::GRAY);
    this->addChild(controlsOption, -1);

    victoryText = Label::createWithSystemFont("Congratulations!", "arial.ttf", 40.f);
    victoryText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
    this->addChild(victoryText, -1);
    victoryText->setVisible(false);

    victoryText2 = Label::createWithSystemFont("Press Enter to return to the main menu\nPress ESC to close the game!", "arial.ttf", 20.f);
    victoryText2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.5));
    this->addChild(victoryText2, -1);
    victoryText2->setVisible(false);

    Label* controls = Label::createWithSystemFont("\nDefeat the Boss while not letting bullets touch your core!\nW: Move Up\nS: Move Down\nA: Move Left\nD: Move Right\nSpacebar: Fire\n\nPickups\nShield: Blocks the next player hit\nBomb: Hit B to clear all bullets on screen\nDamage: Increases damage by 50% for a short time\n\nEnter: Return to Menu", "arial.ttf", 20.f);
    controls->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(controls, -1);
    controls->setVisible(false);

    player.ship = Sprite::create("fightershadowless.png"); //Create player
    player.ship->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                  origin.y + player.ship->getContentSize().height / 2));
    player.speed = 200;
    player.ship->addComponent(CollisionComponent::createDot());
    this->addChild(player.ship, 0);
    player.ship->setVisible(false);

    enemyP1 = Sprite::create("carrierFirstForm.png"); //Enemy Phase 1 Sprite
    enemyP1->setScale(3);
    enemyP1->setPosition(Vec2(origin.x + visibleSize.width / 2,
        visibleSize.height - ((enemyP1->getContentSize().height / 2) * enemyP1->getScale()) + 500));
    enemyP1->addComponent(CollisionComponent::createCircle(enemyP1->getContentSize().width));
    this->addChild(enemyP1, 1);
    enemyP1->setVisible(false);

    enemyP2 = Sprite::create("carrier_01.png"); //Enemy Phase 2 Sprite
    enemyP2->setScale(3);
    enemyP2->setPosition(Vec2(origin.x + visibleSize.width / 2,
        visibleSize.height - (enemyP2->getContentSize().height / 2) * enemyP2->getScale()));
    enemyP2->addComponent(CollisionComponent::createCircle(enemyP2->getContentSize().width));
    this->addChild(enemyP2, 1);
    enemyP2->setVisible(false);

    enemyA1 = Sprite::create("carrierphase3_flap1.2.png"); //Enemy P3 Animation Sprite
    enemyA1->setScale(3);
    enemyA1->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 visibleSize.height - (enemyA1->getContentSize().height / 2) * enemyA1->getScale()));
    enemyA1->addComponent(CollisionComponent::createCircle(enemyA1->getContentSize().width));
    this->addChild(enemyA1, 1);
    enemyA1->setVisible(false);

    enemyA2 = Sprite::create("carrierphase3_flap2.png"); //Enemy P3 Animation Sprite
    enemyA2->setScale(3);
    enemyA2->setPosition(Vec2(origin.x + visibleSize.width / 2,
                              visibleSize.height - (enemyA2->getContentSize().height / 2) * enemyA2->getScale()));
    enemyA2->addComponent(CollisionComponent::createCircle(enemyA2->getContentSize().width));
    this->addChild(enemyA2, 1);
    enemyA2->setVisible(false);

    enemy.ship = enemyP1; //Create Enemy
    enemy.speed = 100;
    enemy.maxHealth = enemy.bossP1Health;
    enemy.health = enemy.maxHealth;
    enemy.movingLeft = true;
    enemy.firingRadius = enemy.ship->getContentSize().width;
    enemyFireDelay = enemy.GetFireDelay();

    enemyP2Glow = Sprite::create("carrierP2Glow2.png"); //Create player shield
    enemyP2Glow->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height - (enemyP1->getContentSize().height / 2) * enemyP1->getScale()));
    enemyP2Glow->setScale(3);
    this->addChild(enemyP2Glow, 2);
    enemyP2Glow->setVisible(false);

    enemyP3Glow = Sprite::create("carrierP3Glow.png"); //Create player shield
    enemyP3Glow->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height - (enemyP1->getContentSize().height / 2) * enemyP1->getScale()));
    enemyP3Glow->setScale(3);
    this->addChild(enemyP3Glow, 2);
    enemyP3Glow->setVisible(false);

    healthBar = Sprite::create("bar_red.png"); //Create healthbars
    healthBar->setScale(healthScale, 1);
    healthBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - healthBar->getContentSize().height / 2));
    this->addChild(healthBar, 6);
    healthBar->setVisible(false);
    healthBarE = Sprite::create("bar_empty.png");
    healthBarE->setScale(baseHealthScale, 1);
    healthBarE->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - healthBarE->getContentSize().height / 2));
    this->addChild(healthBarE, 5);
    healthBarE->setVisible(false);

    shieldUp = Sprite::create("Cheese.png"); //Create shield
    shieldUp->addComponent(CollisionComponent::createCircle(shieldUp->getContentSize().width));
    this->addChild(shieldUp, 0);
    shieldUp->setVisible(false);

    playerShield = Sprite::create("shield.png"); //Create player shield
    playerShield->setPosition(Vec2(player.ship->getContentSize().width / 2, player.ship->getContentSize().height / 2));
    player.ship->addChild(playerShield, 0);
    playerShield->setVisible(false);

    damageUp = Sprite::create("Carrot.png"); //Create damage upgrade
    damageUp->addComponent(CollisionComponent::createCircle(damageUp->getContentSize().width));
    this->addChild(damageUp, 0);
    damageUp->setVisible(false);

    bombUp = Sprite::create("mushroom.png"); //Create bomb
    bombUp->addComponent(CollisionComponent::createCircle(bombUp->getContentSize().width));
    this->addChild(bombUp, 0);
    bombUp->setVisible(false);

    powerupPool.push_back(SHIELD); //Fill powerup pool
    powerupPool.push_back(BOMB);
    powerupPool.push_back(DAMAGE);

    for (Bullets& it : bullets) //Load player bullet pool
    {
        it.bulletBase = Sprite::create("bullet_player.png");
        it.bulletBase->addComponent(CollisionComponent::createCircle(it.bulletBase->getContentSize().width / 2));
        this->addChild(it.bulletBase, 1);
        it.bulletBase->setVisible(false);
        it.bulletUpgrade = Sprite::create("bullet1.png");
        it.bulletUpgrade->addComponent(CollisionComponent::createCircle(it.bulletBase->getContentSize().width / 2));
        this->addChild(it.bulletUpgrade, 1);
        it.bulletUpgrade->setVisible(false);
        it.bullet = it.bulletBase;
    }

    for (Bullets& it : enemyBullets) //Load enemy bullet pool
    {
        it.bullet = Sprite::create("bullet_enemy.png");
        it.bullet->setScale(3);
        it.bullet->addComponent(CollisionComponent::createCircle(it.bullet->getContentSize().width / 2.5 * (it.bullet->getScale() - 1)));
        this->addChild(it.bullet, 4);
        it.bullet->setVisible(false);
    }

    debug = DrawNode::create(5); //Draw debug nodes
    this->addChild(debug, 1);

    auto keyboardListener = EventListenerKeyboard::create(); 
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) //Player controls input
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
            if (gameState == RUNNING || gameState == CONTROLS)
            {
                player.isFiring = true;
                PlayerFire();
                player.autoFire = true;
            }
            break;

        case EventKeyboard::KeyCode::KEY_0:
            debugDrawOn = !debugDrawOn;
            break;

        case EventKeyboard::KeyCode::KEY_GRAVE:
            player.godMode = !player.godMode;
            break;

        case EventKeyboard::KeyCode::KEY_B:
            if (player.hasBomb)
            {
                player.hasBomb = false;
                bombEffect->setVisible(true);
                powerupPool.push_back(BOMB);
                for (Bullets& it : enemyBullets)
                {
                    if (it.bullet->isVisible()) ResetBullet(it);
                }
            }
            break;

        case EventKeyboard::KeyCode::KEY_ESCAPE:
            if (gameState == MENU || gameState == END_SCREEN) Director::getInstance()->end();
                break;

        default:
            break;
        }

        if (gameState == MENU)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
            {
                ++selectedOption;
                if (selectedOption > numMenuOptions) selectedOption = 1;
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
            {
                --selectedOption;
                if (selectedOption < 1) selectedOption = numMenuOptions;
            }
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
            {
                if (selectedOption == 1)
                {
                    background->setVisible(false);
                    startOption->setVisible(false);
                    controlsOption->setVisible(false);
                    enemy.ship->setVisible(true);
                    player.ship->setVisible(true);
                    gameState = BOSS_INTRO;
                }
                else if (selectedOption == 2)
                {
                    background->setVisible(false);
                    controls->setVisible(true);
                    startOption->setVisible(false);
                    controlsOption->setVisible(false);
                    player.ship->setVisible(true);
                    gameState = CONTROLS;
                }
            }
        }
        else if (gameState == CONTROLS)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
            {
                background->setVisible(true);
                controls->setVisible(false);
                startOption->setVisible(true);
                controlsOption->setVisible(true);
                player.ship->setVisible(false);
                for (Bullets& it : bullets)
                {
                    ResetBullet(it);
                }
                gameState = MENU;
            }
        }
        else if (gameState == END_SCREEN)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) resetGame = true;
        }
    };

    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) //Player controls release
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
            player.autoFire = false;
            player.autoFireTimer = 0;
            break;

        default:
            break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    gameState = MENU;
    this->scheduleUpdate();

    return true;
}

void Assignment3::Move(Ship toMove, float dt) //Movement for both ships
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (toMove.movingLeft && toMove.ship->getPosition().x - (dt * toMove.speed) > origin.x + toMove.ship->getContentSize().width / 3) 
        toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x - (dt * toMove.speed), toMove.ship->getPosition().y));

    if (toMove.movingRight && toMove.ship->getPosition().x + (dt * toMove.speed) < visibleSize.width - toMove.ship->getContentSize().width / 3)
        toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x + (dt * toMove.speed), toMove.ship->getPosition().y));

    if (toMove.movingUp && toMove.ship->getPosition().y + (dt * toMove.speed) < visibleSize.height - toMove.ship->getContentSize().height / 3)
        toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x, toMove.ship->getPosition().y + (dt * toMove.speed)));

    if (toMove.movingDown && toMove.ship->getPosition().y - (dt * toMove.speed) > origin.y + toMove.ship->getContentSize().height / 3)
        toMove.ship->setPosition(Vec2(toMove.ship->getPosition().x, toMove.ship->getPosition().y - (dt * toMove.speed)));
}

void Assignment3::EnemyMove(Ship &toMove, float dt) //Enemy specific movement
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
    if (enemy.BossNumber == enemy.THIRD)
    {
        if (toMove.animation > 0.1)
        {
            toMove.animation = 0;
            toMove.ship->setVisible(false);
            if (toMove.ship == enemyA1)
            {
                enemyA2->setPosition(toMove.ship->getPosition());
                toMove.ship = enemyA2;
            }
            else if (toMove.ship == enemyA2)
            {
                enemyA1->setPosition(toMove.ship->getPosition());
                toMove.ship = enemyA1;
            }
            toMove.ship->setVisible(true);
        }
        toMove.animation += 1 * dt;
    }
    Move(enemy, dt);
}

void Assignment3::PlayerFire()
{
    if (player.isFiring) //Player Firing
    {
        if (iter >= 50) iter = 0;
        bullets[iter].fired = true;
        bullets[iter].bulletDamage = player.damage;
        if (player.hasDamage) bullets[iter].bullet = bullets[iter].bulletUpgrade;
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
}

void Assignment3::PlayerAutoCheck(float dt)
{
    if (player.autoFire)
    {
        if (player.autoFireTimer >= 0.2)
        {
            player.autoFireTimer = 0;
            player.isFiring = true;
            PlayerFire();
        }
        else player.autoFireTimer += dt;
    }
}

void Assignment3::ResetBullet(Bullets &bullet) //Reset a bullet
{
    if (bullet.bullet == bullet.bulletUpgrade)
    {
        bullet.bullet->setVisible(false);
        bullet.bullet->setPosition(0, 0);
        bullet.bullet = bullet.bulletBase;
    }
    bullet.fired = false;
    bullet.firedLeft = false;
    bullet.firedRight = false;
    bullet.bullet->setVisible(false);
    bullet.bullet->setPosition(0, 0);
    bullet.timeActive = 0;
}

bool Assignment3::Collided(Sprite* first, Sprite* second) //Checks if any two objects collided
{
    auto firstCollision = dynamic_cast<CollisionComponent*>((first)->getComponent("CollisionComponent"));
    auto secondCollision = dynamic_cast<CollisionComponent*>((second)->getComponent("CollisionComponent"));
    if (firstCollision->IsColliding(secondCollision)) return true;
    return false;
}

void Assignment3::MoveUpgrades(float dt)
{
    if (shieldUp->isVisible()) //Checks for player collision to powerup for collection, then add functionality
    {
        shieldUp->setPosition(shieldUp->getPosition().x, shieldUp->getPosition().y - (player.speed * dt));
        if (shieldUp->getPosition().y <= 0)
        {
            shieldUp->setVisible(false);
            powerupPool.push_back(SHIELD);
            chosenPowerup = READY;
        }
        if (Collided(shieldUp, player.ship))
        {
            shieldUp->setVisible(false);
            playerShield->setVisible(true);
            chosenPowerup = READY;
            player.hasShield = true;
        }
    }
    if (bombUp->isVisible())
    {
        bombUp->setPosition(bombUp->getPosition().x, bombUp->getPosition().y - (player.speed * dt));
        if (bombUp->getPosition().y <= 0)
        {
            bombUp->setVisible(false);
            powerupPool.push_back(BOMB);
            chosenPowerup = READY;
        }
        if (Collided(bombUp, player.ship))
        {
            bombUp->setVisible(false);
            chosenPowerup = READY;
            player.hasBomb = true;
        }
    }
    if (damageUp->isVisible())
    {
        damageUp->setPosition(damageUp->getPosition().x, damageUp->getPosition().y - (player.speed * dt));
        if (damageUp->getPosition().y <= 0)
        {
            damageUp->setVisible(false);
            powerupPool.push_back(DAMAGE);
            chosenPowerup = READY;
        }
        if (Collided(damageUp, player.ship))
        {
            damageUp->setVisible(false);
            chosenPowerup = READY;
            player.hasDamage = true;
            player.damage = 1.5;
        }
    }
}

void Assignment3::ResetToMenu() //Reset and return to menu
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    debug->clear();
    enemy.ship->setVisible(false);
    player.ship->setVisible(false);
    healthBar->setVisible(false);
    healthBarE->setVisible(false);
    background->setVisible(true);
    startOption->setVisible(true);
    controlsOption->setVisible(true);
    shieldUp->setVisible(false);
    bombUp->setVisible(false);
    damageUp->setVisible(false);
    victoryText->setVisible(false);
    victoryText2->setVisible(false);
    playerShield->setVisible(false);
    enemy.maxHealth = enemy.bossP1Health;
    enemy.health = enemy.maxHealth;
    enemy.ship = enemyP1;
    enemy.BossNumber = enemy.FIRST;
    enemy.BossAttacks = enemy.WAVE;
    healthScale = 0;
    healthBar->setScale(healthScale, 1);
    damageDuration = 10;
    player.hasShield = false;
    player.hasBomb = false;
    player.hasDamage = false;
    player.godMode = false;
    player.movingDown = false;
    player.movingUp = false;
    player.movingLeft = false;
    player.movingRight = false;
    resetGame = false;
    player.ship->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + player.ship->getContentSize().height / 2));
    enemyP1->setPosition(Vec2(origin.x + visibleSize.width / 2,
        visibleSize.height - ((enemyP1->getContentSize().height / 2) * enemyP1->getScale()) + 500));
    powerupPool.clear();
    powerupPool.push_back(SHIELD);
    powerupPool.push_back(BOMB);
    powerupPool.push_back(DAMAGE);
    chosenPowerup = READY;
    gameState = MENU;
}

void Assignment3::update(float dt) //Game loop
{
    if (gameState == MENU)
    {
        debug->clear();
        if (selectedOption == 1)
        {
            startOption->setColor(Color3B::WHITE);
            controlsOption->setColor(Color3B::GRAY);
        }
        else if (selectedOption == 2)
        {
            startOption->setColor(Color3B::GRAY);
            controlsOption->setColor(Color3B::WHITE);
        }
    }
    if (gameState == CONTROLS)
    {
        Move(player, dt);
        PlayerAutoCheck(dt);
        debug->clear();
        debug->drawDot(player.ship->getPosition(), 4, Color4F::RED);

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
            }
        }
    }
    if (gameState == BOSS_INTRO)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        Move(player, dt);
        debug->clear();
        debug->drawDot(player.ship->getPosition(), 4, Color4F::RED);
        enemy.ship->setPosition(Vec2(enemy.ship->getPosition().x, enemy.ship->getPosition().y - (enemy.speed * dt)));
        if (enemy.ship->getPosition().y <= visibleSize.height - (enemyP1->getContentSize().height / 2) * enemyP1->getScale())
        {
            healthBarE->setVisible(true);
            healthBar->setVisible(true);
            enemy.ship->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height - (enemyP1->getContentSize().height / 2) * enemyP1->getScale()));
            healthBarE->setScale(baseHealthScale, 1);
            healthBar->setScale(healthBar->getScaleX() + dt, 1);
            if (healthBar->getScaleX() >= baseHealthScale)
            {
                healthScale = baseHealthScale;
                healthBar->setScale(healthScale, 1);
                gameState = RUNNING;
            }
        }
    }
    if (gameState == RUNNING)
    {
        if (bombEffect->isVisible())
        {
            bombAnimationTimer -= 1 * dt;
            if (bombAnimationTimer <= 0)
            {
                bombAnimationTimer = 0.05;
                bombEffect->setVisible(false);
            }
        }
        Move(player, dt); //Player Movement
        EnemyMove(enemy, dt); //Enemy Movement

        if (enemy.firingAngle > 360) enemy.firingAngle = 0; //Enemy rotating firing point
        enemy.firingPoint = Vec2(enemy.ship->getPosition().x + cos(enemy.firingAngle) * enemy.firingRadius, enemy.ship->getPosition().y + sin(enemy.firingAngle) * enemy.firingRadius);
        enemy.firingAngle += 1 * dt;

        PlayerAutoCheck(dt);

        if (bossAttackTimer >= enemy.GetAttackSwapDelay()) //Boss Attack Chooser
        {
            int rand = (RandomHelper::random_int(0, 3));
            if (rand == 0) enemy.BossAttacks = enemy.SPIRAL;
            if (rand == 1) enemy.BossAttacks = enemy.SINE;
            if (rand == 2) enemy.BossAttacks = enemy.WAVE;
            if (rand == 3) enemy.BossAttacks = enemy.CIRCLE;
            bossAttackTimer = 0;
            enemyFireDelay = enemy.GetFireDelay();
            enemyCanFire = true;
        }
        bossAttackTimer += dt;

        if (enemyCanFire) //Enemy Firing
        {
            if (enemy.BossAttacks == enemy.SPIRAL) enemy.SpiralAttack(enemyIter, enemyBullets);
            if (enemy.BossAttacks == enemy.SINE) enemy.SineAttack(enemyIter, enemyBullets, enemy);
            if (enemy.BossAttacks == enemy.WAVE) enemy.WaveAttack(enemyIter, enemyBullets);
            if (enemy.BossAttacks == enemy.CIRCLE) enemy.CircleAttack(enemyIter, enemyBullets);
            enemyCanFire = false;
            enemyFireDelay -= (1 * dt);
        }

        if (enemyFireDelay < enemy.GetFireDelay())
        {
            if (enemyFireDelay >= 0) enemyFireDelay -= (1 * dt);
            else
            {
                enemyFireDelay = enemy.GetFireDelay();
                enemyCanFire = true;
            }
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

                if (Collided(it.bullet, enemy.ship))
                {
                    ResetBullet(it);
                    enemy.health -= it.bulletDamage;
                    healthScale -= ((baseHealthScale * it.bulletDamage) / enemy.maxHealth);
                    healthBar->setScale(healthScale, 1);
                    if (enemy.health <= 0)
                    {
                        healthBar->setVisible(false);
                    }

                    if (RandomHelper::random_int(0, 9) == 0 && chosenPowerup == READY && !(player.hasShield && player.hasBomb && player.hasDamage))
                    {
                        random = RandomHelper::random_int(0, (int)powerupPool.size() - 1);
                        chosenPowerup = powerupPool[random];
                        powerupPool.erase(powerupPool.begin() + random);
                    }

                }
            } 
        }

        if (chosenPowerup != READY) //Spawns and moves Powerups
        {
            if (chosenPowerup == SHIELD && !shieldUp->isVisible())
            {
                shieldUp->setPosition(enemy.firingPoint);
                shieldUp->setVisible(true);
            }
            else if (chosenPowerup == BOMB && !bombUp->isVisible())
            {
                bombUp->setPosition(enemy.firingPoint);
                bombUp->setVisible(true);
            }
            else if (chosenPowerup == DAMAGE && !damageUp->isVisible())
            {
                damageUp->setPosition(enemy.firingPoint);
                damageUp->setVisible(true);
            }

            MoveUpgrades(dt);
        }

        if (player.hasDamage) //Damage powerup timer
        {
            damageDuration -= 1 * dt;
            if (damageDuration <= 0)
            {
                damageDuration = 10;
                player.hasDamage = false;
                powerupPool.push_back(DAMAGE);
                player.damage = 1;
            }
        }

        for (Bullets& it : enemyBullets) //Enemy Bullet Movement
        {
            if (it.fired)
            {
                if (it.firedWith == it.SPIRAL) enemy.BulletSpiralMovement(it, dt);
                else if (it.firedWith == it.SINE) enemy.BulletSineMovement(it, dt);
                else if (it.firedWith == it.WAVE) enemy.BulletWaveMovement(it, dt);
                else if (it.firedWith == it.CIRCLE) enemy.BulletCircleMovement(it, dt);
                if (/*it.bullet->getPosition().y >= Director::getInstance()->getVisibleSize().height ||*/
                    it.bullet->getPosition().y <= 0/* ||
                    it.bullet->getPosition().x >= Director::getInstance()->getVisibleSize().width ||
                    it.bullet->getPosition().x <= 0*/
                    || it.timeActive > 17)
                {
                    ResetBullet(it);
                }
                it.timeActive += dt;

                if (Collided(it.bullet, player.ship))
                {
                    ResetBullet(it);
                    if (player.hasShield)
                    {
                        player.hasShield = false;
                        powerupPool.push_back(SHIELD);
                        playerShield->setVisible(false);
                    }
                    else
                    {
                        if (!player.godMode)
                        {
                            ResetBullet(it);
                            player.ship->setVisible(false);
                            gameState = GAME_OVER;
                        }
                    }
                }
            }
        }

        debug->clear();
        debug->setLineWidth(5);
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

                        auto color = Color4F::RED;

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
        debug->drawDot(player.ship->getPosition(), 4, Color4F::RED);

        if (enemy.health <= 0 || gameState == GAME_OVER)
        {
            for (Bullets& it : bullets)
            {
                ResetBullet(it);
            }
            for (Bullets& it : enemyBullets)
            {
                ResetBullet(it);
            }
            if (enemy.health <= 0)
            {
                if (enemy.BossNumber == enemy.FIRST)
                {
                    enemy.BossNumber = enemy.SECOND;
                    enemy.maxHealth = enemy.bossP2Health;
                    enemy.health = enemy.maxHealth;
                    bossAttackTimer = 8;
                    gameState = BOSS_PHASE;
                }
                else if (enemy.BossNumber == enemy.SECOND)
                {
                    enemy.BossNumber = enemy.THIRD;
                    enemy.maxHealth = enemy.bossP3Health;
                    enemy.health = enemy.maxHealth;
                    bossAttackTimer = 8;
                    gameState = BOSS_PHASE;
                }
                else
                {
                    healthBarE->setVisible(false);
                    shieldUp->setVisible(false);
                    damageUp->setVisible(false);
                    bombUp->setVisible(false);
                    gameState = BOSS_DEATH;
                }
            }
        }
    }
    if (gameState == BOSS_PHASE)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        float middle = visibleSize.width / 2;
        float currentX = enemy.ship->getPosition().x;
        float delta = middle - currentX;

        Move(player, dt);
        MoveUpgrades(dt);
        debug->clear();
        debug->drawDot(player.ship->getPosition(), 4, Color4F::RED);
        enemy.ship->setPosition(currentX + (enemy.speed * dt) * (delta / abs(delta)), enemy.ship->getPosition().y);
        if (delta <= enemy.speed * dt && currentX <= middle || delta >= enemy.speed * dt && currentX >= middle)
        {
            enemy.ship->setPosition(middle, enemy.ship->getPosition().y);
            if (enemy.BossNumber == enemy.SECOND)
            {
                enemyP2Glow->setVisible(true);
                enemyP2Glow->setOpacity(1);
            }
            else if (enemy.BossNumber == enemy.THIRD)
            {
                enemyP3Glow->setVisible(true);
                enemyP3Glow->setOpacity(1);
            }
            healthBar->setVisible(true);
            gameState = PHASE_ANIMATION;
        }
    }
    if (gameState == PHASE_ANIMATION)
    {
        Move(player, dt);
        MoveUpgrades(dt);
        debug->clear();
        debug->drawDot(player.ship->getPosition(), 4, Color4F::RED);
        healthBar->setScale(healthBar->getScaleX() + dt, 1);

        if (enemy.BossNumber == enemy.SECOND)
        {
            if (healthBar->getScaleX() <= baseHealthScale / 2) enemyP2Glow->setOpacity(enemyP2Glow->getOpacity() + 1);
            else
            {
                auto tempPos = enemy.ship->getPosition();
                enemy.ship->setVisible(false);
                enemy.ship = enemyP2;
                enemy.ship->setPosition(tempPos);
                enemy.ship->setVisible(true);
                enemyP2Glow->setOpacity(enemyP2Glow->getOpacity() - 1);
            }
        }

        if (enemy.BossNumber == enemy.THIRD)
        {
            if (healthBar->getScaleX() <= baseHealthScale / 2) enemyP3Glow->setOpacity(enemyP3Glow->getOpacity() + 1);
            else
            {
                auto tempPos = enemy.ship->getPosition();
                enemy.ship->setVisible(false);
                enemy.ship = enemyA1;
                enemy.ship->setPosition(tempPos);
                enemy.ship->setVisible(true);
                enemyP3Glow->setOpacity(enemyP3Glow->getOpacity() - 1);
            }
        }

        if (healthBar->getScaleX() >= baseHealthScale)
        {
            healthScale = baseHealthScale;
            healthBar->setScale(healthScale, 1);
            enemyP2Glow->setVisible(false);
            enemyP3Glow->setVisible(false);
            enemyCanFire = true;
            enemyFireDelay = enemy.GetFireDelay();
            gameState = RUNNING;
        }
    }
    if (gameState == BOSS_DEATH)
    {
        if ((int)animationTime % 2 >= 1) enemy.ship->setPosition(enemy.ship->getPosition().x - (enemy.speed * dt) * 2, enemy.ship->getPosition().y + (enemy.speed * dt) / 3);
        else enemy.ship->setPosition(enemy.ship->getPosition().x + (enemy.speed * dt) * 2, enemy.ship->getPosition().y + (enemy.speed * dt) / 3);
        animationTime += (1 * dt);
        if (animationTime >= 7)
        {
            animationTime = 0;
            gameState = VICTORY;
        }
    }
    if (gameState == VICTORY)
    {
        debug->clear();
        player.ship->setPosition(player.ship->getPosition().x, player.ship->getPositionY() + (player.speed * 2 * dt));
        if (player.ship->getPosition().y > Director::getInstance()->getVisibleSize().height + player.ship->getContentSize().height)
        {
            victoryText->setVisible(true);
            victoryText2->setVisible(true);
            gameState = END_SCREEN;
        }
    }
    if (gameState == END_SCREEN)
    {
        if (resetGame) ResetToMenu();
    }
    if (gameState == GAME_OVER)
    {
        ResetToMenu();
    }
}