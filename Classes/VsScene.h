#ifndef _VSSCENE_H_
#define _VSSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

class VsScene : public Layer
{
protected:
	Sprite* chessBoard;
	//红方子
	Sprite* rRook;//车
	Sprite* rRook1;//车
	Sprite* rKnight;//马
	Sprite* rKnight1;//马
	Sprite* rBishop;//象
	Sprite* rBishop1;//象
	Sprite* rKing;//将
	Sprite* rPawn;//兵
	Sprite* rPawn1;//兵
	Sprite* rPawn2;//兵
	Sprite* rPawn3;//兵
	Sprite* rPawn4;//兵
	Sprite* rGuard;//士
	Sprite* rGuard1;//士
	Sprite* rCannon;//炮
	Sprite* rCannon1;//炮
	//黑方子
	Sprite* bRook;//车
	Sprite* bRook1;//车
	Sprite* bKnight;//马
	Sprite* bKnight1;//马
	Sprite* bBishop;//象
	Sprite* bBishop1;//象
	Sprite* bKing;//将
	Sprite* bPawn;//兵
	Sprite* bPawn1;//兵
	Sprite* bPawn2;//兵
	Sprite* bPawn3;//兵
	Sprite* bPawn4;//兵
	Sprite* bGuard;//士
	Sprite* bGuard1;//士
	Sprite* bCannon;//炮
	Sprite* bCannon1;//炮
	//将军图片
	Sprite* killPic;
	//胜利图片
	Sprite* winPic;
	//失败图片
	Sprite* losePic;
	//各子所在棋盘位置
	Sprite* stonePosition[10][9];
public:
	static Scene* createScene();
	virtual bool init();
	void initStone();
	void moveStone(int mv);
	void ResponseMove();
	CREATE_FUNC(VsScene);
	//设置棋子的位置，x y 为坐标，左下角为0 0
	virtual void setStonePosition(int x, int y, Sprite* stone, char* picname);
};

#endif