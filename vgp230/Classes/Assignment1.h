#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Assignment1 : public Scene
{
public: 
	static Scene* createScene();

	virtual bool init();

	virtual void update(float dt);

	CREATE_FUNC(Assignment1);

	Sprite* sprite1;
};