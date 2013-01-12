/*
 * Player.cpp
 *
 *  Created on: 2013-1-6
 *      Author: allin
 */

#include "Player.h"
#include "cocos2d.h"
#include "ODSocket.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Player::Player():spriteFlag(0),pLayer(NULL){

}

Player::~Player(){
}


Player* Player::create(PUD pud, CCLayer* pLayer) {

	CCLog("Player::create...");

	Player *player = new Player();

	if (player && player->init(pud, pLayer)) {
		//player->autorelease();
		return player;

	} else {
		CC_SAFE_DELETE(player);
		return NULL;
	}

	return player;

}

bool Player::init(PUD pud, CCLayer* pLayer){
	this->pLayer = pLayer;
	this->pud = pud;
	this->spriteFlag = pud.session;
	CCLog("Player::create -> CCSprite::create('CloseNormal.png'), player.spriteFlag:%d:",this->spriteFlag);
	CCSprite* sprite;
	if(pud.session % 2 == 0){
		sprite = CCSprite::create("CloseNormal.png");
	}else {
		sprite = CCSprite::create("CloseNormal2.png");
	}
	sprite->setPosition(ccp(pud.x1,pud.y1));
	this->pLayer->addChild(sprite, 1, this->spriteFlag);
	return true;
}
int Player::move(PUD pud) {
	CCLog("Player::move ->  player.spriteFlag:%d:",spriteFlag);
	CCNode* s = pLayer->getChildByTag(spriteFlag);
	s->stopAllActions();
	CCLog("Player::CCMoveTo:(%d,%d)",pud.x2,pud.y2);
	s->runAction(CCMoveTo::create(1, ccp(pud.x2,pud.y2)) );
	return 0;
}

