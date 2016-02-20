#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

class PlayScene : public Layer
{
protected:
	Sprite* chessBoard;
	Sprite* table;
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
	//��������ͼ��
	Sprite* selectedPic;
	Sprite* selectedPic1;
	//������������λ��
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
	//�������ӵ�λ�ã�x y Ϊ���꣬���½�Ϊ0 0
	virtual void setStonePosition(int x, int y, Sprite* stone);
	virtual void _setStonePosition(int x, int y, Sprite* stone);
	void update(float delta);
	void huiqiCall(Ref* pSender);
	void exitCall(Ref* pSender);
	//����������Ч����Ϊ��schedule�е��ã����Բ���Ϊfloat
	void playEffect(float dt);
	//�������ӱ�Ż�����ӵľ���
	Sprite* getStone(int num);
	void setButtonTrue(float dt);
	void goBackOneStep(float dt);
	void DrawSelected(int x, int y);
	void DrawSelected1(int x, int y);
};

#endif