#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct Bullets
{
	Sprite* bullet;
	bool fired = false, firedLeft = false, firedRight = false;
	float speed = 300;
};