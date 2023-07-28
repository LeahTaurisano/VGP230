#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Ship
{
public:
	int health;
	int maxHealth;
	float speed;
	Sprite* ship;
	bool movingLeft = false, movingRight = false, movingUp = false, movingDown = false, isFiring = false;
};