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
    enum gameState
    {
        START,
        RUNNING,
        BOSS_DEATH,
        GAME_OVER,
        VICTORY
    } gameState = START;

    Ship player;
    Ship enemy;
    Sprite* healthBar;
    Sprite* healthBarE;
    Bullets bullets[50];
    Bullets enemyBullets[500];
    DrawNode* debug;
    bool debugDrawOn = false;
    bool enemyCanFire = true;
    int iter = 0;
    int enemyIter = 0;
    float healthScale = 4;
    float animationTime = 0;
    float enemyFireDelay = 1;
};