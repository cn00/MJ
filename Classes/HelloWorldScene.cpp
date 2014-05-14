#include "HelloWorldScene.h"
#include "SqlShell.h"
#include "HallScene.h"

enum Tag{
	_close_,
	_hall_,
};
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
	

    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
	closeItem->setTag(_close_);
	menu->addChild(closeItem);
	
	auto hall = MenuItemFont::create("HALL", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	hall->setPosition(400, 50);
	hall->setTag(_hall_);
	menu->addChild(hall);
	
    auto label = Label::create("Hello World", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);
    
	GameManager::sqlCommand("select * from province");
	
	auto sqll = SqlShell::create();
	this->addChild(sqll);
	
	const string cardmj[] = {
		"🀀", "🀁", "🀂", "🀃", "🀄︎", "🀅", "🀆",//*4
		"🀇", "🀈", "🀉", "🀊", "🀋", "🀌", "🀍", "🀎", "🀏",//*4
		"🀐", "🀑", "🀒", "🀓", "🀔", "🀕", "🀖", "🀗", "🀘",//*4
		"🀙", "🀚", "🀛", "🀜", "🀝", "🀞", "🀟", "🀠", "🀡",//*4
		"🀢", "🀣", "🀤", "🀥", "🀦", "🀧", "🀨", "🀩", "🀪",//*4
		"🀫",//4*43 = 172
		/*
		 13*4
		 */
	};
	const string cardpk[] = {
		"🂠",
		"🂡", "🂢", "🂣", "🂤", "🂥", "🂦", "🂧", "🂨", "🂩", "🂪", "🂫", "🂬", "🂭", "🂮",
		"🂱", "🂲", "🂳", "🂴", "🂵", "🂶", "🂷", "🂸", "🂹", "🂺", "🂻", "🂼", "🂽", "🂾",
		"🃁", "🃂", "🃃", "🃄", "🃅", "🃆", "🃇", "🃈", "🃉", "🃊", "🃋", "🃌", "🃍", "🃎", "🃏",
		"🃑", "🃒", "🃓", "🃔", "🃕", "🃖", "🃗", "🃘", "🃙", "🃚", "🃛", "🃜", "🃝", "🃞", "🃟"
	};
	map<string, Card*> cards;
	for(auto i:cardmj){
		auto card = Card::create("🀀");
		cocos2d::Texture2D* text = new Texture2D;
		text->autorelease();
		text->initWithString(i.c_str(), "seguisym.ttf", 64);
		card->initWithTexture(text);
		card->setPosition(Point(rand()%320, rand()%480));
		card->setColor(Color3B(rand()%255, rand()%255, rand()%255));
		this->addChild(card);
		
		cards.insert(make_pair(i, card));
	}
	
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
	Tag tag = Tag(((Node*)pSender)->getTag());
	switch (tag) {
		case _close_:{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
			return;
#endif
			
			Director::getInstance()->end();
			
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
			break;}
		case _hall_:{
			Director::getInstance()->replaceScene(HallScene::scene());
			break;}
			
		default:
			break;
	}
	_eventDispatcher->removeEventListenersForTarget(this);
	
}
