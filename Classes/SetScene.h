#ifndef _SETSCENE_H_
#define _SETSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

//设置界面
class SetScene : public Layer
{
protected:
	//设置界面的背景图片
	Sprite* SetPicture;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SetScene);
};

#endif