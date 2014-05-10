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
	static Card* create(const string filename){
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
		
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		
	}
	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){
		if(this->getBoundingBox().containsPoint(touch->getLocation())){
		
			this->runAction(Repeat::create(Sequence::create(
//											 ScaleTo::create(0.1, 1.2),
											 RotateBy::create(0.051, 40),
											 DelayTime::create(0.051),
											 RotateBy::create(0.1, -80),
											 RotateBy::create(0.051, 40),
//											 ScaleTo::create(0.1, 1),
											 nullptr), 3));
			return true;
		}else{
			return false;
		}
	};
	
    virtual void onTouchMoved(Touch *touch, Event *unused_event){
		this->stopAllActions();
		this->runAction(Repeat::create(Sequence::create(
														MoveBy::create(0.051, Point(0, 30)),
														MoveBy::create(0.051, Point(0, -30)),
														nullptr), 3));

	};
	
    virtual void onTouchEnded(Touch *touch, Event *unused_event){
	
	};

protected:
	
private:
	int _type;
	Color3B _color;
	
};

#endif /* defined(__MJ__Card__) */
