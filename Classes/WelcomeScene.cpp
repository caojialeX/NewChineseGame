#include "WelcomeScene.h"
#include "PlayScene.h"
#include "VsScene.h"
#include "SimpleAudioEngine.h"

#define BG_FILE "bg.mp3"

using namespace cocos2d;

Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}

bool WelcomeScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = CCDirector::getInstance()->getVisibleOrigin();
	//Director::getInstance()->setContentScaleFactor(640.00 / 1080);
	Director::getInstance()->setContentScaleFactor(1080 / 640);
	//��ӱ���ͼƬ
	welcomeImage = Sprite::create("beijing.jpg");
	welcomeImage->setPosition(Vec2(origin.x, origin.y));
	welcomeImage->setAnchorPoint(Vec2(0, 0));//Ĭ��ê��Ϊ0.5��0.5��������Ϊ0��0
	//welcomeImage->setTextureRect(CCRectMake(0, 0, 500, 500));
	this->addChild(welcomeImage,0);
	
	//��Ӱ�ť
	auto SingleGame = CCMenuItemImage::create
		(
		"single1.png",     //ƽʱ��ͼƬ
		"single2.png",   //ѡ��ʱ��ͼƬ
		CC_CALLBACK_1(WelcomeScene::menuStartCallback, this)//���ʱִ�еĻص�����
		);

	auto DoubleGame = CCMenuItemImage::create
		(
		"double1.png",     //ƽʱ��ͼƬ
		"double2.png",   //ѡ��ʱ��ͼƬ
		CC_CALLBACK_1(WelcomeScene::menuStartCallback1, this)//���ʱִ�еĻص�����
		);
	//����һ����������ť�Ĳ˵�
	auto menu = Menu::create(SingleGame,DoubleGame, NULL);
	menu->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.3));
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu, 1);

	//Ԥ���ر�������
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_FILE);
	//���ű�������
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_FILE);

	return true;
}

//��ť�Ļص�����
void WelcomeScene::menuStartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(PlayScene::createScene());
}

void WelcomeScene::menuStartCallback1(Ref* pSender)
{
	Director::getInstance()->replaceScene(VsScene::createScene());
}