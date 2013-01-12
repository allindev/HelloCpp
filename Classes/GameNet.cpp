/*
 * GameNet.cpp
 *
 *  Created on: 2013-1-6
 *      Author: allin
 */

#include "GameNet.h"
#include "GameBase.h"

static GAME_NET_CALLBACK g_callback = NULL;

GameNet::GameNet() :
		exitGameReceiveThread(false),_pLayer(NULL) {

}

GameNet::~GameNet() {

}

int GameNet::init(CCLayer* pLayer) {
	_pLayer = pLayer;
	_socket.Init();
	CCLog("start Create....");
	if (_socket.Create(AF_INET, SOCK_STREAM, 0) < 0) {
		CCLog("Create socket fail");
	}


	if (pthread_create(&pid, NULL, gameReceiveThread, this) != 0) {
		return -1;
	}

	return 0;
}

int GameNet::clean() {
	exitGameReceiveThread = true;
	if (_socket) {
		_socket.Clean();
		_socket.Close();

		return 0;
	}
	return -1;
}

Player* GameNet::getPlayer() {
	return player;
}

int GameNet::sendMoveData(PUD& pud) {
	if (!_socket) {
		return -1;
	}

	pud.PUD_htonl();

	int sendByteCount = _socket.Send((char*)(&pud), (sizeof(PUD)));
	CCLog("send bytes:%d", sendByteCount);

	if (sendByteCount > 0)
		return 0;

	return -1;
}

void GameNet::setGameNetCallback(GAME_NET_CALLBACK callback) {
	g_callback = callback;
}

void GameNet::removePlayerToMap(const int session) {

	map< int, Player* >::iterator it = otherPlayers.find(session);

	if (it != otherPlayers.end()) {
		it->second->autorelease();
		otherPlayers.erase(it);
	}
}

Player* GameNet::getPlayerFromMap(const int session) {
	CCLog("GameNet::getPlayerFromMap...session:%d",session);
	map< int, Player* >::iterator it = otherPlayers.find(session);
	CCLog("GameNet::getPlayerFromMap...2");

	if (it != otherPlayers.end()) {
		CCLog("GameNet::getPlayerFromMap -> pud.session:%d",it->second->pud.session);
		return it->second;
	}
	CCLog("GameNet::getPlayerFromMap..3");

	return NULL;
}

Player* GameNet::addPlayerToMap(PUD pud) {

	CCLog("GameNet::addPlayerToMap...session:%d",pud.session);

	int session = pud.session;

	map< int, Player* >::iterator it = otherPlayers.find(session);
	Player* player = Player::create(pud, _pLayer);
	if (it == otherPlayers.end()) {
		CCLog("GameNet::addPlayerToMap  -> otherPlayers.insert session:%d",pud.session);
		otherPlayers.insert(map< int, Player* >::value_type(session, player));
		return player;
	}

	return it->second;
}

void* GameNet::gameReceiveThread(void *arg) {
	CCLog("new [gameReceiveThread] thread");

	GameNet* gameNet = (GameNet*)arg;

	CCLog("start connect ");
	if (!gameNet->_socket.Connect(SERVER_IP, SERVER_PORT)){

		CCLog("connect fail....");

		return 0;
	}

	CCLog("connect ok....");



	char recv_buf[255];
	while (!gameNet->exitGameReceiveThread) {

		CCLog("socket Recv start");
		int RecvByteCount = gameNet->_socket.Recv(recv_buf, sizeof(recv_buf));
		CCLog("socket Recv end RecvByteCount:%d", RecvByteCount);

		PUD* pud = (PUD*) malloc(RecvByteCount);

		memcpy(pud, recv_buf, RecvByteCount);

		pud->PUD_ntohl();
		int type = pud->type;
		CCLog("Recv pd->type %d", type);

		switch (type) {

		case GAME_EVENT_LOGIN_SELF:
			gameNet->player = gameNet->addPlayerToMap((*pud));
			break;

		case GAME_EVENT_LOGOUT_SELF:
			break;

		case GAME_EVENT_LOGIN:
			gameNet->addPlayerToMap((*pud));

			break;

		case GAME_EVENT_LOGOUT:
			gameNet->removePlayerToMap(pud->session);
			break;

		case GAME_EVENT_MOVE:
			Player* pplayer;
			pplayer = gameNet->getPlayerFromMap(pud->session);
			if (pplayer != NULL) {
				pplayer->move((*pud));
			}
			break;

		default:
			break;
		}

//		CCLog("Recv pd->len %d", ntohl(pnd->len));
//
//		CCLog("Recv pd->msg %s", pnd->msg);

		free(pud);

	}

	return NULL;

}
