#include "CollisionTestScene.h"
#include "CollisionComponent.h"


bool CollisionTestScene::init()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	active = stone = Sprite::create("stone.png");
	stone->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	stone->addComponent(CollisionComponent::createBox(stone->getContentSize().width, stone->getContentSize().height));

	mushroom = Sprite::create("mushroom.png");
	mushroom->setPosition(Vec2(visibleSize.width / 4.0f, visibleSize.height / 4.0f));
	mushroom->setScale(3.0f);
	mushroom->addComponent(CollisionComponent::createCircle((mushroom->getContentSize().width / 2) * 3));

	bullet2 = Sprite::create("bullet2.png");
	bullet2->setPosition(Vec2(visibleSize.width / 8.0f, visibleSize.height / 4.0f));
	bullet2->addComponent(CollisionComponent::createCircle(bullet2->getContentSize().width / 2));


	hummer = Sprite::create("hummer.png");
	hummer->setPosition(Vec2(7.0f * visibleSize.width / 8.0f, visibleSize.height / 4.0f));
	hummer->addComponent(CollisionComponent::createBox(hummer->getContentSize().width, hummer->getContentSize().height * .4));

	circle = Sprite::create("crosshair.png");
	circle->setPosition(20, 20);
	circle->addComponent(CollisionComponent::createDot());

	auto label = Label::create();
	label->setString("Arrow keys to move\n\nm: Mushroom\nb: Bullet\ns: Stone\nh: Hummer\nc: Circle\nd: Debug draw");
	label->setPosition(Vec2(label->getContentSize().width / 2.0f + 10, visibleSize.height - label->getContentSize().height / 2.0f - 10));

	this->addChild(stone, 0);
	this->addChild(mushroom, 0);
	this->addChild(bullet2, 0);
	this->addChild(hummer, 0);
	this->addChild(circle, 0);
	this->addChild(label, 0);

	debug = DrawNode::create(5);
	this->addChild(debug, 1);

	this->scheduleUpdate();

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_S:
			active = stone;
			break;
		case EventKeyboard::KeyCode::KEY_M:
			active = mushroom;
			break;
		case EventKeyboard::KeyCode::KEY_B:
			active = bullet2;
			break;
		case EventKeyboard::KeyCode::KEY_H:
			active = hummer;
			break;
		case EventKeyboard::KeyCode::KEY_C:
			active = circle;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			debugDrawEnabled = !debugDrawEnabled;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			left = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			right = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			up = true;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			down = true;
			break;
		};
	};

	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			left = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			right = false;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			up = false;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			down = false;
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	return true;
}

void CollisionTestScene::update(float dt)
{
	if (active != NULL && (left || right || up || down))
	{
		auto p = active->getPosition();

		if (left)
		{
			p.x -= 200 * dt;
		}

		if (right)
		{
			p.x += 200 * dt;
		}

		if (up)
		{
			p.y -= 200 * dt;
		}

		if (down)
		{
			p.y += 200 * dt;
		}

		active->setPosition(p);
	}

	debug->clear();
	debug->setLineWidth(5);

	/// Reset all collision
	for (auto it : this->getChildren())
	{
		if (auto collision = dynamic_cast<CollisionComponent*>(it->getComponent("CollisionComponent")))
		{
			collision->SetColliding(false);
		}
	}

	auto& children = this->getChildren();

	/// Determine all colliding objects
	/// TODO: ADD CODE Here
	for (auto it = children.begin(); it != children.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != children.end(); ++it2)
		{
			auto collision = dynamic_cast<CollisionComponent*>((*it)->getComponent("CollisionComponent"));
			auto collision2 = dynamic_cast<CollisionComponent*>((*it2)->getComponent("CollisionComponent"));

			if (collision && collision2 && collision->IsColliding(collision2))
			{
				collision->SetColliding(true);
				collision2->SetColliding(true);
			}
		}
	}
	///

	if (debugDrawEnabled)
	{
		for (auto it : this->getChildren())
		{
			auto collision = dynamic_cast<CollisionComponent*>(it->getComponent("CollisionComponent"));

			if (collision != NULL)
			{
				auto position = it->getPosition();

				auto color = collision->IsColliding() ? Color4F::RED : Color4F::GREEN;

				switch (collision->GetCollisionType())
				{
				case CollisionComponent::Box:
				{
					auto dx = collision->GetWidth() / 2.0f;
					auto dy = collision->GetHeight() / 2.0f;
					debug->drawRect(Vec2(position.x - dx, position.y + dy), Vec2(position.x + dx, position.y + dy), Vec2(position.x + dx, position.y - dy), Vec2(position.x - dx, position.y - dy), color);
				}
				break;
				case CollisionComponent::Circle:
				{
					auto radius = collision->GetRadius();
					debug->drawCircle(position, radius, 10, 360, false, color);
				}
				break;
				case CollisionComponent::Point:
					debug->drawDot(position, 3, color);
					break;
				}
			}
		}
	}
}

