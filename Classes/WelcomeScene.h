#ifndef _WELCOMESCENE_H_
#define _WELCOMESCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

//��ӭ���� 
class WelcomeScene : public Layer
{
protected:
	//��ӭ����ͼƬ
	Sprite* welcomeImage;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
	//��ť�Ļص�����
	void menuStartCallback(Ref* pSender);
	void menuStartCallback1(Ref* pSender);
};

#endif