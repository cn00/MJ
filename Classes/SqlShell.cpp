//
//  SqlShell.cpp
//  MJ
//
//  Created by CN on 14-5-8.
//
//

#include "SqlShell.h"
#include "ui/UIButton.h"


bool SqlShell::init()
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
		_edit->setMaxLength(8);
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
		this->addChild(button);
		
		ret = true;
	} while (0);
	
	CCLOG("SqlShell::init()");
	return ret;

}

void SqlShell::onEnter()
{
	Layer::onEnter();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SqlShell::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SqlShell::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SqlShell::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SqlShell::onMenuClick(Ref *obj)
{
	
}