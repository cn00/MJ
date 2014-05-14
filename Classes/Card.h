//
//  Card.h
//  MJ
//
//  Created by CN on 14-5-9.
//
//

#ifndef __MJ__Card__
#define __MJ__Card__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace extension;
//using namespace CocosDenshion;

class Card:public Sprite
{
public:
	static Card* create(const string filename = ""){
		Card *sprite = new Card();
		if (sprite && sprite->initWithFile(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;

	};
	
	
	virtual void onEnter()
	{
		Sprite::onEnter();
		
		_listener = EventListenerTouchOneByOne::create();
		_listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
		_listener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
		_listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
		
	}
	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){
		
		if(this->getBoundingBox().containsPoint(touch->getLocation())){
			_origineZ = this->getGlobalZOrder();
			this->setLocalZOrder(300);
			this->runAction(Repeat::create(Sequence::create(
//											 ScaleTo::create(0.1, 1.2),
											 RotateTo::create(0.00, 0),
											 RotateBy::create(0.051, 40),
											 DelayTime::create(0.051),
											 RotateBy::create(0.1, -80),
											 RotateBy::create(0.051, 40),
//											 ScaleTo::create(0.1, 1),
											 nullptr), 2));
			_listener->setSwallowTouches(true);
			return true;
		}else{
			_listener->setSwallowTouches(false);
			return false;
		}
	}
	
    virtual void onTouchMoved(Touch *touch, Event *unused_event){
		this->stopAllActions();
		this->setRotation(0);
		this->cocos2d::Node::setPosition(this->getPosition()+touch->getLocation()-touch->getPreviousLocation());
//		this->runAction(Repeat::create(Sequence::create(
//														MoveBy::create(0.051, Point(0, 30)),
//														MoveBy::create(0.051, Point(0, -30)),
//														nullptr), 3));

	}
	
    virtual void onTouchEnded(Touch *touch, Event *unused_event){
		this->setLocalZOrder(_origineZ);
	}

protected:
	
private:
	int _origineZ;
	int _type;
	Color3B _color;
	EventListenerTouchOneByOne* _listener;
	
};

#endif /* defined(__MJ__Card__) */
