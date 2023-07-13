#pragma once
#include "cocos2d.h"

USING_NS_CC;
 
class Assignment2 : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	virtual void update(float dt); 

	CREATE_FUNC(Assignment2);

private:
	Sprite* sprite1;
	Sprite* healthBar;
};