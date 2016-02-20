#include "PlayScene.h"
//#include "AI.h"
//#include "AI1.h"
//#include "AI2.h"
#include "AI3.h"
#include "WelcomeScene.h"
#include <math.h>
#include <SimpleAudioEngine.h>

#define EFFECT_MUSIC "CAPTURE.WAV"

using namespace cocos2d;
using namespace CocosDenshion;

const int MAX_HISTORY = 1200;
const int BOARD_EDGE = 8 * (457.00 / 580.00);
const int SQUARE_SIZE = 56 * (457.00 / 580.00);
const int BOARD_POSITION_X = 0;
const int BOARD_POSITION_Y = 130;
Point origin = CCDirector::getInstance()->getVisibleOrigin();
EventListenerTouchOneByOne* listener1;
MenuItemImage* huiqiButton;
MenuItemImage* exitButton;

Point startPoint;
Point endPoint;
bool isSelected = false;
//是否轮到电脑走棋
bool isBot = false;
//记录玩家移动棋子所需要的时间
float movetime = 0;
Size visibleSize;
int historyNum = 0;

//历史走法信息表（悔棋用）
struct HistoryMove
{
	WORD wmv;               //上一步走法
	Sprite* ucpcCaptured;     //上一步终点的棋子

	void _Set(int mv, Sprite* pcCaptured)
	{
		wmv = mv;
		ucpcCaptured = pcCaptured;
	}
}historyList[MAX_HISTORY];

void ClearHistory()             //清空历史走法（悔棋）信息
{
	historyList[0]._Set(0, nullptr);
	historyNum = 1;
}

Scene* PlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}

//schedule中调用，每个时间间隔中执行一次，处理逻辑
void PlayScene::update(float dt)
{
	if (isBot == true)
	{
		ResponseMove(); // 轮到电脑走棋
		isBot = false;
	}
}

//播放走棋音效，在scheduleOnce中调用（为了延时播放，即棋子走完后再播放）
void PlayScene::playEffect(float dt)
{
	//播放走棋音效
	SimpleAudioEngine::getInstance()->playEffect(EFFECT_MUSIC);
}

//将棋子摆放到棋盘上的对应的位置上，左下角坐标为（0，0）,默认层次为1，层次越高，显示越靠前
void PlayScene::setStonePosition(int x, int y, Sprite* stone)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	stone->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
	//stone->setAnchorPoint(Vec2(0, 0));//默认锚点为0.5，0.5
	this->addChild(stone, 1);
}

//多了个setVisible函数，此方法在悔棋的函数中会用到
void PlayScene::_setStonePosition(int x, int y, Sprite* stone)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	stone->setVisible(true);
	stone->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), stone);

	//stone->setAnchorPoint(Vec2(0, 0));//默认锚点为0.5，0.5
	//this->addChild(stone, 1);
}

//初始化棋子精灵
void PlayScene::initStone()
{
	//红方棋子
	//车
	rRook = Sprite::create("RR.png");
	rRook1 = Sprite::create("RR.png");
	//马
	rKnight = Sprite::create("RN.png");
	rKnight1 = Sprite::create("RN.png");
	//象
	rBishop = Sprite::create("RB.png");
	rBishop1 = Sprite::create("RB.png");
	//士
	rGuard = Sprite::create("RA.png");
	rGuard1 = Sprite::create("RA.png");
	//将
	rKing = Sprite::create("RK.png");
	//兵
	rPawn = Sprite::create("RP.png");
	rPawn1 = Sprite::create("RP.png");
	rPawn2 = Sprite::create("RP.png");
	rPawn3 = Sprite::create("RP.png");
	rPawn4 = Sprite::create("RP.png");
	//炮
	rCannon = Sprite::create("RC.png");
	rCannon1 = Sprite::create("RC.png");
	
	//黑方棋子
	//车
	bRook = Sprite::create("BR.png");
	bRook1 = Sprite::create("BR.png");
	//马
	bKnight = Sprite::create("BN.png");
	bKnight1 = Sprite::create("BN.png");
	//象
	bBishop = Sprite::create("BB.png");
	bBishop1 = Sprite::create("BB.png");
	//士
	bGuard = Sprite::create("BA.png");
	bGuard1 = Sprite::create("BA.png");
	//将
	bKing = Sprite::create("BK.png");
	//兵
	bPawn = Sprite::create("BP.png");
	bPawn1 = Sprite::create("BP.png");
	bPawn2 = Sprite::create("BP.png");
	bPawn3 = Sprite::create("BP.png");
	bPawn4 = Sprite::create("BP.png");
	//炮
	bCannon = Sprite::create("BC.png");
	bCannon1 = Sprite::create("BC.png");

	

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j ++)
		{
			stonePosition[i][j] = nullptr;
		}
	}
	//横纵轴反了，需要改
	//stonePosition数组记录了棋子在棋盘中的位置，当点击棋子走棋时，为了获得该位置的棋子类型
	stonePosition[0][0] = rRook;
	stonePosition[1][0] = rKnight;
	stonePosition[2][0] = rBishop;
	stonePosition[3][0] = rGuard;
	stonePosition[4][0] = rKing;
	stonePosition[5][0] = rGuard1;
	stonePosition[6][0] = rBishop1;
	stonePosition[7][0] = rKnight1;
	stonePosition[8][0] = rRook1;
	stonePosition[1][2] = rCannon;
	stonePosition[7][2] = rCannon1;
	stonePosition[0][3] = rPawn;
	stonePosition[2][3] = rPawn1;
	stonePosition[4][3] = rPawn2;
	stonePosition[6][3] = rPawn3;
	stonePosition[8][3] = rPawn4;

	stonePosition[0][9] = bRook;
	stonePosition[1][9] = bKnight;
	stonePosition[2][9] = bBishop;
	stonePosition[3][9] = bGuard;
	stonePosition[4][9] = bKing;
	stonePosition[5][9] = bGuard1;
	stonePosition[6][9] = bBishop1;
	stonePosition[7][9] = bKnight1;
	stonePosition[8][9] = bRook1;
	stonePosition[1][7] = bCannon;
	stonePosition[7][7] = bCannon1;
	stonePosition[0][6] = bPawn;
	stonePosition[2][6] = bPawn1;
	stonePosition[4][6] = bPawn2;
	stonePosition[6][6] = bPawn3;
	stonePosition[8][6] = bPawn4;
}

//走棋函数，mv为走法
void PlayScene::moveStone(int mv)
{
	//走法的起点，终点
	int sqSrc, sqDst;
	sqSrc = SRC(mv);  //获得走法起点
	sqDst = DST(mv);   //获得走法终点
	int start_x = sqSrc % 16 - 3;
	int start_y = 9 - (sqSrc / 16 - 3);
	int end_x = sqDst % 16 - 3;
	int end_y = 9 - (sqDst / 16 - 3);
	//log("start_x:%d  start_y:%d  end_x:%d  end_y:%d", start_x,start_y,end_x,end_y);
	Sprite* moveStone = stonePosition[start_x][start_y];
	//设置移动棋子的Z坐标为2，这样使移动棋子显示在所经过棋子的前段（例如炮吃子时，炮显示在隔着的棋子前段）
	moveStone->setPositionZ(2);
	Point endPoint;
	endPoint.x = origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * end_x + SQUARE_SIZE / 2;
	endPoint.y = origin.y + BOARD_EDGE + BOARD_POSITION_Y + SQUARE_SIZE * end_y + SQUARE_SIZE / 2;
	//算出移动距离
	float distance = sqrt((end_x - start_x) * (end_x - start_x) + (end_y - start_y) * (end_y - start_y));
	//记录走棋消耗的时间
	movetime = distance * 0.1;
	float delaytime = movetime + 0.1;
	
	//延时delaytime后播放走棋音效
	this->scheduleOnce(schedule_selector(PlayScene::playEffect), delaytime);
	
	//延迟delaytime秒之后执行update,update函数判断是够该电脑走棋，
	//延迟delaytime秒为了让一方棋子走完另一方再走
	this->scheduleOnce(schedule_selector(PlayScene::update), delaytime);
	
	//创建一个动作序列,该序列先移动棋子，再吃掉棋子
	auto moveTo = MoveTo::create(movetime, endPoint);
	auto hide = Hide::create();
	auto hideaction = TargetedAction::create(stonePosition[end_x][end_y], hide);
	auto seq = Sequence::create(moveTo, hideaction, NULL);
	
	//如果终点没有棋子，则执行动作序列，否则，仅执行走棋的动作
	if (stonePosition[end_x][end_y] != nullptr)
		moveStone->runAction(seq);
	else
		moveStone->runAction(moveTo);

	//走棋后，起点位置不再有棋子
	stonePosition[start_x][start_y] = nullptr;
	//更新历史走法表
	historyList[historyNum]._Set(mv, stonePosition[end_x][end_y]);
	historyNum++;
	//更改终点位置棋子
	stonePosition[end_x][end_y] = moveStone;
	//走完棋后，将棋子的Z坐标设置回1
	moveStone->setPositionZ(1);
}

//悔棋的走棋函数(去除了增加历史表操作),返回走棋需要的时间
float PlayScene::_moveStone(int mv)
{
	//走法的起点，终点
	int sqSrc, sqDst;
	sqSrc = SRC(mv);  //获得走法起点
	sqDst = DST(mv);   //获得走法终点
	int start_x = sqSrc % 16 - 3;
	int start_y = 9 - (sqSrc / 16 - 3);
	int end_x = sqDst % 16 - 3;
	int end_y = 9 - (sqDst / 16 - 3);
	Sprite* moveStone = stonePosition[start_x][start_y];
	Point endPoint;
	endPoint.x = origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * end_x + SQUARE_SIZE / 2;
	endPoint.y = origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * end_y + SQUARE_SIZE / 2;
	//算出移动距离
	float distance = sqrt((end_x - start_x) * (end_x - start_x) + (end_y - start_y) * (end_y - start_y));
	//记录走棋消耗的时间
	movetime = distance * 0.1;
	float delaytime = movetime;
	
	//this->scheduleOnce(schedule_selector(PlayScene::update), delaytime);
	Action* moveTo = MoveTo::create(movetime, endPoint);
	moveStone->runAction(moveTo);
	//走棋后，起点位置不再有棋子
	stonePosition[start_x][start_y] = nullptr;
	//如果终点有棋子，则吃掉                                         
	if (stonePosition[end_x][end_y] != nullptr)
		stonePosition[end_x][end_y]->setVisible(false);
	//更改终点位置棋子
	stonePosition[end_x][end_y] = moveStone;
	return delaytime;
}

//电脑走棋
void PlayScene::ResponseMove() {
	int vlRep;
	// 电脑走一步棋,botResponse函数调用AI，返回最佳走法（走法用一个数字表示）
	int mv = botResponse();
	int sqSrc = SRC(mv);  //获得走法起点
	int sqDst = DST(mv);   //获得走法终点
	int start_x = sqSrc % 16 - 3;
	int start_y = 9 - (sqSrc / 16 - 3);
	int end_x = sqDst % 16 - 3;
	int end_y = 9 - (sqDst / 16 - 3);
	
	//标识出走棋的起点
	DrawSelected(start_x, start_y);
	//走棋
	moveStone(mv);
	//标志出走棋的终点
	DrawSelected1(end_x, end_y);
	
	// 清除上一步棋的选择标记
	//DrawSquare(SRC(Xqwl.mvLast));
	//DrawSquare(DST(Xqwl.mvLast));
	// 把电脑走的棋标记出来
	//Xqwl.mvLast = Search.mvResult;
	//DrawSquare(SRC(Xqwl.mvLast), DRAW_SELECTED);
	//DrawSquare(DST(Xqwl.mvLast), DRAW_SELECTED);
	// 检查重复局面
	vlRep = pos.RepStatus(3);
	if (pos.IsMate()) {
		// 如果分出胜负，那么播放胜负的声音，并且弹出不带声音的提示框
		//PlayResWav(IDR_LOSS);
		//MessageBoxMute("请再接再厉！");
		//
		losePic->setVisible(true);
		log("输了");
		Xqwl.bGameOver = true;
	}
	else if (vlRep > 0) {
		vlRep = pos.RepValue(vlRep);
		// 注意："vlRep"是对玩家来说的分值
		//PlayResWav(vlRep < -WIN_VALUE ? IDR_LOSS : vlRep > WIN_VALUE ? IDR_WIN : IDR_DRAW);
		//MessageBoxMute(vlRep < -WIN_VALUE ? "长打作负，请不要气馁！" :
		//	vlRep > WIN_VALUE ? "电脑长打作负，祝贺你取得胜利！" : "双方不变作和，辛苦了！");
		Xqwl.bGameOver = true;
	}
	else if (pos.nMoveNum > 100) {
		//PlayResWav(IDR_DRAW);
		//MessageBoxMute("超过自然限着作和，辛苦了！");
		Xqwl.bGameOver = true;
	}
	else {
		// 如果没有分出胜负，那么播放将军、吃子或一般走子的声音
		//PlayResWav(pos.InCheck() ? IDR_CHECK2 : pos.Captured() ? IDR_CAPTURE2 : IDR_MOVE2);
		if (pos.Captured()) {
			//pos.SetIrrev();
		}
	}
}

//点击棋子的标志
void PlayScene::DrawSelected(int x, int y)
{
	selectedPic1->setVisible(false);
	selectedPic->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
}

//走棋的标志（点击棋盘，走到这里时）
void PlayScene::DrawSelected1(int x, int y)
{
	selectedPic1->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
	selectedPic1->setVisible(true);
}


bool PlayScene::init()
{
	//设置图片缩放比例
	Director::getInstance()->setContentScaleFactor(580.00 / 457.00);

	//预加载走棋音效
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_MUSIC);
	
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = CCDirector::getInstance()->getVisibleOrigin();
	
	//摆放桌子
	table = Sprite::create("zhuozi.jpg");
	table->setPosition(Vec2(origin.x, origin.y));
	table->setAnchorPoint(Vec2(0, 0));
	this->addChild(table, 0);
	
	//摆放棋盘
	chessBoard = Sprite::create("BOARD.png");
	chessBoard->setPosition(Vec2(origin.x + BOARD_POSITION_X, origin.y + BOARD_POSITION_Y));
	chessBoard->setAnchorPoint(Vec2(0, 0));//默认锚点为0.5，0.5
	this->addChild(chessBoard, 0);
	
	winPic = Sprite::create("win.jpg");
	winPic->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(winPic, 2);
	winPic->setVisible(false);

	losePic = Sprite::create("lose.jpg");
	losePic->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(losePic, 2);
	losePic->setVisible(false);

	//初始化表示选中棋子的图标
	selectedPic = Sprite::create("selected.png");
	this->addChild(selectedPic, 2);

	selectedPic1 = Sprite::create("selected.png");
	this->addChild(selectedPic1, 2);

	//初始化AI
	initAI();

	//初始化历史走法表（悔棋用）
	ClearHistory();

	//初始化棋子
	initStone();
	//摆放红方棋子
	//摆放车
	setStonePosition(0, 0, rRook);
	//摆放马
	setStonePosition(1, 0, rKnight);
	//摆放象
	setStonePosition(2, 0, rBishop);
	//摆放士
	setStonePosition(3, 0, rGuard);
	//摆放将
	setStonePosition(4, 0, rKing);
	//摆放士
	setStonePosition(5, 0, rGuard1);
	//摆放象
	setStonePosition(6, 0, rBishop1);
	//摆放马
	setStonePosition(7, 0, rKnight1);
	//摆放车
	setStonePosition(8, 0, rRook1);
	//摆放兵
	setStonePosition(0, 3, rPawn);
	//摆放兵
	setStonePosition(2, 3, rPawn1);
	//摆放兵
	setStonePosition(4, 3, rPawn2);
	//摆放兵
	setStonePosition(6, 3, rPawn3);
	//摆放兵
	setStonePosition(8, 3, rPawn4);

	//摆放黑方棋子
	//摆放车
	setStonePosition(0, 9, bRook);
	//摆放马
	setStonePosition(1, 9, bKnight);
	//摆放象
	setStonePosition(2, 9, bBishop);
	//摆放士
	setStonePosition(3, 9, bGuard);
	//摆放将
	setStonePosition(4, 9, bKing);
	//摆放士
	setStonePosition(5, 9, bGuard1);
	//摆放象
	setStonePosition(6, 9, bBishop1);
	//摆放马
	setStonePosition(7, 9, bKnight1);
	//摆放车
	setStonePosition(8, 9, bRook1);
	//摆放兵
	setStonePosition(0, 6, bPawn);
	//摆放兵
	setStonePosition(2, 6, bPawn1);
	//摆放兵
	setStonePosition(4, 6, bPawn2);
	//摆放兵
	setStonePosition(6, 6, bPawn3);
	//摆放兵
	setStonePosition(8, 6, bPawn4);
	
	//炮放到最后摆放，为了吃棋子时，显示在隔着的棋子的前端
	//摆放炮
	setStonePosition(1, 7, bCannon);
	//摆放炮
	setStonePosition(7, 7, bCannon1);
	//摆放炮,
	setStonePosition(1, 2, rCannon);
	//摆放炮
	setStonePosition(7, 2, rCannon1);

	//允许接收触摸事件  
	this->setTouchEnabled(true);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	
	listener1->onTouchBegan = [=](Touch* touch, Event* event){
		//所点击格子的横纵坐标（从0开始）
		int x;
		int y;
		Point touchPoint = Director::getInstance()->convertToUI(touch->getLocationInView());
		if ((int)(touchPoint.x - BOARD_POSITION_X - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) <= 50)
		{
			int ix = (touchPoint.x - BOARD_POSITION_X - BOARD_EDGE) / SQUARE_SIZE;
			x = ix - 1;
		}
		else if ((int)(touchPoint.x - BOARD_POSITION_X - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) > 50)
		{
			int ix1 = (touchPoint.x - BOARD_POSITION_X - BOARD_EDGE) / SQUARE_SIZE;
			x = ix1;
		}

		if ((int)(touchPoint.y - BOARD_POSITION_Y - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) <= 50)
		{
			int iy = (touchPoint.y - BOARD_POSITION_Y - BOARD_EDGE) / SQUARE_SIZE;
			y = iy - 1;
		}
		else if ((int)(touchPoint.y - BOARD_POSITION_Y - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) > 50)
		{
			int iy1 = (touchPoint.y - BOARD_POSITION_Y - BOARD_EDGE) / SQUARE_SIZE;
			y = iy1;
		}
		y = 9 - y;
		//所选格子转化成一维数组号
		int sq = 51 + x + y * 16;
		//pc为所选子，mv为走棋
		int pc, mv, vlRep;
		sq = Xqwl.bFlipped ? SQUARE_FLIP(sq) : sq;
		pc = pos.ucpcSquares[sq];

		if ((pc & SIDE_TAG(pos.sdPlayer)) != 0) {
			// 如果点击自己的子，那么直接选中该子
			if (Xqwl.sqSelected != 0) {
				//DrawSquare(Xqwl.sqSelected);
				//画出选中图标
				DrawSelected(x, 9 - y);
				//Sprite* selectedPic = Sprite::create("selected.png");
				//selectedPic->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * (9 - y) + SQUARE_SIZE / 2));
				//this->addChild(selectedPic, 2);
			}
			Xqwl.sqSelected = sq;
			//DrawSquare(sq, DRAW_SELECTED);
			DrawSelected(x, 9 - y);
			//Sprite* selectedPic = Sprite::create("selected.png");
			//selectedPic->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * (9 - y) + SQUARE_SIZE / 2));
			//this->addChild(selectedPic, 2);
			if (Xqwl.mvLast != 0) {
				//DrawSquare(SRC(Xqwl.mvLast));
				//DrawSquare(DST(Xqwl.mvLast));
			}
			//PlayResWav(IDR_CLICK); // 播放点击的声音
		}
		else if (Xqwl.sqSelected != 0 && !Xqwl.bGameOver) {
			// 如果点击的不是自己的子，但有子选中了(一定是自己的子)，那么走这个子
			mv = MOVE(Xqwl.sqSelected, sq);
			if (pos.LegalMove(mv)) {
				if (pos.MakeMove(mv)) {
					moveStone(mv);
					Xqwl.mvLast = mv;
					//DrawSquare(Xqwl.sqSelected, DRAW_SELECTED);
					//DrawSquare(sq, DRAW_SELECTED);
					DrawSelected1(x, 9 - y);
					Xqwl.sqSelected = 0;
					// 检查重复局面
					vlRep = pos.RepStatus(3);
					if (pos.IsMate()) {
						// 如果分出胜负，那么播放胜负的声音，并且弹出不带声音的提示框
						//PlayResWav(IDR_WIN);
						//MessageBoxMute("祝贺你取得胜利！");
						winPic->setVisible(true);
						Xqwl.bGameOver = 1;
					}
					else if (vlRep > 0) {
						vlRep = pos.RepValue(vlRep);

						Xqwl.bGameOver = 1;
					}
					else if (pos.nMoveNum > 100) {
						//PlayResWav(IDR_DRAW);
						//MessageBoxMute("超过自然限着作和，辛苦了！");
						Xqwl.bGameOver = 1;
					}
					else {
						// 如果没有分出胜负，那么播放将军、吃子或一般走子的声音
						//PlayResWav(pos.InCheck() ? IDR_CHECK : pos.Captured() ? IDR_CAPTURE : IDR_MOVE);
						if (pos.Captured()) {
							//如果上一步吃了子，则清空历史表，不知道为什么这么做，所以注释掉了
							//如果有下面的语句，则吃子后悔棋会出错（为什么）
							//pos.SetIrrev();
						}
						//ResponseMove(); // 轮到电脑走棋
						isBot = true;
					}
				}
				else {
					//PlayResWav(IDR_ILLEGAL); // 播放被将军的声音
				}
			}
			// 如果根本就不符合走法(例如马不走日字)，那么程序不予理会
		}
	
		return true;
	};

	//添加悔棋按钮
	huiqiButton = CCMenuItemImage::create
		(
		"huiqi1.png",     //平时的图片
		"huiqi2.png",   //选中时的图片
		CC_CALLBACK_1(PlayScene::huiqiCall, this)//点击时执行的回调方法
		);
	
	//添加退出按钮
	exitButton = CCMenuItemImage::create
		(
		"tuichu1.png",     //平时的图片
		"tuichu2.png",   //选中时的图片
		CC_CALLBACK_1(PlayScene::exitCall, this)//点击时执行的回调方法
		);

	auto menu = Menu::create(huiqiButton, NULL);
	menu->setPosition(100, 80);
	this->addChild(menu, 3);

	auto menu1 = Menu::create(exitButton, NULL);
	menu1->setPosition(200, 80);
	this->addChild(menu1, 3);

	//将触摸监听添加到eventDispacher中去  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, rRook);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rKnight);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rBishop);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rGuard);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rKing);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rGuard1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rBishop1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rKnight1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rRook1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rCannon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rCannon1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rPawn);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rPawn1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rPawn2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rPawn3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), rPawn4);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bRook);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bKnight);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bBishop);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bGuard);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bKing);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bGuard1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bBishop1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bKnight1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bRook1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bCannon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bCannon1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bPawn);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bPawn1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bPawn2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bPawn3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), bPawn4);

	return true;
}

//悔棋的走棋函数,返回走棋动作需要的时间
float PlayScene::unmoveStone()
{
	//获得上一步的走法
	int mv = historyList[historyNum - 1].wmv;
	int sqSrc, sqDst, pc;
	sqSrc = SRC(mv);
	sqDst = DST(mv);
	//和mv相反的走法
	int _mv = sqDst + sqSrc * 256;
	float runtime = _moveStone(_mv);
	//获得终点的二维位置
	int x = sqDst % 16 - 3;
	int y = 9 - (sqDst / 16 - 3);
	//走这步前，终点的棋子
	Sprite* dstPiece = historyList[historyNum - 1].ucpcCaptured;
	if (dstPiece != nullptr) 
	{
		_setStonePosition(x, y, dstPiece);
		stonePosition[x][y] = dstPiece;
	}
	return runtime;
}

//悔棋
void retractMove()                          
{
	historyList[historyNum - 1]._Set(0, nullptr);
	historyNum--;
}

//将按钮设置为可以使用，该函数在scheduleOnce中调用。 
void PlayScene::setButtonTrue(float dt)
{
	huiqiButton->setEnabled(true);
}

void PlayScene::goBackOneStep(float dt)
{
	float delaytime = unmoveStone();
	pos.UndoMakeMove();
	retractMove();
	this->scheduleOnce(schedule_selector(PlayScene::setButtonTrue), delaytime);
}

//悔棋按钮的回调函数
void PlayScene::huiqiCall(Ref* pSender)
{
	//如果历史表记录的个数大于1，代表走了棋
	if (historyNum > 1)
	{
		//设置悔棋按钮为不可按（防止快速按两次悔棋出现的bug）
		huiqiButton->setEnabled(false);
		//悔棋回撤两步

		float delaytime = unmoveStone();
		pos.UndoMakeMove();
		retractMove();
		//延迟delaytime后再执行一次goBackOneStep,即第一步悔棋走完之后再走第二步
		this->scheduleOnce(schedule_selector(PlayScene::goBackOneStep), delaytime);
	} 
}  

//退出按钮调用的函数
void PlayScene::exitCall(Ref* pSender)
{
	Director::getInstance()->replaceScene(WelcomeScene::createScene());
}