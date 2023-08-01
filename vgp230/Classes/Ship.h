#pragma once
#include "cocos2d.h"
#include "Bullets.h"

USING_NS_CC;

class Ship
{
public:
	int health;
	int maxHealth;
	float speed;
	float damage = 1;
	Sprite* ship;
	float animation = 0;
	bool hasShield = false, hasBomb = false, hasDamage = false;
	bool movingLeft = false, movingRight = false, movingUp = false, movingDown = false, isFiring = false;
	Vec2 firingPoint;
	float firingAngle = 0;
	float firingRadius;
	

	enum BossAttacks
	{
		SPIRAL,
		SINE,
		WAVE,
		CIRCLE,
		REGULAR
	} BossAttacks = CIRCLE;

	enum BossNumber
	{
		FIRST,
		SECOND,
		THIRD
	} BossNumber = FIRST;

	float GetFireDelay();

	void BulletSpiralMovement(Bullets it, float dt);

	void BulletStraightMovement(Bullets it, float dt, float speedMod);

	void BulletSineMovement(Bullets &it, float dt);

	void BulletWaveMovement(Bullets& it, float dt);

	void BulletCircleMovement(Bullets& it, float dt);

	void SpiralAttack(int &enemyIter, Bullets enemyBullets[]);

	void SineAttack(int& enemyIter, Bullets enemyBullets[], Ship enemy);

	void WaveAttack(int& enemyIter, Bullets enemyBullets[]);

	void CircleAttack(int& enemyIter, Bullets enemyBullets[]);
};