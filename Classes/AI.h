/*
玩家对弈的AI
*/

// 棋盘范围
const int RANK_TOP = 3;
const int RANK_BOTTOM = 12;
const int FILE_LEFT = 3;
const int FILE_RIGHT = 11;

// 棋子编号
const int PIECE_KING = 0;
const int PIECE_ADVISOR = 1;
const int PIECE_BISHOP = 2;
const int PIECE_KNIGHT = 3;
const int PIECE_ROOK = 4;
const int PIECE_CANNON = 5;
const int PIECE_PAWN = 6;

// 其他常数
const int MAX_GEN_MOVES = 128; // 最大的生成走法数

// 判断棋子是否在棋盘中的数组
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

// 判断棋子是否在九宫的数组
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

// 判断步长是否符合特定走法的数组，1=帅(将)，2=仕(士)，3=相(象)
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

// 根据步长判断马是否蹩腿的数组
static const char ccKnightPin[512] = {//因为是用的256的棋盘，所以步长最大为正负255，为了消除负的，将步长加256，所以这里是512长的数组
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

// 帅(将)的步长
static const char ccKingDelta[4] = { -16, -1, 1, 16 };
// 仕(士)的步长
static const char ccAdvisorDelta[4] = { -17, -15, 15, 17 };
// 马的步长，以帅(将)的步长作为马腿
static const char ccKnightDelta[4][2] = { { -33, -31 }, { -18, 14 }, { -14, 18 }, { 31, 33 } };
// 马被将军的步长，以仕(士)的步长作为马腿
static const char ccKnightCheckDelta[4][2] = { { -33, -18 }, { -31, -14 }, { 14, 31 }, { 18, 33 } };

// 棋盘初始设置
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

// 判断棋子是否在棋盘中
inline int IN_BOARD(int sq) {
	return ccInBoard[sq] != 0;
}

// 判断棋子是否在九宫中
inline int IN_FORT(int sq) {
	return ccInFort[sq] != 0;
}

// 获得格子的横坐标  //横纵坐标，格子坐标都从0开始
inline int RANK_Y(int sq) {
	return sq >> 4;//右移4位，相当于除以16
}

// 获得格子的纵坐标
inline int FILE_X(int sq) {
	return sq & 15;
}

// 根据纵坐标和横坐标获得格子
inline int COORD_XY(int x, int y) {
	return x + (y << 4);
}

// 翻转格子  //计算子力时，黑方格子有颠倒
inline int SQUARE_FLIP(int sq) {
	return 254 - sq;
}

// 纵坐标水平镜像
inline int FILE_FLIP(int x) {
	return 14 - x;
}

// 横坐标垂直镜像
inline int RANK_FLIP(int y) {
	return 15 - y;
}

// 格子水平镜像
inline int MIRROR_SQUARE(int sq) {
	return COORD_XY(FILE_FLIP(FILE_X(sq)), RANK_Y(sq));
}

// 格子水平镜像
inline int SQUARE_FORWARD(int sq, int sd) {
	return sq - 16 + (sd << 5);  //返回兵向前走一步后的位置
}

// 走法是否符合帅(将)的步长
inline int KING_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 1;
}

// 走法是否符合仕(士)的步长
inline int ADVISOR_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 2;
}

// 走法是否符合相(象)的步长
inline int BISHOP_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 3;
}

// 相(象)眼的位置  //起点加终点除以2
inline int BISHOP_PIN(int sqSrc, int sqDst) {
	return (sqSrc + sqDst) >> 1;
}

// 马腿的位置
inline int KNIGHT_PIN(int sqSrc, int sqDst) {
	return sqSrc + ccKnightPin[sqDst - sqSrc + 256];
}

// 是否未过河//?
inline int HOME_HALF(int sq, int sd) {  //sq为棋盘上的位置，sd是走棋方
	return (sq & 0x80) != (sd << 7);
}

// 是否已过河//?
inline int AWAY_HALF(int sq, int sd) {
	return (sq & 0x80) == (sd << 7);
}

// 是否在河的同一边
inline int SAME_HALF(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0x80) == 0;//8位2进制，最左边1位相同即在河的同一边
}

// 是否在同一行
inline int SAME_RANK(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0xf0) == 0;//8位2进制，前4位相同即是同一行
}

// 是否在同一列
inline int SAME_FILE(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0x0f) == 0;//后4位相同即在同一列
}

// 获得红黑标记(红子是8，黑子是16)//  sd代表走棋方，0代表红方，1代表黑方
inline int SIDE_TAG(int sd) {
	return 8 + (sd << 3);
}

// 获得对方红黑标记   //对方
inline int OPP_SIDE_TAG(int sd) {
	return 16 - (sd << 3);
}

// 获得走法的起点
inline int SRC(int mv) {
	return mv & 255;
}

// 获得走法的终点
inline int DST(int mv) {
	return mv >> 8;
}

// 根据起点和终点获得走法
inline int MOVE(int sqSrc, int sqDst)  {
	return sqSrc + sqDst * 256;
}

// 走法水平镜像
inline int MIRROR_MOVE(int mv) {
	return MOVE(MIRROR_SQUARE(SRC(mv)), MIRROR_SQUARE(DST(mv)));
}

// 局面结构
struct PositionStruct1 {
	int sdPlayer;                   // 轮到谁走，0=红方，1=黑方
	char ucpcSquares[256];          // 棋盘上的棋子

	void Startup(void) {            // 初始化棋盘
		sdPlayer = 0;
		memcpy(ucpcSquares, cucpcStartup, 256);
	}
	void ChangeSide(void) {         // 交换走子方
		sdPlayer = 1 - sdPlayer;
	}
	void AddPiece(int sq, int pc) { // 在棋盘上放一枚棋子
		ucpcSquares[sq] = pc;
	}
	void DelPiece(int sq) {         // 从棋盘上拿走一枚棋子
		ucpcSquares[sq] = 0;
	}
	int MovePiece(int mv);                      // 搬一步棋的棋子
	void UndoMovePiece(int mv, int pcCaptured); // 撤消搬一步棋的棋子
	int MakeMove(int mv);                      // 走一步棋
	int GenerateMoves(int *mvs) const;          // 生成所有走法
	int LegalMove(int mv) const;               // 判断走法是否合理
	int Checked(void) const;                   // 判断是否被将军
	int IsMate(void);                          // 判断是否被杀
};

// 搬一步棋的棋子
int PositionStruct1::MovePiece(int mv) {
	int sqSrc, sqDst, pc, pcCaptured;//起点，终点，移动的棋子，终点位置原来棋子
	sqSrc = SRC(mv);  //获得走法起点
	sqDst = DST(mv);   //获得走法终点
	pcCaptured = ucpcSquares[sqDst];//终点位置原棋子
	DelPiece(sqDst);
	pc = ucpcSquares[sqSrc];
	DelPiece(sqSrc);
	AddPiece(sqDst, pc);
	return pcCaptured;  //返回原来终点位置的棋子号
}

// 撤消搬一步棋的棋子，返回上一步
void PositionStruct1::UndoMovePiece(int mv, int pcCaptured) {
	int sqSrc, sqDst, pc;
	sqSrc = SRC(mv);
	sqDst = DST(mv);
	pc = ucpcSquares[sqDst];
	DelPiece(sqDst);
	AddPiece(sqSrc, pc);
	AddPiece(sqDst, pcCaptured);
}

// 走一步棋
BOOL PositionStruct1::MakeMove(int mv) {
	int pc;
	pc = MovePiece(mv);
	if (Checked()) {//检查如果不合规
		UndoMovePiece(mv, pc);
		return FALSE;
	}
	ChangeSide();
	return TRUE;
}

// 生成所有走法
int PositionStruct1::GenerateMoves(int *mvs) const {  //mvs为记录所有走法的数组
	int i, j, nGenMoves, nDelta, sqSrc, sqDst;
	int pcSelfSide, pcOppSide, pcSrc, pcDst;
	// 生成所有走法，需要经过以下几个步骤：

	nGenMoves = 0;
	pcSelfSide = SIDE_TAG(sdPlayer);//获得红黑标志，红8，黑16
	pcOppSide = OPP_SIDE_TAG(sdPlayer);//获得对方红黑标志
	for (sqSrc = 0; sqSrc < 256; sqSrc++) {

		// 1. 找到一个本方棋子，再做以下判断：
		pcSrc = ucpcSquares[sqSrc];
		if ((pcSrc & pcSelfSide) == 0) {//对方的子
			continue;  //跳过下面的代码
		}

		// 2. 根据棋子确定走法(已找到己方子)
		switch (pcSrc - pcSelfSide) {
		case PIECE_KING:  //老将，0
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccKingDelta[i];
				if (!IN_FORT(sqDst)) {//如果终点不在9宫格，则作废
					continue;
				}
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {//如果终点棋子不是自己的子
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;//记录有多少种走法
				}
			}
			break;
		case PIECE_ADVISOR://士
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccAdvisorDelta[i];
				if (!IN_FORT(sqDst)) {//如果终点不在9宫格
					continue;
				}
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;
				}
			}
			break;
		case PIECE_BISHOP://象
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccAdvisorDelta[i];//走一步士找象眼
				if (!(IN_BOARD(sqDst) && HOME_HALF(sqDst, sdPlayer) && ucpcSquares[sqDst] == 0)) {//终点不在棋盘或过河或终点有子     ？
					continue;
				}
				sqDst += ccAdvisorDelta[i];//走第二步士，则为象的走法
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {//如果终点不是自己的子
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;
				}
			}
			break;
		case PIECE_KNIGHT://马
			for (i = 0; i < 4; i++) {
				sqDst = sqSrc + ccKingDelta[i];//马腿
				if (ucpcSquares[sqDst] != 0) {//如果蹩马腿
					continue;
				}
				for (j = 0; j < 2; j++) {
					sqDst = sqSrc + ccKnightDelta[i][j];
					if (!IN_BOARD(sqDst)) {//如果目标位置不在棋盘上
						continue;
					}
					pcDst = ucpcSquares[sqDst];
					if ((pcDst & pcSelfSide) == 0) {//如果终点不是自己的子
						mvs[nGenMoves] = MOVE(sqSrc, sqDst);
						nGenMoves++;
					}
				}
			}
			break;
		case PIECE_ROOK://车
			for (i = 0; i < 4; i++) {
				nDelta = ccKingDelta[i];
				sqDst = sqSrc + nDelta;//走一步
				while (IN_BOARD(sqDst)) {//目标在棋盘中
					pcDst = ucpcSquares[sqDst];
					if (pcDst == 0) {//如果目标上无子
						mvs[nGenMoves] = MOVE(sqSrc, sqDst);
						nGenMoves++;
					}
					else {
						if ((pcDst & pcOppSide) != 0) {//如果目标是对方
							mvs[nGenMoves] = MOVE(sqSrc, sqDst);
							nGenMoves++;
						}
						break;
					}//else
					sqDst += nDelta;
				}//while
			}//for
			break;
		case PIECE_CANNON://炮
			for (i = 0; i < 4; i++) {
				nDelta = ccKingDelta[i];
				sqDst = sqSrc + nDelta;
				while (IN_BOARD(sqDst)) {
					pcDst = ucpcSquares[sqDst];
					if (pcDst == 0) {//如果目标为空格
						mvs[nGenMoves] = MOVE(sqSrc, sqDst);
						nGenMoves++;
					}
					else {
						break;//如果目标格有子，则break,跳到下一个while循环
					}
					sqDst += nDelta;
				}//while
				sqDst += nDelta;//再往前一格，即越过阻挡的子
				while (IN_BOARD(sqDst)) {
					pcDst = ucpcSquares[sqDst];
					if (pcDst != 0) {//如果目标有子
						if ((pcDst & pcOppSide) != 0) {//如果目标是对方的子
							mvs[nGenMoves] = MOVE(sqSrc, sqDst);
							nGenMoves++;
						}
						break;//目标为自己的子，则跳出while循环
					}
					sqDst += nDelta;
				}//while
			}//for
			break;
		case PIECE_PAWN://兵
			sqDst = SQUARE_FORWARD(sqSrc, sdPlayer);//兵向前走一步
			if (IN_BOARD(sqDst)) {//如果在界内
				pcDst = ucpcSquares[sqDst];
				if ((pcDst & pcSelfSide) == 0) {//如果目标格不是自己子
					mvs[nGenMoves] = MOVE(sqSrc, sqDst);
					nGenMoves++;
				}
			}
			if (AWAY_HALF(sqSrc, sdPlayer)) {//如果已过河
				for (nDelta = -1; nDelta <= 1; nDelta += 2) {//左右移一步
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
	return nGenMoves;//返回走法数量
}

// 判断走法是否合理
BOOL PositionStruct1::LegalMove(int mv) const {
	int sqSrc, sqDst, sqPin;
	int pcSelfSide, pcSrc, pcDst, nDelta;
	// 判断走法是否合法，需要经过以下的判断过程：

	// 1. 判断起始格是否有自己的棋子
	sqSrc = SRC(mv);
	pcSrc = ucpcSquares[sqSrc];
	pcSelfSide = SIDE_TAG(sdPlayer);
	if ((pcSrc & pcSelfSide) == 0) {
		return FALSE;
	}

	// 2. 判断目标格是否有自己的棋子
	sqDst = DST(mv);
	pcDst = ucpcSquares[sqDst];
	if ((pcDst & pcSelfSide) != 0) {
		return FALSE;
	}

	// 3. 根据棋子的类型检查走法是否合理
	switch (pcSrc - pcSelfSide) {
	case PIECE_KING://将
		return IN_FORT(sqDst) && KING_SPAN(sqSrc, sqDst);//终点在9宫格，且符合将的步长
	case PIECE_ADVISOR://士
		return IN_FORT(sqDst) && ADVISOR_SPAN(sqSrc, sqDst);//终点在9宫格，且符合士的步长
	case PIECE_BISHOP://象
		return SAME_HALF(sqSrc, sqDst) && BISHOP_SPAN(sqSrc, sqDst) &&
			ucpcSquares[BISHOP_PIN(sqSrc, sqDst)] == 0;//起点终点在同一侧，并且符合象的步长，并且没有象眼
	case PIECE_KNIGHT://马
		sqPin = KNIGHT_PIN(sqSrc, sqDst);//获得马腿位置
		return sqPin != sqSrc && ucpcSquares[sqPin] == 0;//如果马腿位置不为起点，并且无马腿(若不符合马的步长，则KNIGHT_PIN函数返回起点位置)
	case PIECE_ROOK://车
	case PIECE_CANNON://炮  车和炮在一起判断
		if (SAME_RANK(sqSrc, sqDst)) {//如果在同一行
			nDelta = (sqDst < sqSrc ? -1 : 1);//左右移动
		}
		else if (SAME_FILE(sqSrc, sqDst)) {//如果在同一列
			nDelta = (sqDst < sqSrc ? -16 : 16);//上下移动(一次移动16个位置)
		}
		else {//若不在同一行或列则错误
			return FALSE;
		}
		sqPin = sqSrc + nDelta;
		while (sqPin != sqDst && ucpcSquares[sqPin] == 0) {//如果下一格不是重点，且下一个无子
			sqPin += nDelta;
		}
		if (sqPin == sqDst) {//如果下一格是终点
			return pcDst == 0 || pcSrc - pcSelfSide == PIECE_ROOK;//如果终点无子 或者该子是车  则返回true
		}
		else if (pcDst != 0 && pcSrc - pcSelfSide == PIECE_CANNON) {//如果下一步有子   且起点子是炮  
			sqPin += nDelta;//继续往下走，直到到终点且没越界
			while (sqPin != sqDst && ucpcSquares[sqPin] == 0) {
				sqPin += nDelta;
			}
			return sqPin == sqDst;
		}
		else {
			return FALSE;
		}
	case PIECE_PAWN://兵
		if (AWAY_HALF(sqDst, sdPlayer) && (sqDst == sqSrc - 1 || sqDst == sqSrc + 1)) {//如果过河并且左右移动返回真
			return TRUE;
		}
		return sqDst == SQUARE_FORWARD(sqSrc, sdPlayer);//如果向前移动返回真
	default:
		return FALSE;
	}
}

// 判断是否被将军
BOOL PositionStruct1::Checked() const {
	int i, j, sqSrc, sqDst;
	int pcSelfSide, pcOppSide, pcDst, nDelta;
	pcSelfSide = SIDE_TAG(sdPlayer);
	pcOppSide = OPP_SIDE_TAG(sdPlayer);
	// 找到棋盘上的帅(将)，再做以下判断：

	for (sqSrc = 0; sqSrc < 256; sqSrc++) {
		if (ucpcSquares[sqSrc] != pcSelfSide + PIECE_KING) {
			continue;
		}

		// 1. 判断是否被对方的兵(卒)将军
		if (ucpcSquares[SQUARE_FORWARD(sqSrc, sdPlayer)] == pcOppSide + PIECE_PAWN) {
			return TRUE;
		}
		for (nDelta = -1; nDelta <= 1; nDelta += 2) {
			if (ucpcSquares[sqSrc + nDelta] == pcOppSide + PIECE_PAWN) {
				return TRUE;
			}
		}

		// 2. 判断是否被对方的马将军(以仕(士)的步长当作马腿)
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

		// 3. 判断是否被对方的车或炮将军(包括将帅对脸)
		for (i = 0; i < 4; i++) {
			nDelta = ccKingDelta[i];
			sqDst = sqSrc + nDelta;//下一格
			while (IN_BOARD(sqDst)) {//下一个在棋盘中
				pcDst = ucpcSquares[sqDst];
				if (pcDst != 0) {//如果下一格不为空
					if (pcDst == pcOppSide + PIECE_ROOK || pcDst == pcOppSide + PIECE_KING) {//下一格为对方车或老将
						return TRUE;
					}
					break;//如果下一个不为空且不是对方车或将，则跳到下面
				}
				sqDst += nDelta;
			}//while
			sqDst += nDelta;//越过这个子,往下找炮
			while (IN_BOARD(sqDst)) {
				int pcDst = ucpcSquares[sqDst];
				if (pcDst != 0) {
					if (pcDst == pcOppSide + PIECE_CANNON) {//若是炮
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

// 判断是否被杀
BOOL PositionStruct1::IsMate(void) {
	int i, nGenMoveNum, pcCaptured;
	int mvs[MAX_GEN_MOVES];

	nGenMoveNum = GenerateMoves(mvs);
	for (i = 0; i < nGenMoveNum; i++) {
		pcCaptured = MovePiece(mvs[i]);//返回原来终点位置棋子
		if (!Checked()) {//如果没被将军，则返回上一步
			UndoMovePiece(mvs[i], pcCaptured);
			return FALSE;//只要有一步不被将军，则没死
		}
		else {//如果被将军
			UndoMovePiece(mvs[i], pcCaptured);//返回上一步
		}
	}
	return TRUE;//所有步都被将军，死了
}

static PositionStruct1 pos; // 局面实例

static struct {
	HINSTANCE hInst;                              // 应用程序句柄实例
	HWND hWnd;                                    // 主窗口句柄
	HDC hdc, hdcTmp;                              // 设备句柄，只在"ClickSquare"过程中有效
	HBITMAP bmpBoard, bmpSelected, bmpPieces[24]; // 资源图片句柄
	int sqSelected, mvLast;                       // 选中的格子，上一步棋
	BOOL bFlipped;                                // 是否翻转棋盘
} Xqwl;

// 初始化棋局
static void Startup(void) {
	pos.Startup();
	Xqwl.sqSelected = Xqwl.mvLast = 0;
}