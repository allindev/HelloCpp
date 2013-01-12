/*
 * base.h
 *
 *  Created on: 2013-1-6
 *      Author: allin
 */

#ifndef BASE_H_
#define BASE_H_

#include "ODSocket.h"

#define SERVER_IP "172.16.11.53"
#define SERVER_PORT 9123
#define RECV_BUFFER_SIZE 255

#define GAME_EVENT_LOGIN_SELF			0x1001
#define GAME_EVENT_LOGOUT_SELF			0x1002
#define GAME_EVENT_LOGIN				0x1003
#define GAME_EVENT_LOGOUT				0x1004

#define GAME_EVENT_MOVE					0x2001



typedef struct
{
	int session;			//玩家编号
	int type;				//类型
	int direction;			//方向
	int speed;				//速度
	int accelerations;		//加速度
	int x1;					//起点x坐标
	int y1;					//起点y坐标
	int x2;					//终点x坐标
	int y2;					//终点y坐标

	void PUD_ntohl(){
		session = ntohl(session);
		type = ntohl(type);
		direction = ntohl(direction);
		speed = ntohl(speed);
		accelerations = ntohl(accelerations);
		x1 = ntohl(x1);
		y1 = ntohl(y1);
		x2 = ntohl(x2);
		y2 = ntohl(y2);
	}

	void PUD_htonl(){
		session = htonl(session);
		type = htonl(type);
		direction = htonl(direction);
		speed = htonl(speed);
		accelerations = htonl(accelerations);
		x1 = htonl(x1);
		y1 = htonl(y1);
		x2 = htonl(x2);
		y2 = htonl(y2);
	}



}PUD;

#endif /* BASE_H_ */
