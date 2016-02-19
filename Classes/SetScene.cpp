#include "SetScene.h"
#include "cocos2d.h"

using namespace cocos2d;

Scene* SetScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SetScene::create();
	scene->addChild(layer);
	return scene;
}

bool SetScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = CCDirector::getInstance()->getVisibleOrigin();

	//��ӱ���ͼƬ
	SetPicture = Sprite::create("setpicture.jpg");
	SetPicture->setPosition(Vec2(origin.x, origin.y));
	SetPicture->setAnchorPoint(Vec2(0, 0));//Ĭ��ê��Ϊ0.5��0.5��������Ϊ0��0
	this->addChild(SetPicture, 0);
	
	return true;
}

