/*
 * GameNet.h
 *
 *  Created on: 2013-1-5
 *      Author: allin
 */

#ifndef GAMENET_H_
#define GAMENET_H_

#include <map>
#include "pthread.h"
#include "cocos2d.h"

#include "GameBase.h"
#include "ODSocket.h"
#include "Player.h"

using std::map;
USING_NS_CC;



typedef  int(*GAME_NET_CALLBACK)(int event, unsigned char msg[], int len);

class GameNet
{
//////////////////function//////////////
public:

	GameNet();
	~GameNet();

	int init(CCLayer*);

	int clean();

	void setGameNetCallback(GAME_NET_CALLBACK callback);

	int sendMoveData(PUD&);
//	int login(PUD&);
//	int logout();

	Player* getPlayer();

private:
	Player* getPlayerFromMap(const int session);
	void removePlayerToMap(const int session);
	Player* addPlayerToMap(PUD);

	static void * gameReceiveThread(void *);


//////////////////data//////////////
public:

private:
	CCLayer* _pLayer;
	ODSocket _socket;
	pthread_t pid;
	bool exitGameReceiveThread;
	Player* player;
	map<int, Player*> otherPlayers;
};


#endif /* GAMENET_H_ */
