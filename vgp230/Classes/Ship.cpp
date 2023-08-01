#include "Ship.h";
#define degrees * 3.14159 / 180
#define bulletIter enemyBullets[enemyIter]

float Ship::GetFireDelay()
{
    if (BossAttacks == SINE) return 0.6 / ((int)BossNumber + 1);
    if (BossAttacks == SPIRAL) return 0.3 / ((int)BossNumber + 1);
    if (BossAttacks == WAVE) return 0.6 / ((int)BossNumber + 1);
    if (BossAttacks == CIRCLE) return 1.2 / ((int)BossNumber + 1);
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

void Ship::BulletStraightMovement(Bullets it, float dt, float speedMod)
{
    auto prevX = it.bullet->getPosition().x;
    auto prevY = it.bullet->getPosition().y;
    it.bullet->setPosition(Vec2(prevX, prevY - (it.speed * speedMod * dt)));
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

void Ship::BulletCircleMovement(Bullets& it, float dt)
{
    it.angleFired += 0.5;
    it.centerPoint = Vec2(it.centerPoint.x, it.centerPoint.y - (it.speed * 3 * dt));
    it.bullet->setPosition(Vec2(it.centerPoint.x + cos(it.angleFired degrees) * it.firedRadius, it.centerPoint.y + sin(it.angleFired degrees) * it.firedRadius));
    BulletStraightMovement(it, dt, 2);
}

void Ship::SpiralAttack(int &enemyIter, Bullets enemyBullets[])
{
    for (int i = 0; i < 4; ++i)
    {
        if (enemyIter >= 1000) enemyIter = 0;
        bulletIter.fired = true;
        bulletIter.firedWith = bulletIter.SPIRAL;
        if (i == 0)
        {
            bulletIter.fireDirection = bulletIter.POS_NEG;
            bulletIter.angleFired = firingAngle;
        }
        if (i == 1)
        {
            bulletIter.fireDirection = bulletIter.POS_NEG;
            bulletIter.angleFired = firingAngle + 90;
        }
        if (i == 2)
        {
            bulletIter.fireDirection = bulletIter.NEG_NEG;
            bulletIter.angleFired = firingAngle;
        }
        if (i == 3)
        {
            bulletIter.fireDirection = bulletIter.NEG_NEG;
            bulletIter.angleFired = firingAngle + 90;
        }
        bulletIter.bullet->setVisible(true);
        bulletIter.bullet->setPosition(Vec2(firingPoint.x, firingPoint.y));
        ++enemyIter;
    }
}

void Ship::SineAttack(int& enemyIter, Bullets enemyBullets[], Ship enemy)
{
    for (int i = 0; i < 2; ++i)
    {
        if (enemyIter >= 1000) enemyIter = 0;
        bulletIter.fired = true;
        bulletIter.firedWith = bulletIter.SINE;
        if (i == 0) bulletIter.fireDirection = bulletIter.POS_POS;
        if (i == 1) bulletIter.fireDirection = bulletIter.NEG_NEG;
        bulletIter.bullet->setVisible(true);
        bulletIter.bullet->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, enemy.ship->getPosition().y));
        bulletIter.firedX = Director::getInstance()->getVisibleSize().width / 2;
        ++enemyIter;
    }
}

void Ship::WaveAttack(int& enemyIter, Bullets enemyBullets[])
{
    for (int i = 60; i <= 120; i += 15)
    {
        if (enemyIter >= 1000) enemyIter = 0;
        bulletIter.fired = true;
        bulletIter.firedWith = bulletIter.WAVE;
        bulletIter.bullet->setPosition(Vec2(firingPoint.x, firingPoint.y));
        bulletIter.angleFired = i degrees;
        bulletIter.bullet->setVisible(true);
        ++enemyIter;
    }
} 

void Ship::CircleAttack(int& enemyIter, Bullets enemyBullets[])
{
    for (int i = 0; i < 360; i += 45)
    {
        if (enemyIter >= 1000) enemyIter = 0;
        bulletIter.fired = true;
        bulletIter.firedWith = bulletIter.CIRCLE;
        bulletIter.centerPoint = firingPoint;
        bulletIter.angleFired = i;
        bulletIter.firedRadius = 200;
        bulletIter.bullet->setVisible(true);
        bulletIter.bullet->setPosition(Vec2(firingPoint.x + bulletIter.firedRadius * cos(i degrees), firingPoint.y + bulletIter.firedRadius * sin(i degrees)));
        ++enemyIter;
    }
}