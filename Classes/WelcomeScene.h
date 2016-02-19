#ifndef _WELCOMESCENE_H_
#define _WELCOMESCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

//欢迎界面 
class WelcomeScene : public Layer
{
protected:
	//欢迎界面图片
	Sprite* welcomeImage;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
	//按钮的回调函数
	void menuStartCallback(Ref* pSender);
	void menuStartCallback1(Ref* pSender);
};

#endif