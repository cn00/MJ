//
//  SqlShell.h
//  MJ
//
//  Created by CN on 14-5-8.
//
//

#ifndef __MJ__SqlShell__
#define __MJ__SqlShell__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

#include "VisibleRect.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

using namespace extension;
using namespace ui;

class SqlShell : public Layer, public extension::EditBoxDelegate
{
public:
	bool init()
	{
		bool ret = false;
		do {
			if (!Layer::init())return false;
			auto cl = LayerColor::create(Color4B(10.5, 0.5, 0.5 ,0.8));
			this->addChild(cl);
			
			auto editBoxSize = Size(VisibleRect::right().x-100, 80);
			_edit = EditBox::create(editBoxSize, Scale9Sprite::create("HelloWorld.png"));
			_edit->setAnchorPoint(Point(0, 1));
			_edit->setPosition(VisibleRect::leftTop());
			_edit->setFontName("Paint Boy");
			_edit->setFontSize(25);
			_edit->setFontColor(Color3B::RED);
			_edit->setPlaceHolder("Name:");
			_edit->setPlaceholderFontColor(Color3B::WHITE);
			_edit->setMaxLength(80);
			_edit->setReturnType(EditBox::KeyboardReturnType::DONE);
			_edit->setDelegate(this);
			this->addChild(_edit);
			
			_displayValueLabel = Text::create();
			_displayValueLabel->setMaxLineWidth(VisibleRect::right().x-100);
			_displayValueLabel->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
			_displayValueLabel->setPosition(Point(50,500));
			this->addChild(_displayValueLabel);
			
			auto button = Button::create();
			button->loadTextures("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
			button->addTouchEventListener(this, toucheventselector(SqlShell::onButtonClick));
			button->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
			button->setPosition(VisibleRect::rightTop());
			button->setTag(1);
			this->addChild(button);
			
			auto button2 = button->clone();
			button2->setPosition(VisibleRect::rightTop()-Point(0, 50));
			button2->addTouchEventListener(this, toucheventselector(SqlShell::onButtonClick));
			button2->setTag(2);
			this->addChild(button2);
			
			ret = true;
		} while (0);
		
		CCLOG("SqlShell::init()");
		return ret;
		
	}
	
	void onEnter()
	{
		Layer::onEnter();
		
//		auto listener = EventListenerTouchOneByOne::create();
//		listener->onTouchBegan = CC_CALLBACK_2(SqlShell::onTouchBegan, this);
//		listener->onTouchMoved = CC_CALLBACK_2(SqlShell::onTouchMoved, this);
//		listener->onTouchEnded = CC_CALLBACK_2(SqlShell::onTouchEnded, this);
//		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

//	
//	virtual bool onTouchBegan(Touch *touch, Event *unused_event){
//		return 1;
//	};
//	
//    virtual void onTouchMoved(Touch *touch, Event *unused_event){
//	
//	};
//	
//    virtual void onTouchEnded(Touch *touch, Event *unused_event){
//	
//	};

	void onButtonClick(Ref* obj,ui::TouchEventType type){
		Point p = ((Button*)obj)->getTouchMovePos();
		CCLOG("Button[%d],[x:%f, y:%f]", ((Node*)obj)->getTag(), p.x, p.y);
		
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		
		switch (type) {
			case TOUCH_EVENT_BEGAN:
				_displayValueLabel->setText(String::createWithFormat("Touch Down")->getCString());
				break;
				
			case TOUCH_EVENT_MOVED:
				_displayValueLabel->setText(String::createWithFormat("Touch Move")->getCString());
				break;
				
			case TOUCH_EVENT_ENDED:{
				
				std::ostringstream s;
				for(auto it : GameManager::sqlRecords)
				{
					s << it.first << "\t\t";
					for(auto it2 : it.second)s<<it2<<(it2.length()<3*6?"\t\t\t\t":it2.length()<3*8?"\t\t":"\t");
					s << "\n";
				}
				
				_displayValueLabel->setText(s.str().c_str());
				break;}
				
			case TOUCH_EVENT_CANCELED:
				_displayValueLabel->setText(String::createWithFormat("Touch Cancelled")->getCString());
				break;
				
			default:
				break;
		}
	}
	
	void onButtonClick2(Ref* obj,ui::TouchEventType type){
		
	}
	
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
		
	};
	
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
		
	};
	
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
		
	};
	
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox){};
	

	
	void onMenuClick(Ref *obj);
	
    CREATE_FUNC(SqlShell);
	
private:
	EditBox* _edit;
	Text* _displayValueLabel;
};

#endif /* defined(__MJ__SqlShell__) */
