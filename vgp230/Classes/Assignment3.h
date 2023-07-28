#pragma once
#include "cocos2d.h"
#include "Bullets.h"
#include "Ship.h"

USING_NS_CC;

class Assignment3 : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    void Move(Ship toMove, float dt);

    void EnemyMove(Ship &toMove, float dt);

    void ResetBullet(Bullets &bullet);

    virtual void update(float dt);

    CREATE_FUNC(Assignment3);

private:
    Ship player;
    Ship enemy;
    Sprite* healthBar;
    Sprite* healthBarE;
    Bullets bullets[100];
    DrawNode* debug;
    bool debugDrawOn = false;
    int iter = 0;
    float healthScale = 4;
};