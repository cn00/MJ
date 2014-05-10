#include "HelloWorldScene.h"
#include "SqlShell.h"

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	log("origin[%f, %f], visibleSize[%f, %f]", origin.x, origin.y, visibleSize.width, visibleSize.height);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Cowboy.plist");
	
	auto ps = Sprite::createWithSpriteFrameName("testAnimationResource/11.png");
	ps->setPosition(Point(visibleSize)/4);
	this->addChild(ps);
    
    // background img
    auto sprite = Sprite::create("HelloWorld1.png");
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

    auto label = Label::create("Hello World", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);
    
	GameManager::sqlCommand("select * from province");
	
	auto sqll = SqlShell::create();
	this->addChild(sqll);
	
	for(auto i:{1, 2, 3}){
		auto card = Card::create("CloseNorma.png");
		card->setPosition(VisibleRect::center()*i/2);
		this->addChild(card);
	}
/*
	label = Label::create("🀀🀁🀂🀃🀄🀅🀆", "", 64);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	label->setPosition(VisibleRect::bottom());
	this->addChild(label);
	
	label = Label::create("🀇🀈🀉🀊🀋🀌🀍🀎🀏", "", 64);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	label->setRotation(90);
	label->setPosition(VisibleRect::left());
	this->addChild(label);
	
	label = Label::create("🀐🀑🀒🀓🀔🀕🀖🀗🀘", "", 64);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	label->setRotation(-90);
	label->setPosition(VisibleRect::right());
	this->addChild(label);
	
	label = Label::create("🀙🀚🀛🀜🀝🀞🀟🀠🀡", "", 64);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	label->setRotation(-180);
	label->setPosition(VisibleRect::top()-Point(0, 100));
	this->addChild(label);
	
	label = Label::create("🀢🀣🀤🀥🀦🀧🀨🀩🀪🀫", "", 64);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	label->setRotation(-180);
	label->setPosition(VisibleRect::center());
	this->addChild(label);
*/
	char c[] = {char(0x00), char(0x01), char(0xf0), char(0x04),};
	label = Label::create( c, "", 64);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	label->setRotation(-180);
	label->setPosition(VisibleRect::center());
	this->addChild(label);
	
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/ppxhn.mp3", true);
	
    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{

	
	Node *node = nullptr;
	int mind = 0xefffff;
	for(auto it : this->getChildren())
	{
		Size sz = it->getContentSize();
		Point an = it->getAnchorPoint();
		Point midpo = it->getPosition()-Point(sz.width*an.x, sz.height*an.y)+Point(sz/2);
		float dis = (touch->getLocation()- midpo).getLengthSq();
		Rect rec(it->getPosition()-Point(sz.width*an.x, sz.height*an.y), sz);
		mind =(rec.containsPoint(touch->getLocation()))?mind > dis?(node = it, dis):mind:(node = nullptr, 0xefffff);
	}
	
	if(node != nullptr)node->setScale(0.8);

	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
	CCLOG("onTouchMoved[%f, %f]", touch->getLocation().x, touch->getLocation().y);
	
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	
	Node *node = nullptr;
	int mind = 0xefffff;
	for(auto it : this->getChildren())
	{
		Size sz = it->getContentSize();
		Point an = it->getAnchorPoint();
		Point midpo = it->getPosition()-Point(sz.width*an.x, sz.height*an.y)+Point(sz/2);
		float dis = (touch->getLocation()- midpo).getLengthSq();
		mind = mind > dis?(node = it, dis):mind;
	}
	
	node->setScale(1);

}

void HelloWorld::menuCallback(Ref* pSender)
{
	_eventDispatcher->removeEventListenersForTarget(this);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
	
}
