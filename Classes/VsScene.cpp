#include "VsScene.h"
#include "AI.h"
//#include "AI1.h"
//#include "AI2.h"
#include <math.h>
using namespace cocos2d;

const int BOARD_EDGE = 8;
const int SQUARE_SIZE = 56;
const int BOARD_POSITION = 200;
Point origin1 = CCDirector::getInstance()->getVisibleOrigin();

Point StartPoint1;
Point endPoint1;
bool isSelected1 = false;
Sprite *selectedStone1;
Size visibleSize1;
//走棋时间
float movetime1;

Scene* VsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = VsScene::create();
	scene->addChild(layer);
	return scene;
}


void VsScene::setStonePosition(int x, int y, Sprite* stone, char* picname)
{
	Size visibleSize1 = Director::getInstance()->getVisibleSize();


	stone->setPosition(Vec2(origin1.x + BOARD_POSITION + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin1.y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
	//stone->setAnchorPoint(Vec2(0, 0));//默认锚点为0.5，0.5
	this->addChild(stone, 1);
}

//初始化棋子精灵
void VsScene::initStone()
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

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			stonePosition[i][j] = nullptr;
		}
	}
	stonePosition[0][0] = bRook;
	stonePosition[0][1] = bKnight;
	stonePosition[0][2] = bBishop;
	stonePosition[0][3] = bGuard;
	stonePosition[0][4] = bKing;
	stonePosition[0][5] = bGuard1;
	stonePosition[0][6] = bBishop1;
	stonePosition[0][7] = bKnight1;
	stonePosition[0][8] = bRook1;
	stonePosition[2][1] = bCannon;
	stonePosition[2][7] = bCannon1;
	stonePosition[3][0] = bPawn;
	stonePosition[3][2] = bPawn1;
	stonePosition[3][4] = bPawn2;
	stonePosition[3][6] = bPawn3;
	stonePosition[3][8] = bPawn4;

	stonePosition[9][0] = rRook;
	stonePosition[9][1] = rKnight;
	stonePosition[9][2] = rBishop;
	stonePosition[9][3] = rGuard;
	stonePosition[9][4] = rKing;
	stonePosition[9][5] = rGuard1;
	stonePosition[9][6] = rBishop1;
	stonePosition[9][7] = rKnight1;
	stonePosition[9][8] = rRook1;
	stonePosition[7][1] = rCannon;
	stonePosition[7][7] = rCannon1;
	stonePosition[6][0] = rPawn;
	stonePosition[6][2] = rPawn1;
	stonePosition[6][4] = rPawn2;
	stonePosition[6][6] = rPawn3;
	stonePosition[6][8] = rPawn4;
}


void VsScene::moveStone(int mv)
{
	//走法的起点，终点
	int sqSrc, sqDst;
	sqSrc = SRC(mv);  //获得走法起点
	sqDst = DST(mv);   //获得走法终点
	log("aaaaa: %d", sqDst);
	int start_x = sqSrc % 16 - 3;
	int start_y = sqSrc / 16 - 3;
	int end_x = sqDst % 16 - 3;
	int end_y = sqDst / 16 - 3;
	end_y = 9 - end_y;
	Sprite* moveStone = stonePosition[start_y][start_x];
	//log("QQQQQ: %d", stonePosition[start_y][start_x]);
	Point endPoint1;
	endPoint1.x = origin1.x + BOARD_POSITION + BOARD_EDGE + SQUARE_SIZE * end_x + SQUARE_SIZE / 2;
	endPoint1.y = origin1.y + BOARD_EDGE + SQUARE_SIZE * end_y + SQUARE_SIZE / 2;
	//log("endPositionX: %d  endPositionY: %d", end_x,end_y);
	//算出移动距离
	float distance = sqrt((end_x - start_x) * (end_x - start_x) + (9 - end_y - start_y) * (9 - end_y - start_y));
	log("distance:  %f", distance);
	//记录走棋消耗的时间
	movetime1 = distance * 0.1;
	Action* moveTo = MoveTo::create(movetime1, endPoint1);
	moveStone->runAction(moveTo);
	stonePosition[start_y][start_x] = nullptr;
	//如果终点有棋子，则吃掉
	if (stonePosition[9 - end_y][end_x] != nullptr)
		stonePosition[9 - end_y][end_x]->setVisible(false);
	stonePosition[9 - end_y][end_x] = moveStone;
}

bool VsScene::init()
{
	visibleSize1 = Director::getInstance()->getVisibleSize();
	Point origin1 = CCDirector::getInstance()->getVisibleOrigin();
	//摆放棋盘
	chessBoard = Sprite::create("BOARD.png");
	chessBoard->setPosition(Vec2(origin1.x + BOARD_POSITION, origin1.y));
	chessBoard->setAnchorPoint(Vec2(0, 0));//默认锚点为0.5，0.5
	this->addChild(chessBoard, 0);

	winPic = Sprite::create("win.jpg");
	winPic->setPosition(Vec2(visibleSize1.width / 2, visibleSize1.height / 2));
	this->addChild(winPic, 2);
	winPic->setVisible(false);

	losePic = Sprite::create("lose.jpg");
	losePic->setPosition(Vec2(visibleSize1.width / 2, visibleSize1.height / 2));
	this->addChild(losePic, 2);
	losePic->setVisible(false);

	Xqwl.bFlipped = false;
	Startup();

	//初始化棋子
	initStone();
	//摆放红方棋子
	//摆放车
	setStonePosition(0, 0, rRook, "RR.png");
	//摆放马
	setStonePosition(1, 0, rKnight, "RN.png");
	//摆放象
	setStonePosition(2, 0, rBishop, "RB.png");
	//摆放士
	setStonePosition(3, 0, rGuard, "RA.png");
	//摆放将
	setStonePosition(4, 0, rKing, "RK.png");
	//摆放士
	setStonePosition(5, 0, rGuard1, "RA.png");
	//摆放象
	setStonePosition(6, 0, rBishop1, "RB.png");
	//摆放马
	setStonePosition(7, 0, rKnight1, "RN.png");
	//摆放车
	setStonePosition(8, 0, rRook1, "RR.png");
	//摆放兵
	setStonePosition(0, 3, rPawn, "RP.png");
	//摆放兵
	setStonePosition(2, 3, rPawn1, "RP.png");
	//摆放兵
	setStonePosition(4, 3, rPawn2, "RP.png");
	//摆放兵
	setStonePosition(6, 3, rPawn3, "RP.png");
	//摆放兵
	setStonePosition(8, 3, rPawn4, "RP.png");
	//摆放炮
	setStonePosition(1, 2, rCannon, "RC.png");
	//摆放炮
	setStonePosition(7, 2, rCannon1, "RC.png");

	//摆放黑方棋子
	//摆放车
	setStonePosition(0, 9, bRook, "BR.png");
	//摆放马
	setStonePosition(1, 9, bKnight, "BN.png");
	//摆放象
	setStonePosition(2, 9, bBishop, "BB.png");
	//摆放士
	setStonePosition(3, 9, bGuard, "BA.png");
	//摆放将
	setStonePosition(4, 9, bKing, "BK.png");
	//摆放士
	setStonePosition(5, 9, bGuard1, "BA.png");
	//摆放象
	setStonePosition(6, 9, bBishop1, "BB.png");
	//摆放马
	setStonePosition(7, 9, bKnight1, "BN.png");
	//摆放车
	setStonePosition(8, 9, bRook1, "BR.png");
	//摆放兵
	setStonePosition(0, 6, bPawn, "BP.png");
	//摆放兵
	setStonePosition(2, 6, bPawn1, "BP.png");
	//摆放兵
	setStonePosition(4, 6, bPawn2, "BP.png");
	//摆放兵
	setStonePosition(6, 6, bPawn3, "BP.png");
	//摆放兵
	setStonePosition(8, 6, bPawn4, "BP.png");
	//摆放炮
	setStonePosition(1, 7, bCannon, "BC.png");
	//摆放炮
	setStonePosition(7, 7, bCannon1, "BC.png");

	//允许接收触摸事件  
	this->setTouchEnabled(true);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	/*
	listener1->onTouchBegan = [=](Touch* touch, Event* event){
	//所点击格子的横纵坐标（从0开始）
	log("aaaaaaaaaaa");
	int x;
	int y;
	Point touchPoint = Director::getInstance()->convertToUI(touch->getLocationInView());
	if ((int)(touchPoint.x - BOARD_POSITION - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) <= 50)
	{
	int ix = (touchPoint.x - BOARD_POSITION - BOARD_EDGE) / SQUARE_SIZE;
	x = ix - 1;
	}
	else if ((int)(touchPoint.x - BOARD_POSITION - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) > 50)
	{
	int ix1 = (touchPoint.x - BOARD_POSITION - BOARD_EDGE) / SQUARE_SIZE;
	x = ix1;
	}

	if ((int)(touchPoint.y - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) <= 50)
	{
	int iy = (touchPoint.y - BOARD_EDGE) / SQUARE_SIZE;
	y = iy - 1;
	}
	else if ((int)(touchPoint.y - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) > 50)
	{
	int iy1 = (touchPoint.y - BOARD_EDGE) / SQUARE_SIZE;
	y = iy1;
	}
	y = 9 - y;
	//所选格子转化成一维数组号
	int sq = 51 + x + y * 16;
	log("sq: %d", sq);
	int pc, mv;
	//Xqwl.hdc = GetDC(Xqwl.hWnd);
	//Xqwl.hdcTmp = CreateCompatibleDC(Xqwl.hdc);
	sq = Xqwl.bFlipped ? SQUARE_FLIP(sq) : sq;
	pc = pos.ucpcSquares[sq];

	if ((pc & SIDE_TAG(pos.sdPlayer)) != 0) {
	// 如果点击自己的子，那么直接选中该子
	log("选中自己的子");
	if (Xqwl.sqSelected != 0) {
	//DrawSquare(Xqwl.sqSelected);
	}
	Xqwl.sqSelected = sq;
	//DrawSquare(sq, DRAW_SELECTED);
	if (Xqwl.mvLast != 0) {
	//DrawSquare(SRC(Xqwl.mvLast));
	//DrawSquare(DST(Xqwl.mvLast));
	}
	//PlayResWav(IDR_CLICK); // 播放点击的声音
	}
	else if (Xqwl.sqSelected != 0) {
	// 如果点击的不是自己的子，但有子选中了(一定是自己的子)，那么走这个子
	log("点击的不是自己的子");
	mv = MOVE(Xqwl.sqSelected, sq);
	if (pos.LegalMove(mv)) {
	if (pos.MakeMove(mv)) {
	moveStone(mv);
	log("走棋了");
	Xqwl.mvLast = mv;
	//DrawSquare(Xqwl.sqSelected, DRAW_SELECTED);
	//DrawSquare(sq, DRAW_SELECTED);
	Xqwl.sqSelected = 0;
	if (pos.IsMate()) {
	// 如果分出胜负，那么播放胜负的声音，并且弹出不带声音的提示框
	//PlayResWav(IDR_WIN);
	//MessageBoxMute("祝贺你取得胜利！");
	}
	else {
	// 如果没有分出胜负，那么播放将军、吃子或一般走子的声音
	//PlayResWav(pos.Checked() ? IDR_CHECK : pc != 0 ? IDR_CAPTURE : IDR_MOVE);
	}
	}
	else {
	//PlayResWav(IDR_ILLEGAL); // 播放被将军的声音
	}
	}
	// 如果根本就不符合走法(例如马不走日字)，那么程序不予理会
	}
	log("test: %d", pos.ucpcSquares[195]);
	return true;
	};
	*/

	listener1->onTouchBegan = [=](Touch* touch, Event* event){
		//所点击格子的横纵坐标（从0开始）
		int x;
		int y;
		Point touchPoint = Director::getInstance()->convertToUI(touch->getLocationInView());
		if ((int)(touchPoint.x - BOARD_POSITION - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) <= 50)
		{
			int ix = (touchPoint.x - BOARD_POSITION - BOARD_EDGE) / SQUARE_SIZE;
			x = ix - 1;
		}
		else if ((int)(touchPoint.x - BOARD_POSITION - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) > 50)
		{
			int ix1 = (touchPoint.x - BOARD_POSITION - BOARD_EDGE) / SQUARE_SIZE;
			x = ix1;
		}

		if ((int)(touchPoint.y - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) <= 50)
		{
			int iy = (touchPoint.y - BOARD_EDGE) / SQUARE_SIZE;
			y = iy - 1;
		}
		else if ((int)(touchPoint.y - BOARD_EDGE) * 100 % (SQUARE_SIZE * 100) > 50)
		{
			int iy1 = (touchPoint.y - BOARD_EDGE) / SQUARE_SIZE;
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
			}
			Xqwl.sqSelected = sq;
			//DrawSquare(sq, DRAW_SELECTED);
			if (Xqwl.mvLast != 0) {
				//DrawSquare(SRC(Xqwl.mvLast));
				//DrawSquare(DST(Xqwl.mvLast));
			}
			//PlayResWav(IDR_CLICK); // 播放点击的声音
		}
		else if (Xqwl.sqSelected != 0) {
			// 如果点击的不是自己的子，但有子选中了(一定是自己的子)，那么走这个子
			mv = MOVE(Xqwl.sqSelected, sq);
			if (pos.LegalMove(mv)) {
				if (pos.MakeMove(mv)) {
					moveStone(mv);
					Xqwl.mvLast = mv;
					//DrawSquare(Xqwl.sqSelected, DRAW_SELECTED);
					//DrawSquare(sq, DRAW_SELECTED);
					Xqwl.sqSelected = 0;
					if (pos.IsMate()) {
						// 如果分出胜负，那么播放胜负的声音，并且弹出不带声音的提示框
						//PlayResWav(IDR_WIN);
						//MessageBoxMute("祝贺你取得胜利！");
						winPic->setVisible(true);
					}
					else {
						//PlayResWav(IDR_ILLEGAL); // 播放被将军的声音
					}
				}
				// 如果根本就不符合走法(例如马不走日字)，那么程序不予理会
			}

			return true;
		}
		return true;
	};

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
