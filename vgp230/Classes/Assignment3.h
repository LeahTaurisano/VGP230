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

    void PlayerFire();

    void ResetBullet(Bullets &bullet);

    bool Collided(Sprite* first, Sprite* second);

    virtual void update(float dt);

    CREATE_FUNC(Assignment3);


    enum gameState
    {
        START,
        MENU,
        CONTROLS,
        RUNNING,
        BOSS_PHASE,
        BOSS_DEATH,
        GAME_OVER,
        VICTORY
    } gameState = START;

    enum Powerup
    {
        READY,
        SHIELD,
        BOMB,
        DAMAGE,
    }chosenPowerup = READY;

    std::vector<Powerup> powerupPool;
    Ship player;
    Sprite* playerShield;
    Ship enemy;
    Sprite* enemyP1;
    Sprite* enemyA1;
    Sprite* enemyA2;
    Sprite* healthBar;
    Sprite* healthBarE;
    Sprite* shieldUp;
    Sprite* damageUp;
    Sprite* bombUp;
    Sprite* background;
    Bullets bullets[50];
    Bullets enemyBullets[1000];
    DrawNode* debug;
    Label* startOption;
    Label* controlsOption;
    LayerColor* bombEffect;
    bool debugDrawOn = false;
    bool enemyCanFire = true;
    int random;
    int iter = 0;
    int enemyIter = 0;
    int numMenuOptions = 2;
    int selectedOption = 1;
    float healthScale = 4;
    float animationTime = 0;
    float enemyFireDelay;
    float bossAttackTimer = 0;
    float damageDuration = 10;
    float bombAnimationTimer = 0.05;
};