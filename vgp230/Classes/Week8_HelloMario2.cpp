#include "Week8_HelloMario2.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#pragma warning(pop)


Scene* HelloMario2::createScene()
{
  auto ret = new (std::nothrow) HelloMario2();
  if (ret && ret->initWithPhysics() && ret->init())
  {
    ret->autorelease();
    return ret;
  }
  else
  {
    CC_SAFE_DELETE(ret);
    return nullptr;
  }

  return ret;
}

bool HelloMario2::init()
{
  /// TODO: call load() which loads the save file
    load();

  if (!HelloMarioSolution::init())
  {
    return false;
  }

  initPauseMenu();

  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
  {
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
      /// TODO: call showPauseMenu / hidePauseMenu depending on if menu is visible
        if (menu->isVisible()) hidePauseMenu();
        else showPauseMenu();
    }
  };

  auto dispatcher = Director::getInstance()->getEventDispatcher();

  dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

  return true;
}

void HelloMario2::initPauseMenu()
{
  // Create "New Game" button
  auto newGameButton = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 24), [=](cocos2d::Ref* sender) 
  {
    /// Bonus: Reset the game
  });

  /// TODO: Create save button which calls the "save()" function
  auto saveGameButton = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithTTF("Save Game", "fonts/Marker Felt.ttf", 24), [=](cocos2d::Ref* sender)
      {
          save();
      });

  /// TODO: Create load button which calls the "load()" button
  auto loadGameButton = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithTTF("Load Game", "fonts/Marker Felt.ttf", 24), [=](cocos2d::Ref* sender)
      {
          load();
      });

  /// TODO: Create Quit button
  auto quitGameButton = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithTTF("Quit Game", "fonts/Marker Felt.ttf", 24), [=](cocos2d::Ref* sender)
      {
          
      });

  /// TODO: add buttons to menu

  // TODO: add buttons into menu below
  menu = cocos2d::Menu::create(newGameButton, saveGameButton, loadGameButton, quitGameButton, nullptr);

  menu->alignItemsVerticallyWithPadding(20);

  // Add the menu to the scene
  this->addChild(menu);

  hidePauseMenu();
}

void HelloMario2::showPauseMenu() 
{
  auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
  auto pos = Vec2{ cocos2d::Director::getInstance()->getVisibleSize() * 0.5f } + origin;

  Vec2 screenCenter = Director::getInstance()->getVisibleSize() * 0.5f;

  // Get the camera's position
  Vec2 cameraPosition = _defaultCamera->getPosition();

  // Calculate the offset for the menu's position
  Vec2 menuOffset = cameraPosition - screenCenter;

  /// TODO: Pause Physics from updating
  getPhysicsWorld()->setSpeed(0);

  menu->setPosition(pos + menuOffset);
  menu->setVisible(true);
}

void HelloMario2::hidePauseMenu()
{
  /// TODO: Resume Physics from updating
    getPhysicsWorld()->setSpeed(1);
  /// TODO: Hide menu
    menu->setVisible(false);
}

void HelloMario2::update(float dt)
{
  ///TODO: If menu is open, don't call below
    if (!menu->isVisible()) HelloMarioSolution::update(dt);
}

void HelloMario2::load()
{
  std::string jsonString = cocos2d::FileUtils::getInstance()->getStringFromFile("Mario.json");

  if (jsonString != "")
  {
    rapidjson::Document document;
    document.Parse(jsonString.c_str());
    
    if (document.HasParseError()) 
    {
      std::stringstream ss;
      ss << "Error parsing JSON: ErrorCode " << document.GetParseError();
      std::string s = ss.str();
      return;
    }
    
    if (document.HasMember("WalkSpeed") && document["WalkSpeed"].IsFloat()) 
    {
      ///TODO: Add variable walkSpeed to base class, then uncomment line below
      walkSpeed = document["WalkSpeed"].GetFloat();
    }
    
    ///TODO: load JumpSpeed into jumpSpeed -- Add variable to base class
    if (document.HasMember("JumpSpeed") && document["JumpSpeed"].IsFloat())
    {
        jumpSpeed = document["JumpSpeed"].GetFloat();
    }

    ///TODO: load Scale into scale -- Add variable to base class
    if (document.HasMember("Scale") && document["Scale"].IsFloat())
    {
        scale = document["Scale"].GetFloat();
    }

    if (document.HasMember("StartPosition") && document["StartPosition"].IsObject())
    {
      auto obj = document["StartPosition"].GetObjectW();
      float x = obj.HasMember("X") && obj["X"].IsFloat() ? obj["X"].GetFloat() : 0.0f;
      float y = obj.HasMember("Y") && obj["Y"].IsFloat() ? obj["Y"].GetFloat() : 0.0f;
      ///TODO: load "Y" parameter
      
      ///TODO: Add variable startPosition to base class, then uncomment line below
      startPosition = { x, y };
    }
  }
}

void HelloMario2::save()
{
  rapidjson::Document document;
  document.SetObject();

  document.AddMember("WalkSpeed", walkSpeed, document.GetAllocator());
  ///TODO: save JumpSpeed
  document.AddMember("JumpSpeed", jumpSpeed, document.GetAllocator());
  ///TODO: save Scale (mario size)
  document.AddMember("Scale", scale, document.GetAllocator());

  rapidjson::Value start(rapidjson::kObjectType);
  /// TODO: add marios position into "X", and "Y" members inside of start 
  
  start.AddMember("X", GetMarioPosition().x, document.GetAllocator());
  start.AddMember("Y", GetMarioPosition().y, document.GetAllocator());
  document.AddMember("StartPosition", start, document.GetAllocator());
  
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  document.Accept(writer);

  std::string jsonStr = buffer.GetString();

  auto fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename("Mario.json");
  cocos2d::FileUtils::getInstance()->writeStringToFile(jsonStr, fullPath);
  /// TODO: Write json string to fullPath using FileUtils (writeStringToFile)
}