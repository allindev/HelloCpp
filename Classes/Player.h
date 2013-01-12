/*
 * Player.h
 *
 *  Created on: 2013-1-6
 *      Author: allin
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "GameBase.h"
#include "cocos2d.h"
USING_NS_CC;
class Player : public CCNode
{
//////////////////function//////////////
public:
	Player();
	~Player();
	int move(PUD);
	static Player* create(PUD, CCLayer*);
private:
	bool init(PUD, CCLayer*);
//////////////////data//////////////
public:
	PUD pud;
private:
	int spriteFlag;
	CCLayer* pLayer ;
};

#endif /* PLAYER_H_ */
