#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct Bullets
{
	Sprite* bullet;
	bool fired = false, firedLeft = false, firedRight = false, playerFired = false;
	float speed = 100;
	float damage = 1;
};