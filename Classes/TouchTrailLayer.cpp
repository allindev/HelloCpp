/*
 * cocos2d+ext for iPhone
 *
 * Copyright (c) 2011 - Ngo Duc Hiep
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "TouchTrailLayer.h"

bool TouchTrailLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	//setIsTouchEnabled(true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 1, false);
    map = new CCMutableDictionary<CCTouch*, CCBlade*>();
	map->retain();
	//schedule(schedule_selector(TouchTrailLayer::autoDim),1/60);
	return true;
}

void TouchTrailLayer::autoDim(float t)
{
	for(unsigned int i=0; i<map->count(); i++)
	{
		CCTouch* pTouch = map->allKeys()[i];
		CCBlade *w = map->objectForKey(pTouch);
		w->pop(1);
	}
}

bool TouchTrailLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	CCBlade *w = CCBlade::bladeWithMaximumPoint(100);
	w->setTexture(CCTextureCache::sharedTextureCache()->addImage("game/streak1.png"));
        
	map->setObject(w,pTouch);
	addChild(w);        

	CCPoint pos = pTouch->locationInView(pTouch->view());
	pos = CCDirector::sharedDirector()->convertToGL(pos);
	w->push(pos);

	return true;
}

void TouchTrailLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	CCBlade *w = map->objectForKey(pTouch);
	CCPoint pos = pTouch->locationInView(pTouch->view());
	pos = CCDirector::sharedDirector()->convertToGL(pos);
	w->push(pos);
}

void TouchTrailLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	CCBlade *w = (CCBlade *)map->objectForKey(pTouch);
	w->dim(true);
	map->removeObjectForKey(pTouch);
}

void TouchTrailLayer::clenup() 
{
    map->release();
    CCNode::cleanup();
}
