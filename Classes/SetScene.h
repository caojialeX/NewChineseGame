#ifndef _SETSCENE_H_
#define _SETSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

//���ý���
class SetScene : public Layer
{
protected:
	//���ý���ı���ͼƬ
	Sprite* SetPicture;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SetScene);
};

#endif