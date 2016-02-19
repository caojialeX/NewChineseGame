#ifndef _VSSCENE_H_
#define _VSSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

class VsScene : public Layer
{
protected:
	Sprite* chessBoard;
	//�췽��
	Sprite* rRook;//��
	Sprite* rRook1;//��
	Sprite* rKnight;//��
	Sprite* rKnight1;//��
	Sprite* rBishop;//��
	Sprite* rBishop1;//��
	Sprite* rKing;//��
	Sprite* rPawn;//��
	Sprite* rPawn1;//��
	Sprite* rPawn2;//��
	Sprite* rPawn3;//��
	Sprite* rPawn4;//��
	Sprite* rGuard;//ʿ
	Sprite* rGuard1;//ʿ
	Sprite* rCannon;//��
	Sprite* rCannon1;//��
	//�ڷ���
	Sprite* bRook;//��
	Sprite* bRook1;//��
	Sprite* bKnight;//��
	Sprite* bKnight1;//��
	Sprite* bBishop;//��
	Sprite* bBishop1;//��
	Sprite* bKing;//��
	Sprite* bPawn;//��
	Sprite* bPawn1;//��
	Sprite* bPawn2;//��
	Sprite* bPawn3;//��
	Sprite* bPawn4;//��
	Sprite* bGuard;//ʿ
	Sprite* bGuard1;//ʿ
	Sprite* bCannon;//��
	Sprite* bCannon1;//��
	//����ͼƬ
	Sprite* killPic;
	//ʤ��ͼƬ
	Sprite* winPic;
	//ʧ��ͼƬ
	Sprite* losePic;
	//������������λ��
	Sprite* stonePosition[10][9];
public:
	static Scene* createScene();
	virtual bool init();
	void initStone();
	void moveStone(int mv);
	void ResponseMove();
	CREATE_FUNC(VsScene);
	//�������ӵ�λ�ã�x y Ϊ���꣬���½�Ϊ0 0
	virtual void setStonePosition(int x, int y, Sprite* stone, char* picname);
};

#endif