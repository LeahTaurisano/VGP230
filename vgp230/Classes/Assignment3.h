#pragma once
#include "cocos2d.h"
#include "Bullets.h"
#include "Ship.h"
#include "Stars.h"

USING_NS_CC;

class Assignment3 : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    void Move(Ship toMove, float dt);

    void EnemyMove(Ship &toMove, float dt);

    void PlayerFire();

    void PlayerAutoCheck(float dt);

    void ResetBullet(Bullets &bullet);

    bool Collided(Sprite* first, Sprite* second);

    void MoveUpgrades(float dt);

    void MoveStars(Stars stars, float dt);

    void ResetToMenu();

    virtual void update(float dt);

    CREATE_FUNC(Assignment3);


    enum gameState
    {
        START,
        MENU,
        CONTROLS,
        BOSS_INTRO,
        RUNNING,
        BOSS_PHASE,
        PHASE_ANIMATION,
        BOSS_DEATH,
        GAME_OVER,
        VICTORY,
        END_SCREEN
    } gameState = START;

    enum Powerup
    {
        READY,
        SHIELD,
        BOMB,
        DAMAGE,
    }chosenPowerup = READY;

    Stars starsL;
    Stars starsS;
    std::vector<Powerup> powerupPool;
    Ship player;
    Sprite* playerShield;
    Ship enemy;
    Sprite* enemyP2Glow;
    Sprite* enemyP3Glow;
    Sprite* enemyP1;
    Sprite* enemyP2;
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
    Label* victoryText;
    Label* gameOverText;
    Label* endText;
    LayerColor* bombEffect;
    bool debugDrawOn = false;
    bool enemyCanFire = true;
    bool resetGame = false;
    int random;
    int iter = 0;
    int enemyIter = 0;
    int numMenuOptions = 2;
    int selectedOption = 1;
    float baseHealthScale = 4;
    float healthScale = 0;
    float animationTime = 0;
    float enemyFireDelay;
    float bossAttackTimer = 0;
    float damageDuration = 10;
    float bombAnimationTimer = 0.05;
};