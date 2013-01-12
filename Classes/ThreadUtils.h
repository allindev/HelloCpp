/*
 * ThreadUtils.h
 *
 *  Created on: 2012-12-21
 *      Author: Administrator
 */

#ifndef THREADUTILS_H_
#define THREADUTILS_H_

#include "cocos2d.h"
#include "pthread.h"
#include "ODSocket.h"

USING_NS_CC;

typedef struct {
	int type;
	int len;
	char msg[];

}PND;

class ThreadUtils {
public:
	int start();

private:
	static void * start_thread(void *);
	static void socketTest();

public:
	static ODSocket _socket;

private:
	pthread_t pid;
};

#endif /* THREADUTILS_H_ */
