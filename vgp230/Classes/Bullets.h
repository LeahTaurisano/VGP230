#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Bullets
{
public:
	Sprite* bullet;
	bool fired = false, firedLeft = false, firedRight = false, playerFired = false;
	float speed = 100;
	float damage = 1;
	float angleFired;
	float firedX;
	float cosCount = 0;
	float timeActive = 0;

	enum firedWith
	{
		SPIRAL,
		SINE,
		WAVE,
		REGULAR
	} firedWith = REGULAR;

	enum fireDirection
	{
		POS_POS,
		POS_NEG,
		NEG_POS,
		NEG_NEG
	} fireDirection = POS_POS;
};