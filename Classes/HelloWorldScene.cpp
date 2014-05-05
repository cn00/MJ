#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	log("origin[%f, %f], visibleSize[%f, %f]", origin.x, origin.y, visibleSize.width, visibleSize.height);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Cowboy.plist");
	
	auto ps = Sprite::createWithSpriteFrameName("testAnimationResource/1.png");
	ps->setPosition(Point(visibleSize)/4);
	this->addChild(ps);
    
    // background img
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Point(visibleSize/2));
    this->addChild(sprite, 0);
	
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    auto label = LabelTTF::create("Hello World", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);
    
	
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/ppxhn.mp3", true);
	
    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
	CCLOG("onTouchMoved[%f, %f]", touch->getLocation().x, touch->getLocation().y);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	
}

void HelloWorld::menuCallback(Ref* pSender)
{
	_eventDispatcher->removeEventListenersForTarget(this);
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
 */
	
}
