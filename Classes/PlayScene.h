#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

class PlayScene : public Layer
{
protected:
	Sprite* chessBoard;
	Sprite* table;
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
	//棋子锁定图标
	Sprite* selectedPic;
	Sprite* selectedPic1;
	//各子所在棋盘位置
	Sprite* stonePosition[9][10];
public:
	static Scene* createScene();
	virtual bool init();
	void initStone();
	void moveStone(int mv);
	float _moveStone(int mv);
	float unmoveStone();
	void ResponseMove();
	CREATE_FUNC(PlayScene);
	//设置棋子的位置，x y 为坐标，左下角为0 0
	virtual void setStonePosition(int x, int y, Sprite* stone);
	virtual void _setStonePosition(int x, int y, Sprite* stone);
	void update(float delta);
	void huiqiCall(Ref* pSender);
	void exitCall(Ref* pSender);
	//播放走棋音效，因为在schedule中调用，所以参数为float
	void playEffect(float dt);
	//根据棋子编号获得棋子的精灵
	Sprite* getStone(int num);
	void setButtonTrue(float dt);
	void goBackOneStep(float dt);
	void DrawSelected(int x, int y);
	void DrawSelected1(int x, int y);
};

#endif