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
	//添加背景图片
	welcomeImage = Sprite::create("beijing.jpg");
	welcomeImage->setPosition(Vec2(origin.x, origin.y));
	welcomeImage->setAnchorPoint(Vec2(0, 0));//默认锚点为0.5，0.5，这里设为0，0
	//welcomeImage->setTextureRect(CCRectMake(0, 0, 500, 500));
	this->addChild(welcomeImage,0);
	
	//添加按钮
	auto SingleGame = CCMenuItemImage::create
		(
		"single1.png",     //平时的图片
		"single2.png",   //选中时的图片
		CC_CALLBACK_1(WelcomeScene::menuStartCallback, this)//点击时执行的回调方法
		);

	auto DoubleGame = CCMenuItemImage::create
		(
		"double1.png",     //平时的图片
		"double2.png",   //选中时的图片
		CC_CALLBACK_1(WelcomeScene::menuStartCallback1, this)//点击时执行的回调方法
		);
	//创建一个有两个按钮的菜单
	auto menu = Menu::create(SingleGame,DoubleGame, NULL);
	menu->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.3));
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu, 1);

	//预加载背景音乐
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_FILE);
	//播放背景音乐
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_FILE);

	return true;
}

//按钮的回调函数
void WelcomeScene::menuStartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(PlayScene::createScene());
}

void WelcomeScene::menuStartCallback1(Ref* pSender)
{
	Director::getInstance()->replaceScene(VsScene::createScene());
}