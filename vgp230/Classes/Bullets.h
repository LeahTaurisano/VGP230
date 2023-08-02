#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Bullets
{
public:
	Sprite* bullet;
	Sprite* bulletBase;
	Sprite* bulletUpgrade;
	bool fired = false, firedLeft = false, firedRight = false, playerFired = false;
	float speed = 100;
	float bulletDamage;
	float angleFired;
	float firedX;
	float cosCount = 0;
	float timeActive = 0;
	float firedRadius;
	Vec2 centerPoint; //for circle attack

	enum firedWith
	{
		SPIRAL,
		SINE,
		WAVE,
		CIRCLE,
	} firedWith;

	enum fireDirection
	{
		POS_POS,
		POS_NEG,
		NEG_POS,
		NEG_NEG
	} fireDirection = POS_POS;
};