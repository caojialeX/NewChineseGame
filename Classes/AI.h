/*
��Ҷ��ĵ�AI
*/

// ���̷�Χ
const int RANK_TOP = 3;
const int RANK_BOTTOM = 12;
const int FILE_LEFT = 3;
const int FILE_RIGHT = 11;

// ���ӱ��
const int PIECE_KING = 0;
const int PIECE_ADVISOR = 1;
const int PIECE_BISHOP = 2;
const int PIECE_KNIGHT = 3;
const int PIECE_ROOK = 4;
const int PIECE_CANNON = 5;
const int PIECE_PAWN = 6;

// ��������
const int MAX_GEN_MOVES = 128; // ���������߷���

// �ж������Ƿ��������е�����
static const char ccInBoard[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// �ж������Ƿ��ھŹ�������
static const char ccInFort[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// �жϲ����Ƿ�����ض��߷������飬1=˧(��)��2=��(ʿ)��3=��(��)
static const char ccLegalSpan[512] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

// ���ݲ����ж����Ƿ����ȵ�����
static const char ccKnightPin[512] = {//��Ϊ���õ�256�����̣����Բ������Ϊ����255��Ϊ���������ģ���������256������������512��������
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, -16, 0, -16, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 16, 0, 16, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

// ˧(��)�Ĳ���
static const char ccKingDelta[4] = { -16, -1, 1, 16 };
// ��(ʿ)�Ĳ���
static const char ccAdvisorDelta[4] = { -17, -15, 15, 17 };
// ��Ĳ�������˧(��)�Ĳ�����Ϊ����
static const char ccKnightDelta[4][2] = { { -33, -31 }, { -18, 14 }, { -14, 18 }, { 31, 33 } };
// �������Ĳ���������(ʿ)�Ĳ�����Ϊ����
static const char ccKnightCheckDelta[4][2] = { { -33, -18 }, { -31, -14 }, { 14, 31 }, { 18, 33 } };

// ���̳�ʼ����
static const char cucpcStartup[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 20, 19, 18, 17, 16, 17, 18, 19, 20, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0,
	0, 0, 0, 22, 0, 22, 0, 22, 0, 22, 0, 22, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 14, 0, 14, 0, 14, 0, 14, 0, 14, 0, 0, 0, 0,
	0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 12, 11, 10, 9, 8, 9, 10, 11, 12, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// �ж������Ƿ���������
inline int IN_BOARD(int sq) {
	return ccInBoard[sq] != 0;
}

// �ж������Ƿ��ھŹ���
inline int IN_FORT(int sq) {
	return ccInFort[sq] != 0;
}

// ��ø��ӵĺ�����  //�������꣬�������궼��0��ʼ
inline int RANK_Y(int sq) {
	return sq >> 4;//����4λ���൱�ڳ���16
}

// ��ø��ӵ�������
inline int FILE_X(int sq) {
	return sq & 15;
}

// ����������ͺ������ø���
inline int COORD_XY(int x, int y) {
	return x + (y << 4);
}

// ��ת����  //��������ʱ���ڷ������еߵ�
inline int SQUARE_FLIP(int sq) {
	return 254 - sq;
}

// ������ˮƽ����
inline int FILE_FLIP(int x) {
	return 14 - x;
}

// �����괹ֱ����
inline int RANK_FLIP(int y) {
	return 15 - y;
}

// ����ˮƽ����
inline int MIRROR_SQUARE(int sq) {
	return COORD_XY(FILE_FLIP(FILE_X(sq)), RANK_Y(sq));
}

// ����ˮƽ����
inline int SQUARE_FORWARD(int sq, int sd) {
	return sq - 16 + (sd << 5);  //���ر���ǰ��һ�����λ��
}

// �߷��Ƿ����˧(��)�Ĳ���
inline int KING_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 1;
}

// �߷��Ƿ������(ʿ)�Ĳ���
inline int ADVISOR_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 2;
}

// �߷��Ƿ������(��)�Ĳ���
inline int BISHOP_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 3;
}

// ��(��)�۵�λ��  //�����յ����2
inline int BISHOP_PIN(int sqSrc, int sqDst) {
	return (sqSrc + sqDst) >> 1;
}

// ���ȵ�λ��
inline int KNIGHT_PIN(int sqSrc, int sqDst) {
	return sqSrc + ccKnightPin[sqDst - sqSrc + 256];
}

// �Ƿ�δ����//?
inline int HOME_HALF(int sq, int sd) {  //sqΪ�����ϵ�λ�ã�sd�����巽
	return (sq & 0x80) != (sd << 7);
}

// �Ƿ��ѹ���//?
inline int AWAY_HALF(int sq, int sd) {
	return (sq & 0x80) == (sd << 7);
}

// �Ƿ��ںӵ�ͬһ��
inline int SAME_HALF(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0x80) == 0;//8λ2���ƣ������1λ��ͬ���ںӵ�ͬһ��
}

// �Ƿ���ͬһ��
inline int SAME_RANK(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0xf0) == 0;//8λ2���ƣ�ǰ4λ��ͬ����ͬһ��
}

// �Ƿ���ͬһ��
inline int SAME_FILE(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0x0f) == 0;//��4λ��ͬ����ͬһ��
}

// ��ú�ڱ��(������8��������16)//  sd�������巽��0����췽��1����ڷ�
inline int SIDE_TAG(int sd) {
	return 8 + (sd << 3);
}

// ��öԷ���ڱ��   //�Է�
inline int OPP_SIDE_TAG(int sd) {
	return 16 - (sd << 3);
}

// ����߷������
inline int SRC(int mv) {
	return mv & 255;
}

// ����߷����յ�
inline int DST(int mv) {
	return mv >> 8;
}

// ���������յ����߷�
inline int MOVE(int sqSrc, int sqDst)  {
	return sqSrc + sqDst * 256;
}

// �߷�ˮƽ����
inline int MIRROR_MOVE(int mv) {
	return MOVE(MIRROR_SQUARE(SRC(mv)), MIRROR_SQUARE(DST(mv)));
}

// ����ṹ
struct PositionStruct1 {
	int sdPlayer;                   // �ֵ�˭�ߣ�0=�췽��1=�ڷ�
	char ucpcSquares[256];          // �����ϵ�����

	void Startup(void) {            // ��ʼ������
		sdPlayer = 0;
		memcpy(ucpcSquares, cucpcStartup, 256);
	}
	void ChangeSide(void) {         // �������ӷ�
		sdPlayer = 1 - sdPlayer;
	}
	void AddPiece(int sq, int pc) { // �������Ϸ�һö����
		ucpcSquares[sq] = pc;
	}
	void DelPiece(int sq) {         // ������������һö����
		ucpcSquares[sq] = 0;
	}
	int MovePiece(int mv);                      // ��һ���������
	void UndoMovePiece(int mv, int pcCaptured); // ������һ���������
	int MakeMove(int mv);                      // ��һ����
	int GenerateMoves(int *mvs) const;          // ���������߷�
	int LegalMove(int mv) const;               // �ж��߷��Ƿ����
	int Checked(void) const;                   // �ж��Ƿ񱻽���
	int IsMate(void);                          // �ж��Ƿ�ɱ
};

// ��һ���������
int PositionStruct1::MovePiece(int mv) {
	int sqSrc, sqDst, pc, pcCaptured;//��㣬�յ㣬�ƶ������ӣ��յ�λ��ԭ������
	sqSrc = SRC(mv);  //����߷����
	sqDst = DST(mv);   //����߷��յ�
	pcCaptured = ucpcSquares[sqDst];//�յ�λ��ԭ����
	DelPiece(sqDst);
	pc = ucpcSquares[sqSrc];
	DelPiece(sqSrc);
	AddPiece(sqDst, pc);
	return pcCaptured;  //����ԭ���յ�λ�õ����Ӻ�
}

// ������һ��������ӣ�������һ��
void PositionStruct1::UndoMovePiece(int mv, int pcCaptured) {
	int sqSrc, sqDst, pc;
	sqSrc = SRC(mv);
	sqDst = DST(mv);
	pc = ucpcSquares[sqDst];
	DelPiece(sqDst);
	AddPiece(sqSrc, pc);
	AddPiece(sqDst, pcCaptured);
}

// ��һ����
BOOL PositionStruct1::MakeMove(int mv) {
	int pc;
	pc = MovePiece(mv);
	if (Checked()) {//���������Ϲ�
		UndoMovePiece(mv, pc);
		return FALSE;
	}
	ChangeSide();
	return TRUE;
}

// ���������߷�
int PositionStruct1::GenerateMoves(int *mvs) const {  //mvsΪ��¼�����߷�������
	int i, j, nGenMoves, nDelta, sqSrc, sqDst;
	int pcSelfSide, pcOppSide, pcSrc, pcDst;
	// ���������߷�����Ҫ�������¼������裺

	nGenMoves = 0;
	pcSelfSide = SIDE_TAG(sdPlayer);//��ú�ڱ�־����8����16
	pcOppSide = OPP_SIDE_TAG(sdPlayer);//��öԷ���ڱ�־
	for (sqSrc = 0; sqSrc < 256; sqSrc++) {

		// 1. �ҵ�һ���������ӣ����������жϣ�
		pcSrc = ucpcSquares[sqSrc];
		if ((pcSrc & pcSelfSide) == 0) {//�Է�����
			continue;  //��������Ĵ���
		}

		// 2. ��������ȷ���߷�(���ҵ�������)
		switch (pcSrc - pcSelfSide) {
		case PIECE_KING:  //�Ͻ���0
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccKingDelta[i];
				if (!IN_FORT(sqDst)) {//����յ㲻��9����������
					continue;
				}
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {//����յ����Ӳ����Լ�����
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;//��¼�ж������߷�
				}
			}
			break;
		case PIECE_ADVISOR://ʿ
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccAdvisorDelta[i];
				if (!IN_FORT(sqDst)) {//����յ㲻��9����
					continue;
				}
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;
				}
			}
			break;
		case PIECE_BISHOP://��
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccAdvisorDelta[i];//��һ��ʿ������
				if (!(IN_BOARD(sqDst) && HOME_HALF(sqDst, sdPlayer) && ucpcSquares[sqDst] == 0)) {//�յ㲻�����̻���ӻ��յ�����     ��
					continue;
				}
				sqDst += ccAdvisorDelta[i];//�ߵڶ���ʿ����Ϊ����߷�
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {//����յ㲻���Լ�����
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;
				}
			}
			break;
		case PIECE_KNIGHT://��
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccKingDelta[i];//����
				if (ucpcSquares[sqDst] != 0) {//���������
					continue;
				}
				for (j = 0; j < 2; j++) {
					sqDst = sqSrc + ccKnightDelta[i][j];
					if (!IN_BOARD(sqDst)) {//���Ŀ��λ�ò���������
						continue;
					}
					pcDst = ucpcSquares[sqDst];
					if ((pcDst & pcSelfSide) == 0) {//����յ㲻���Լ�����
						mvs[nGenMoves] = MOVE(sqSrc, sqDst);
						nGenMoves++;
					}
				}
			}
			break;
		case PIECE_ROOK://��
			for (i = 0; i < 4; i++) {
				nDelta = ccKingDelta[i];
				sqDst = sqSrc + nDelta;//��һ��
				while (IN_BOARD(sqDst)) {//Ŀ����������
					pcDst = ucpcSquares[sqDst];
					if (pcDst == 0) {//���Ŀ��������
						mvs[nGenMoves] = MOVE(sqSrc, sqDst);
						nGenMoves++;
					}
					else {
						if ((pcDst & pcOppSide) != 0) {//���Ŀ���ǶԷ�
							mvs[nGenMoves] = MOVE(sqSrc, sqDst);
							nGenMoves++;
						}
						break;
					}//else
					sqDst += nDelta;
				}//while
			}//for
			break;
		case PIECE_CANNON://��
			for (i = 0; i < 4; i++) {
				nDelta = ccKingDelta[i];
				sqDst = sqSrc + nDelta;
				while (IN_BOARD(sqDst)) {
					pcDst = ucpcSquares[sqDst];
					if (pcDst == 0) {//���Ŀ��Ϊ�ո�
						mvs[nGenMoves] = MOVE(sqSrc, sqDst);
						nGenMoves++;
					}
					else {
						break;//���Ŀ������ӣ���break,������һ��whileѭ��
					}
					sqDst += nDelta;
				}//while
				sqDst += nDelta;//����ǰһ�񣬼�Խ���赲����
				while (IN_BOARD(sqDst)) {
					pcDst = ucpcSquares[sqDst];
					if (pcDst != 0) {//���Ŀ������
						if ((pcDst & pcOppSide) != 0) {//���Ŀ���ǶԷ�����
							mvs[nGenMoves] = MOVE(sqSrc, sqDst);
							nGenMoves++;
						}
						break;//Ŀ��Ϊ�Լ����ӣ�������whileѭ��
					}
					sqDst += nDelta;
				}//while
			}//for
			break;
		case PIECE_PAWN://��
			sqDst = SQUARE_FORWARD(sqSrc, sdPlayer);//����ǰ��һ��
			if (IN_BOARD(sqDst)) {//����ڽ���
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {//���Ŀ������Լ���
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;
				}
			}
			if (AWAY_HALF(sqSrc, sdPlayer)) {//����ѹ���
				for (nDelta = -1; nDelta <= 1; nDelta += 2) {//������һ��
					sqDst = sqSrc + nDelta;
					if (IN_BOARD(sqDst)) {
						pcDst = ucpcSquares[sqDst];
						if ((pcDst & pcSelfSide) == 0) {
							mvs[nGenMoves] = MOVE(sqSrc, sqDst);
							nGenMoves++;
						}
					}
				}
			}
			break;
		}
	}
	return nGenMoves;//�����߷�����
}

// �ж��߷��Ƿ����
BOOL PositionStruct1::LegalMove(int mv) const {
	int sqSrc, sqDst, sqPin;
	int pcSelfSide, pcSrc, pcDst, nDelta;
	// �ж��߷��Ƿ�Ϸ�����Ҫ�������µ��жϹ��̣�

	// 1. �ж���ʼ���Ƿ����Լ�������
	sqSrc = SRC(mv);
	pcSrc = ucpcSquares[sqSrc];
	pcSelfSide = SIDE_TAG(sdPlayer);
	if ((pcSrc & pcSelfSide) == 0) {
		return FALSE;
	}

	// 2. �ж�Ŀ����Ƿ����Լ�������
	sqDst = DST(mv);
	pcDst = ucpcSquares[sqDst];
	if ((pcDst & pcSelfSide) != 0) {
		return FALSE;
	}

	// 3. �������ӵ����ͼ���߷��Ƿ����
	switch (pcSrc - pcSelfSide) {
	case PIECE_KING://��
		return IN_FORT(sqDst) && KING_SPAN(sqSrc, sqDst);//�յ���9�����ҷ��Ͻ��Ĳ���
	case PIECE_ADVISOR://ʿ
		return IN_FORT(sqDst) && ADVISOR_SPAN(sqSrc, sqDst);//�յ���9�����ҷ���ʿ�Ĳ���
	case PIECE_BISHOP://��
		return SAME_HALF(sqSrc, sqDst) && BISHOP_SPAN(sqSrc, sqDst) &&
			ucpcSquares[BISHOP_PIN(sqSrc, sqDst)] == 0;//����յ���ͬһ�࣬���ҷ�����Ĳ���������û������
	case PIECE_KNIGHT://��
		sqPin = KNIGHT_PIN(sqSrc, sqDst);//�������λ��
		return sqPin != sqSrc && ucpcSquares[sqPin] == 0;//�������λ�ò�Ϊ��㣬����������(����������Ĳ�������KNIGHT_PIN�����������λ��)
	case PIECE_ROOK://��
	case PIECE_CANNON://��  ��������һ���ж�
		if (SAME_RANK(sqSrc, sqDst)) {//�����ͬһ��
			nDelta = (sqDst < sqSrc ? -1 : 1);//�����ƶ�
		}
		else if (SAME_FILE(sqSrc, sqDst)) {//�����ͬһ��
			nDelta = (sqDst < sqSrc ? -16 : 16);//�����ƶ�(һ���ƶ�16��λ��)
		}
		else {//������ͬһ�л��������
			return FALSE;
		}
		sqPin = sqSrc + nDelta;
		while (sqPin != sqDst && ucpcSquares[sqPin] == 0) {//�����һ�����ص㣬����һ������
			sqPin += nDelta;
		}
		if (sqPin == sqDst) {//�����һ�����յ�
			return pcDst == 0 || pcSrc - pcSelfSide == PIECE_ROOK;//����յ����� ���߸����ǳ�  �򷵻�true
		}
		else if (pcDst != 0 && pcSrc - pcSelfSide == PIECE_CANNON) {//�����һ������   �����������  
			sqPin += nDelta;//���������ߣ�ֱ�����յ���ûԽ��
			while (sqPin != sqDst && ucpcSquares[sqPin] == 0) {
				sqPin += nDelta;
			}
			return sqPin == sqDst;
		}
		else {
			return FALSE;
		}
	case PIECE_PAWN://��
		if (AWAY_HALF(sqDst, sdPlayer) && (sqDst == sqSrc - 1 || sqDst == sqSrc + 1)) {//������Ӳ��������ƶ�������
			return TRUE;
		}
		return sqDst == SQUARE_FORWARD(sqSrc, sdPlayer);//�����ǰ�ƶ�������
	default:
		return FALSE;
	}
}

// �ж��Ƿ񱻽���
BOOL PositionStruct1::Checked() const {
	int i, j, sqSrc, sqDst;
	int pcSelfSide, pcOppSide, pcDst, nDelta;
	pcSelfSide = SIDE_TAG(sdPlayer);
	pcOppSide = OPP_SIDE_TAG(sdPlayer);
	// �ҵ������ϵ�˧(��)�����������жϣ�

	for (sqSrc = 0; sqSrc < 256; sqSrc++) {
		if (ucpcSquares[sqSrc] != pcSelfSide + PIECE_KING) {
			continue;
		}

		// 1. �ж��Ƿ񱻶Է��ı�(��)����
		if (ucpcSquares[SQUARE_FORWARD(sqSrc, sdPlayer)] == pcOppSide + PIECE_PAWN) {
			return TRUE;
		}
		for (nDelta = -1; nDelta <= 1; nDelta += 2) {
			if (ucpcSquares[sqSrc + nDelta] == pcOppSide + PIECE_PAWN) {
				return TRUE;
			}
		}

		// 2. �ж��Ƿ񱻶Է�������(����(ʿ)�Ĳ�����������)
		for (i = 0; i < 4; i++) {
			if (ucpcSquares[sqSrc + ccAdvisorDelta[i]] != 0) {
				continue;
			}
			for (j = 0; j < 2; j++) {
				pcDst = ucpcSquares[sqSrc + ccKnightCheckDelta[i][j]];
				if (pcDst == pcOppSide + PIECE_KNIGHT) {
					return TRUE;
				}
			}
		}

		// 3. �ж��Ƿ񱻶Է��ĳ����ڽ���(������˧����)
		for (i = 0; i < 4; i++) {
			nDelta = ccKingDelta[i];
			sqDst = sqSrc + nDelta;//��һ��
			while (IN_BOARD(sqDst)) {//��һ����������
				pcDst = ucpcSquares[sqDst];
				if (pcDst != 0) {//�����һ��Ϊ��
					if (pcDst == pcOppSide + PIECE_ROOK || pcDst == pcOppSide + PIECE_KING) {//��һ��Ϊ�Է������Ͻ�
						return TRUE;
					}
					break;//�����һ����Ϊ���Ҳ��ǶԷ����򽫣�����������
				}
				sqDst += nDelta;
			}//while
			sqDst += nDelta;//Խ�������,��������
			while (IN_BOARD(sqDst)) {
				int pcDst = ucpcSquares[sqDst];
				if (pcDst != 0) {
					if (pcDst == pcOppSide + PIECE_CANNON) {//������
						return TRUE;
					}
					break;
				}
				sqDst += nDelta;
			}//while
		}//for
		return FALSE;
	}//for
	return FALSE;
}

// �ж��Ƿ�ɱ
BOOL PositionStruct1::IsMate(void) {
	int i, nGenMoveNum, pcCaptured;
	int mvs[MAX_GEN_MOVES];

	nGenMoveNum = GenerateMoves(mvs);
	for (i = 0; i < nGenMoveNum; i++) {
		pcCaptured = MovePiece(mvs[i]);//����ԭ���յ�λ������
		if (!Checked()) {//���û���������򷵻���һ��
			UndoMovePiece(mvs[i], pcCaptured);
			return FALSE;//ֻҪ��һ��������������û��
		}
		else {//���������
			UndoMovePiece(mvs[i], pcCaptured);//������һ��
		}
	}
	return TRUE;//���в���������������
}

static PositionStruct1 pos; // ����ʵ��

static struct {
	HINSTANCE hInst;                              // Ӧ�ó�����ʵ��
	HWND hWnd;                                    // �����ھ��
	HDC hdc, hdcTmp;                              // �豸�����ֻ��"ClickSquare"��������Ч
	HBITMAP bmpBoard, bmpSelected, bmpPieces[24]; // ��ԴͼƬ���
	int sqSelected, mvLast;                       // ѡ�еĸ��ӣ���һ����
	BOOL bFlipped;                                // �Ƿ�ת����
} Xqwl;

// ��ʼ�����
static void Startup(void) {
	pos.Startup();
	Xqwl.sqSelected = Xqwl.mvLast = 0;
}