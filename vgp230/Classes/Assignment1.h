#pragma once
#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Assignment1 : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	virtual void update(float dt);

	Vec2 nextPos(Sprite* sprite, Vec2 speed, float dt);

	void move(Sprite* sprite, Vec2& speed, float dt);

	CREATE_FUNC(Assignment1);

	Sprite* sprite1;
	Sprite* sprite2;

	Vec2 speed1;
	Vec2 speed2;
};