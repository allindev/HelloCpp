/*
 * ThreadUtils.c
 *
 *  Created on: 2012-12-21
 *      Author: Administrator
 */

#include <string>
#include "ThreadUtils.h"
#include "ODSocket.h"

using std::string;
USING_NS_CC;

ODSocket ThreadUtils::_socket;

int ThreadUtils::start() {

	_socket.Init();
	CCLog("start Create....");
	if (_socket.Create(AF_INET, SOCK_STREAM, 0) < 0) {
		CCLog("Create socket fail");
	}

	CCLog("ThreadUtils::start 1");
	if (pthread_create(&pid, NULL, start_thread, 0) != 0) {
		return -1;
	}
	CCLog("ThreadUtils::start 2");
	return 0;
}

void* ThreadUtils::start_thread(void *arg) {
	CCLog("new thread");

//	for(int i = 0; i != 100; ++i)
//	{
//		CCLog("count->%d",i);
//	}
	socketTest();

	return NULL;

}

#define  BUFFER_SIZE 255
void ThreadUtils::socketTest() {

//	ODSocket _socket;
	char buf[BUFFER_SIZE];

	CCLog("start connect ");
	if (_socket.Connect("192.168.1.10", 9123)) {
		CCLog("connect ok....");
		//socket.Send()
	}

	CCLog("end connect....");

	//strcpy(buf,"1");

	char* tmp = "1234文字";
	int tmplen = strlen(tmp);
	PND* pnd = (PND*) malloc(sizeof(PND) + tmplen);

	pnd->type = htonl(29990);
	pnd->len = htonl(tmplen);
	CCLog("per send tmplen:%d , pnd->len:%d", tmplen, pnd->len);
	memcpy(pnd->msg, tmp, tmplen);

	CCLog("per send bytes:%d", sizeof(pnd));

	int sendByteCount = _socket.Send((char*) pnd, (sizeof(PND) + tmplen));

	CCLog("send bytes:%d", sendByteCount);

	free(pnd);

//	memset(pnd,0, sizeof(PND) + strlen(tmp));

	CCLog("socket Recv start");
	int RecvByteCount = _socket.Recv(buf, sizeof(buf));
	CCLog("socket Recv end RecvByteCount:%d", RecvByteCount);

	PND* pnd2 = (PND*) malloc(RecvByteCount);

	memcpy(pnd2, buf, RecvByteCount);
//	memcpy(pnd2.msg, buf+8, pnd2.len );

	CCLog("Recv pd->type %d", ntohl(pnd2->type));

	CCLog("Recv pd->len %d", ntohl(pnd2->len));

	CCLog("Recv pd->msg %s", pnd2->msg);

	free(pnd2);

//	_socket.Clean();
//	_socket.Close();
//	int type = 29990;
//	char* tmp = "ww12aaww--中文用GB2312";
//
//	type = htonl(type);
//
//	memcpy(buf,&type,sizeof(type));
//
//	int len = strlen(tmp);
//	int nlen = htonl(len);
//
//
//	memcpy(buf+4,&nlen,sizeof(len));
//	memcpy(buf+8,tmp,len);
//
//
//	int sendByteCount = _socket->Send(buf, 4+4+len);
//	CCLog("send bytes:%d", sendByteCount);

//	memset(buf, 0, sendByteCount);
//	CCLog("recv start....");
//	_socket->Recv(buf,255,0);
//	CCLog("recv end....");
//
//
//
//	int recvValue = 0;
//	memcpy(&recvValue,buf,4);
//	recvValue = ntohl(recvValue);
//	CCLog("recv type:%d", recvValue);
//
//	int rlen = 0;
//	memcpy(&rlen,buf+4,4);
//	rlen = ntohl(rlen);
//	CCLog("recv len:%d", rlen);
//
//	char recvMsg[rlen+1];
//	CCLog("recv recvMsg start");
//	memcpy(recvMsg,buf+4+4,rlen);
//	CCLog("recv recvMsg end");
//	CCLog("recv message:%s", recvMsg);
//
//	if(recvValue > 0){
//		_socket->Close();
//	}
}
