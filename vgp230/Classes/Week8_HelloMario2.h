#pragma once

#include "Week7_HelloMarioSolution.h"

class HelloMario2 : public HelloMarioSolution
{
public:
  static Scene* createScene();

  virtual bool init();

  virtual void update(float dt);

  void load();

  void save();

  void initPauseMenu();

  void showPauseMenu();
  void hidePauseMenu();

  CREATE_FUNC(HelloMarioSolution)
private:
  cocos2d::Menu* menu;
};