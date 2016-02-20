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
//�Ƿ��ֵ���������
bool isBot = false;
//��¼����ƶ���������Ҫ��ʱ��
float movetime = 0;
Size visibleSize;
int historyNum = 0;

//��ʷ�߷���Ϣ�������ã�
struct HistoryMove
{
	WORD wmv;               //��һ���߷�
	Sprite* ucpcCaptured;     //��һ���յ������

	void _Set(int mv, Sprite* pcCaptured)
	{
		wmv = mv;
		ucpcCaptured = pcCaptured;
	}
}historyList[MAX_HISTORY];

void ClearHistory()             //�����ʷ�߷������壩��Ϣ
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

//schedule�е��ã�ÿ��ʱ������ִ��һ�Σ������߼�
void PlayScene::update(float dt)
{
	if (isBot == true)
	{
		ResponseMove(); // �ֵ���������
		isBot = false;
	}
}

//����������Ч����scheduleOnce�е��ã�Ϊ����ʱ���ţ�������������ٲ��ţ�
void PlayScene::playEffect(float dt)
{
	//����������Ч
	SimpleAudioEngine::getInstance()->playEffect(EFFECT_MUSIC);
}

//�����Ӱڷŵ������ϵĶ�Ӧ��λ���ϣ����½�����Ϊ��0��0��,Ĭ�ϲ��Ϊ1�����Խ�ߣ���ʾԽ��ǰ
void PlayScene::setStonePosition(int x, int y, Sprite* stone)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	stone->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
	//stone->setAnchorPoint(Vec2(0, 0));//Ĭ��ê��Ϊ0.5��0.5
	this->addChild(stone, 1);
}

//���˸�setVisible�������˷����ڻ���ĺ����л��õ�
void PlayScene::_setStonePosition(int x, int y, Sprite* stone)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	stone->setVisible(true);
	stone->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), stone);

	//stone->setAnchorPoint(Vec2(0, 0));//Ĭ��ê��Ϊ0.5��0.5
	//this->addChild(stone, 1);
}

//��ʼ�����Ӿ���
void PlayScene::initStone()
{
	//�췽����
	//��
	rRook = Sprite::create("RR.png");
	rRook1 = Sprite::create("RR.png");
	//��
	rKnight = Sprite::create("RN.png");
	rKnight1 = Sprite::create("RN.png");
	//��
	rBishop = Sprite::create("RB.png");
	rBishop1 = Sprite::create("RB.png");
	//ʿ
	rGuard = Sprite::create("RA.png");
	rGuard1 = Sprite::create("RA.png");
	//��
	rKing = Sprite::create("RK.png");
	//��
	rPawn = Sprite::create("RP.png");
	rPawn1 = Sprite::create("RP.png");
	rPawn2 = Sprite::create("RP.png");
	rPawn3 = Sprite::create("RP.png");
	rPawn4 = Sprite::create("RP.png");
	//��
	rCannon = Sprite::create("RC.png");
	rCannon1 = Sprite::create("RC.png");
	
	//�ڷ�����
	//��
	bRook = Sprite::create("BR.png");
	bRook1 = Sprite::create("BR.png");
	//��
	bKnight = Sprite::create("BN.png");
	bKnight1 = Sprite::create("BN.png");
	//��
	bBishop = Sprite::create("BB.png");
	bBishop1 = Sprite::create("BB.png");
	//ʿ
	bGuard = Sprite::create("BA.png");
	bGuard1 = Sprite::create("BA.png");
	//��
	bKing = Sprite::create("BK.png");
	//��
	bPawn = Sprite::create("BP.png");
	bPawn1 = Sprite::create("BP.png");
	bPawn2 = Sprite::create("BP.png");
	bPawn3 = Sprite::create("BP.png");
	bPawn4 = Sprite::create("BP.png");
	//��
	bCannon = Sprite::create("BC.png");
	bCannon1 = Sprite::create("BC.png");

	

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j ++)
		{
			stonePosition[i][j] = nullptr;
		}
	}
	//�����ᷴ�ˣ���Ҫ��
	//stonePosition�����¼�������������е�λ�ã��������������ʱ��Ϊ�˻�ø�λ�õ���������
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

//���庯����mvΪ�߷�
void PlayScene::moveStone(int mv)
{
	//�߷�����㣬�յ�
	int sqSrc, sqDst;
	sqSrc = SRC(mv);  //����߷����
	sqDst = DST(mv);   //����߷��յ�
	int start_x = sqSrc % 16 - 3;
	int start_y = 9 - (sqSrc / 16 - 3);
	int end_x = sqDst % 16 - 3;
	int end_y = 9 - (sqDst / 16 - 3);
	//log("start_x:%d  start_y:%d  end_x:%d  end_y:%d", start_x,start_y,end_x,end_y);
	Sprite* moveStone = stonePosition[start_x][start_y];
	//�����ƶ����ӵ�Z����Ϊ2������ʹ�ƶ�������ʾ�����������ӵ�ǰ�Σ������ڳ���ʱ������ʾ�ڸ��ŵ�����ǰ�Σ�
	moveStone->setPositionZ(2);
	Point endPoint;
	endPoint.x = origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * end_x + SQUARE_SIZE / 2;
	endPoint.y = origin.y + BOARD_EDGE + BOARD_POSITION_Y + SQUARE_SIZE * end_y + SQUARE_SIZE / 2;
	//����ƶ�����
	float distance = sqrt((end_x - start_x) * (end_x - start_x) + (end_y - start_y) * (end_y - start_y));
	//��¼�������ĵ�ʱ��
	movetime = distance * 0.1;
	float delaytime = movetime + 0.1;
	
	//��ʱdelaytime�󲥷�������Ч
	this->scheduleOnce(schedule_selector(PlayScene::playEffect), delaytime);
	
	//�ӳ�delaytime��֮��ִ��update,update�����ж��ǹ��õ������壬
	//�ӳ�delaytime��Ϊ����һ������������һ������
	this->scheduleOnce(schedule_selector(PlayScene::update), delaytime);
	
	//����һ����������,���������ƶ����ӣ��ٳԵ�����
	auto moveTo = MoveTo::create(movetime, endPoint);
	auto hide = Hide::create();
	auto hideaction = TargetedAction::create(stonePosition[end_x][end_y], hide);
	auto seq = Sequence::create(moveTo, hideaction, NULL);
	
	//����յ�û�����ӣ���ִ�ж������У����򣬽�ִ������Ķ���
	if (stonePosition[end_x][end_y] != nullptr)
		moveStone->runAction(seq);
	else
		moveStone->runAction(moveTo);

	//��������λ�ò���������
	stonePosition[start_x][start_y] = nullptr;
	//������ʷ�߷���
	historyList[historyNum]._Set(mv, stonePosition[end_x][end_y]);
	historyNum++;
	//�����յ�λ������
	stonePosition[end_x][end_y] = moveStone;
	//������󣬽����ӵ�Z�������û�1
	moveStone->setPositionZ(1);
}

//��������庯��(ȥ����������ʷ�����),����������Ҫ��ʱ��
float PlayScene::_moveStone(int mv)
{
	//�߷�����㣬�յ�
	int sqSrc, sqDst;
	sqSrc = SRC(mv);  //����߷����
	sqDst = DST(mv);   //����߷��յ�
	int start_x = sqSrc % 16 - 3;
	int start_y = 9 - (sqSrc / 16 - 3);
	int end_x = sqDst % 16 - 3;
	int end_y = 9 - (sqDst / 16 - 3);
	Sprite* moveStone = stonePosition[start_x][start_y];
	Point endPoint;
	endPoint.x = origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * end_x + SQUARE_SIZE / 2;
	endPoint.y = origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * end_y + SQUARE_SIZE / 2;
	//����ƶ�����
	float distance = sqrt((end_x - start_x) * (end_x - start_x) + (end_y - start_y) * (end_y - start_y));
	//��¼�������ĵ�ʱ��
	movetime = distance * 0.1;
	float delaytime = movetime;
	
	//this->scheduleOnce(schedule_selector(PlayScene::update), delaytime);
	Action* moveTo = MoveTo::create(movetime, endPoint);
	moveStone->runAction(moveTo);
	//��������λ�ò���������
	stonePosition[start_x][start_y] = nullptr;
	//����յ������ӣ���Ե�                                         
	if (stonePosition[end_x][end_y] != nullptr)
		stonePosition[end_x][end_y]->setVisible(false);
	//�����յ�λ������
	stonePosition[end_x][end_y] = moveStone;
	return delaytime;
}

//��������
void PlayScene::ResponseMove() {
	int vlRep;
	// ������һ����,botResponse��������AI����������߷����߷���һ�����ֱ�ʾ��
	int mv = botResponse();
	int sqSrc = SRC(mv);  //����߷����
	int sqDst = DST(mv);   //����߷��յ�
	int start_x = sqSrc % 16 - 3;
	int start_y = 9 - (sqSrc / 16 - 3);
	int end_x = sqDst % 16 - 3;
	int end_y = 9 - (sqDst / 16 - 3);
	
	//��ʶ����������
	DrawSelected(start_x, start_y);
	//����
	moveStone(mv);
	//��־��������յ�
	DrawSelected1(end_x, end_y);
	
	// �����һ�����ѡ����
	//DrawSquare(SRC(Xqwl.mvLast));
	//DrawSquare(DST(Xqwl.mvLast));
	// �ѵ����ߵ����ǳ���
	//Xqwl.mvLast = Search.mvResult;
	//DrawSquare(SRC(Xqwl.mvLast), DRAW_SELECTED);
	//DrawSquare(DST(Xqwl.mvLast), DRAW_SELECTED);
	// ����ظ�����
	vlRep = pos.RepStatus(3);
	if (pos.IsMate()) {
		// ����ֳ�ʤ������ô����ʤ�������������ҵ���������������ʾ��
		//PlayResWav(IDR_LOSS);
		//MessageBoxMute("���ٽ�������");
		//
		losePic->setVisible(true);
		log("����");
		Xqwl.bGameOver = true;
	}
	else if (vlRep > 0) {
		vlRep = pos.RepValue(vlRep);
		// ע�⣺"vlRep"�Ƕ������˵�ķ�ֵ
		//PlayResWav(vlRep < -WIN_VALUE ? IDR_LOSS : vlRep > WIN_VALUE ? IDR_WIN : IDR_DRAW);
		//MessageBoxMute(vlRep < -WIN_VALUE ? "�����������벻Ҫ���٣�" :
		//	vlRep > WIN_VALUE ? "���Գ���������ף����ȡ��ʤ����" : "˫���������ͣ������ˣ�");
		Xqwl.bGameOver = true;
	}
	else if (pos.nMoveNum > 100) {
		//PlayResWav(IDR_DRAW);
		//MessageBoxMute("������Ȼ�������ͣ������ˣ�");
		Xqwl.bGameOver = true;
	}
	else {
		// ���û�зֳ�ʤ������ô���Ž��������ӻ�һ�����ӵ�����
		//PlayResWav(pos.InCheck() ? IDR_CHECK2 : pos.Captured() ? IDR_CAPTURE2 : IDR_MOVE2);
		if (pos.Captured()) {
			//pos.SetIrrev();
		}
	}
}

//������ӵı�־
void PlayScene::DrawSelected(int x, int y)
{
	selectedPic1->setVisible(false);
	selectedPic->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
}

//����ı�־��������̣��ߵ�����ʱ��
void PlayScene::DrawSelected1(int x, int y)
{
	selectedPic1->setPosition(Vec2(origin.x + BOARD_POSITION_X + BOARD_EDGE + SQUARE_SIZE * x + SQUARE_SIZE / 2, origin.y + BOARD_POSITION_Y + BOARD_EDGE + SQUARE_SIZE * y + SQUARE_SIZE / 2));
	selectedPic1->setVisible(true);
}


bool PlayScene::init()
{
	//����ͼƬ���ű���
	Director::getInstance()->setContentScaleFactor(580.00 / 457.00);

	//Ԥ����������Ч
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_MUSIC);
	
	visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = CCDirector::getInstance()->getVisibleOrigin();
	
	//�ڷ�����
	table = Sprite::create("zhuozi.jpg");
	table->setPosition(Vec2(origin.x, origin.y));
	table->setAnchorPoint(Vec2(0, 0));
	this->addChild(table, 0);
	
	//�ڷ�����
	chessBoard = Sprite::create("BOARD.png");
	chessBoard->setPosition(Vec2(origin.x + BOARD_POSITION_X, origin.y + BOARD_POSITION_Y));
	chessBoard->setAnchorPoint(Vec2(0, 0));//Ĭ��ê��Ϊ0.5��0.5
	this->addChild(chessBoard, 0);
	
	winPic = Sprite::create("win.jpg");
	winPic->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(winPic, 2);
	winPic->setVisible(false);

	losePic = Sprite::create("lose.jpg");
	losePic->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(losePic, 2);
	losePic->setVisible(false);

	//��ʼ����ʾѡ�����ӵ�ͼ��
	selectedPic = Sprite::create("selected.png");
	this->addChild(selectedPic, 2);

	selectedPic1 = Sprite::create("selected.png");
	this->addChild(selectedPic1, 2);

	//��ʼ��AI
	initAI();

	//��ʼ����ʷ�߷��������ã�
	ClearHistory();

	//��ʼ������
	initStone();
	//�ڷź췽����
	//�ڷų�
	setStonePosition(0, 0, rRook);
	//�ڷ���
	setStonePosition(1, 0, rKnight);
	//�ڷ���
	setStonePosition(2, 0, rBishop);
	//�ڷ�ʿ
	setStonePosition(3, 0, rGuard);
	//�ڷŽ�
	setStonePosition(4, 0, rKing);
	//�ڷ�ʿ
	setStonePosition(5, 0, rGuard1);
	//�ڷ���
	setStonePosition(6, 0, rBishop1);
	//�ڷ���
	setStonePosition(7, 0, rKnight1);
	//�ڷų�
	setStonePosition(8, 0, rRook1);
	//�ڷű�
	setStonePosition(0, 3, rPawn);
	//�ڷű�
	setStonePosition(2, 3, rPawn1);
	//�ڷű�
	setStonePosition(4, 3, rPawn2);
	//�ڷű�
	setStonePosition(6, 3, rPawn3);
	//�ڷű�
	setStonePosition(8, 3, rPawn4);

	//�ڷźڷ�����
	//�ڷų�
	setStonePosition(0, 9, bRook);
	//�ڷ���
	setStonePosition(1, 9, bKnight);
	//�ڷ���
	setStonePosition(2, 9, bBishop);
	//�ڷ�ʿ
	setStonePosition(3, 9, bGuard);
	//�ڷŽ�
	setStonePosition(4, 9, bKing);
	//�ڷ�ʿ
	setStonePosition(5, 9, bGuard1);
	//�ڷ���
	setStonePosition(6, 9, bBishop1);
	//�ڷ���
	setStonePosition(7, 9, bKnight1);
	//�ڷų�
	setStonePosition(8, 9, bRook1);
	//�ڷű�
	setStonePosition(0, 6, bPawn);
	//�ڷű�
	setStonePosition(2, 6, bPawn1);
	//�ڷű�
	setStonePosition(4, 6, bPawn2);
	//�ڷű�
	setStonePosition(6, 6, bPawn3);
	//�ڷű�
	setStonePosition(8, 6, bPawn4);
	
	//�ڷŵ����ڷţ�Ϊ�˳�����ʱ����ʾ�ڸ��ŵ����ӵ�ǰ��
	//�ڷ���
	setStonePosition(1, 7, bCannon);
	//�ڷ���
	setStonePosition(7, 7, bCannon1);
	//�ڷ���,
	setStonePosition(1, 2, rCannon);
	//�ڷ���
	setStonePosition(7, 2, rCannon1);

	//������մ����¼�  
	this->setTouchEnabled(true);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	
	listener1->onTouchBegan = [=](Touch* touch, Event* event){
		//��������ӵĺ������꣨��0��ʼ��
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
		//��ѡ����ת����һά�����
		int sq = 51 + x + y * 16;
		//pcΪ��ѡ�ӣ�mvΪ����
		int pc, mv, vlRep;
		sq = Xqwl.bFlipped ? SQUARE_FLIP(sq) : sq;
		pc = pos.ucpcSquares[sq];

		if ((pc & SIDE_TAG(pos.sdPlayer)) != 0) {
			// �������Լ����ӣ���ôֱ��ѡ�и���
			if (Xqwl.sqSelected != 0) {
				//DrawSquare(Xqwl.sqSelected);
				//����ѡ��ͼ��
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
			//PlayResWav(IDR_CLICK); // ���ŵ��������
		}
		else if (Xqwl.sqSelected != 0 && !Xqwl.bGameOver) {
			// �������Ĳ����Լ����ӣ�������ѡ����(һ�����Լ�����)����ô�������
			mv = MOVE(Xqwl.sqSelected, sq);
			if (pos.LegalMove(mv)) {
				if (pos.MakeMove(mv)) {
					moveStone(mv);
					Xqwl.mvLast = mv;
					//DrawSquare(Xqwl.sqSelected, DRAW_SELECTED);
					//DrawSquare(sq, DRAW_SELECTED);
					DrawSelected1(x, 9 - y);
					Xqwl.sqSelected = 0;
					// ����ظ�����
					vlRep = pos.RepStatus(3);
					if (pos.IsMate()) {
						// ����ֳ�ʤ������ô����ʤ�������������ҵ���������������ʾ��
						//PlayResWav(IDR_WIN);
						//MessageBoxMute("ף����ȡ��ʤ����");
						winPic->setVisible(true);
						Xqwl.bGameOver = 1;
					}
					else if (vlRep > 0) {
						vlRep = pos.RepValue(vlRep);

						Xqwl.bGameOver = 1;
					}
					else if (pos.nMoveNum > 100) {
						//PlayResWav(IDR_DRAW);
						//MessageBoxMute("������Ȼ�������ͣ������ˣ�");
						Xqwl.bGameOver = 1;
					}
					else {
						// ���û�зֳ�ʤ������ô���Ž��������ӻ�һ�����ӵ�����
						//PlayResWav(pos.InCheck() ? IDR_CHECK : pos.Captured() ? IDR_CAPTURE : IDR_MOVE);
						if (pos.Captured()) {
							//�����һ�������ӣ��������ʷ����֪��Ϊʲô��ô��������ע�͵���
							//������������䣬����Ӻ��������Ϊʲô��
							//pos.SetIrrev();
						}
						//ResponseMove(); // �ֵ���������
						isBot = true;
					}
				}
				else {
					//PlayResWav(IDR_ILLEGAL); // ���ű�����������
				}
			}
			// ��������Ͳ������߷�(������������)����ô���������
		}
	
		return true;
	};

	//��ӻ��尴ť
	huiqiButton = CCMenuItemImage::create
		(
		"huiqi1.png",     //ƽʱ��ͼƬ
		"huiqi2.png",   //ѡ��ʱ��ͼƬ
		CC_CALLBACK_1(PlayScene::huiqiCall, this)//���ʱִ�еĻص�����
		);
	
	//����˳���ť
	exitButton = CCMenuItemImage::create
		(
		"tuichu1.png",     //ƽʱ��ͼƬ
		"tuichu2.png",   //ѡ��ʱ��ͼƬ
		CC_CALLBACK_1(PlayScene::exitCall, this)//���ʱִ�еĻص�����
		);

	auto menu = Menu::create(huiqiButton, NULL);
	menu->setPosition(100, 80);
	this->addChild(menu, 3);

	auto menu1 = Menu::create(exitButton, NULL);
	menu1->setPosition(200, 80);
	this->addChild(menu1, 3);

	//������������ӵ�eventDispacher��ȥ  
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

//��������庯��,�������嶯����Ҫ��ʱ��
float PlayScene::unmoveStone()
{
	//�����һ�����߷�
	int mv = historyList[historyNum - 1].wmv;
	int sqSrc, sqDst, pc;
	sqSrc = SRC(mv);
	sqDst = DST(mv);
	//��mv�෴���߷�
	int _mv = sqDst + sqSrc * 256;
	float runtime = _moveStone(_mv);
	//����յ�Ķ�άλ��
	int x = sqDst % 16 - 3;
	int y = 9 - (sqDst / 16 - 3);
	//���ⲽǰ���յ������
	Sprite* dstPiece = historyList[historyNum - 1].ucpcCaptured;
	if (dstPiece != nullptr) 
	{
		_setStonePosition(x, y, dstPiece);
		stonePosition[x][y] = dstPiece;
	}
	return runtime;
}

//����
void retractMove()                          
{
	historyList[historyNum - 1]._Set(0, nullptr);
	historyNum--;
}

//����ť����Ϊ����ʹ�ã��ú�����scheduleOnce�е��á� 
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

//���尴ť�Ļص�����
void PlayScene::huiqiCall(Ref* pSender)
{
	//�����ʷ���¼�ĸ�������1������������
	if (historyNum > 1)
	{
		//���û��尴ťΪ���ɰ�����ֹ���ٰ����λ�����ֵ�bug��
		huiqiButton->setEnabled(false);
		//����س�����

		float delaytime = unmoveStone();
		pos.UndoMakeMove();
		retractMove();
		//�ӳ�delaytime����ִ��һ��goBackOneStep,����һ����������֮�����ߵڶ���
		this->scheduleOnce(schedule_selector(PlayScene::goBackOneStep), delaytime);
	} 
}  

//�˳���ť���õĺ���
void PlayScene::exitCall(Ref* pSender)
{
	Director::getInstance()->replaceScene(WelcomeScene::createScene());
}