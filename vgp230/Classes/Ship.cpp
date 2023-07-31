#include "Ship.h";
#define degrees * 3.14159 / 180

float Ship::GetFireDelay()
{
    if (BossAttacks == SINE) return 0.6 / ((int)BossNumber + 1);
    if (BossAttacks == SPIRAL) return 0.3 / ((int)BossNumber + 1);
    if (BossAttacks == WAVE) return 0.6 / ((int)BossNumber + 1);
}

void Ship::BulletSpiralMovement(Bullets it, float dt)
{
    auto prevX = it.bullet->getPosition().x;
    auto prevY = it.bullet->getPosition().y;
    if (it.fireDirection == it.POS_POS) it.bullet->setPosition(Vec2(prevX + cos(it.angleFired) * (it.speed * 3 * dt), prevY + abs(sin(it.angleFired)) * (it.speed * 3 * dt)));
    if (it.fireDirection == it.POS_NEG) it.bullet->setPosition(Vec2(prevX + cos(it.angleFired) * (it.speed * 3 * dt), prevY - abs(sin(it.angleFired)) * (it.speed * 3 * dt)));
    if (it.fireDirection == it.NEG_POS) it.bullet->setPosition(Vec2(prevX - cos(it.angleFired) * (it.speed * 3 * dt), prevY + abs(sin(it.angleFired)) * (it.speed * 3 * dt)));
    if (it.fireDirection == it.NEG_NEG) it.bullet->setPosition(Vec2(prevX - cos(it.angleFired) * (it.speed * 3 * dt), prevY - abs(sin(it.angleFired)) * (it.speed * 3 * dt)));
}

void Ship::BulletStraightMovement(Bullets it, float dt)
{
    auto prevX = it.bullet->getPosition().x;
    auto prevY = it.bullet->getPosition().y;
    it.bullet->setPosition(Vec2(prevX, prevY - (it.speed * 3 * dt)));
}

void Ship::BulletSineMovement(Bullets &it, float dt)
{
    auto prevX = it.bullet->getPosition().x;
    auto prevY = it.bullet->getPosition().y;
    if (it.cosCount >= 360) it.cosCount = 0;
    if (it.fireDirection == it.POS_POS) it.bullet->setPosition(Vec2(it.firedX + cos(it.cosCount * 1) * Director::getInstance()->getVisibleSize().width / 2, prevY - (it.speed / 1.7 * dt)));
    if (it.fireDirection == it.NEG_NEG) it.bullet->setPosition(Vec2(it.firedX - cos(it.cosCount * 1) * Director::getInstance()->getVisibleSize().width / 2, prevY - (it.speed / 1.7 * dt)));
    it.cosCount += (dt * 1);
}

void Ship::BulletWaveMovement(Bullets& it, float dt)
{
    auto prevX = it.bullet->getPosition().x;
    auto prevY = it.bullet->getPosition().y;
    it.bullet->setPosition(Vec2(prevX - cos(it.angleFired) * (it.speed * 3 * dt), prevY - sin(it.angleFired) * (it.speed * 3 * dt)));
}

void Ship::SpiralAttack(int &enemyIter, Bullets enemyBullets[])
{
    for (int i = 0; i < 4; ++i)
    {
        if (enemyIter >= 1000) enemyIter = 0;
        enemyBullets[enemyIter].fired = true;
        enemyBullets[enemyIter].firedWith = enemyBullets[enemyIter].SPIRAL;
        if (i == 0)
        {
            enemyBullets[enemyIter].fireDirection = enemyBullets[enemyIter].POS_NEG;
            enemyBullets[enemyIter].angleFired = firingAngle;
        }
        if (i == 1)
        {
            enemyBullets[enemyIter].fireDirection = enemyBullets[enemyIter].POS_NEG;
            enemyBullets[enemyIter].angleFired = firingAngle + 90;
        }
        if (i == 2)
        {
            enemyBullets[enemyIter].fireDirection = enemyBullets[enemyIter].NEG_NEG;
            enemyBullets[enemyIter].angleFired = firingAngle;
        }
        if (i == 3)
        {
            enemyBullets[enemyIter].fireDirection = enemyBullets[enemyIter].NEG_NEG;
            enemyBullets[enemyIter].angleFired = firingAngle + 90;
        }
        enemyBullets[enemyIter].bullet->setVisible(true);
        enemyBullets[enemyIter].bullet->setPosition(Vec2(firingPoint.x, firingPoint.y));
        ++enemyIter;
    }
}

void Ship::SineAttack(int& enemyIter, Bullets enemyBullets[], Ship enemy)
{
    for (int i = 0; i < 2; ++i)
    {
        if (enemyIter >= 1000) enemyIter = 0;
        enemyBullets[enemyIter].fired = true;
        enemyBullets[enemyIter].firedWith = enemyBullets[enemyIter].SINE;
        if (i == 0) enemyBullets[enemyIter].fireDirection = enemyBullets[enemyIter].POS_POS;
        if (i == 1) enemyBullets[enemyIter].fireDirection = enemyBullets[enemyIter].NEG_NEG;
        enemyBullets[enemyIter].bullet->setVisible(true);
        enemyBullets[enemyIter].bullet->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, enemy.ship->getPosition().y));
        enemyBullets[enemyIter].firedX = Director::getInstance()->getVisibleSize().width / 2;
        ++enemyIter;
    }
}

void Ship::WaveAttack(int& enemyIter, Bullets enemyBullets[])
{
    for (int i = 0; i < 5; ++i)
    {
        if (enemyIter >= 1000) enemyIter = 0;
        enemyBullets[enemyIter].fired = true;
        enemyBullets[enemyIter].firedWith = enemyBullets[enemyIter].WAVE;
        enemyBullets[enemyIter].bullet->setPosition(Vec2(firingPoint.x, firingPoint.y));
        if (i == 0)
        {
            enemyBullets[enemyIter].angleFired = 90 degrees;
        }
        if (i == 1)
        {
            enemyBullets[enemyIter].angleFired = 75 degrees;
        }
        if (i == 2)
        {
            enemyBullets[enemyIter].angleFired = 60 degrees;
        }
        if (i == 3)
        {
            enemyBullets[enemyIter].angleFired = 105 degrees;
        }
        if (i == 4)
        {
            enemyBullets[enemyIter].angleFired = 120 degrees;
        }
        enemyBullets[enemyIter].bullet->setVisible(true);
        ++enemyIter;
    }
} 