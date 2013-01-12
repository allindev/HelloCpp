#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "GameNet.h"
USING_NS_CC;

//CCLayer* HelloWorld::curLayer = 0;
CCScene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld* layer = HelloWorld::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", this,
			menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(
			ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
					origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	setTouchEnabled(true);

//	CCLayer* layer = CCLayerColor::create(ccc4(255,255,0,255));
//	addChild(layer, -1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(
			ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	CCSprite* pSprite2 = CCSprite::create("CloseNormal2.png");
//	pSprite2->setPosition(ccp(200,200));
//	this->addChild(pSprite2, -1);

	gameNet.init(this);

	return true;
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*) (*it);

	CCPoint location = touch->getLocation();

	PUD pud = { gameNet.getPlayer()->pud.session, GAME_EVENT_MOVE,
				0, 0, 0, 10, 10,
				location.x, location.y };

//	CCLog("player move pud:  session=%d,type=%d,x1=%d,y1=%d,x2=%d,y2=%d",
//			pud.session,pud.type,pud.x1,pud.y1,pud.x2,pud.y2);
	gameNet.sendMoveData(pud);
}

void HelloWorld::menuCloseCallback(CCObject* pSender) {

	gameNet.clean();

	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

