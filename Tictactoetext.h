#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#pragma warning(disable:4996)

using namespace std;

enum {
	EMPTY,
	COMPUTER,
	USER,
	BOARDSIZE,
	INF = 1000
};

enum {
	DRAW,
	COMPUTERWIN,
	USERWIN,
	INPUTPOSITION,
	OUTOFRANGE,
	CHECKEDPOSITION,
	CONTINUE,
	COMPUTERORDER,
	USERORDER,
};

static const char symbol[3] = { '_', 'X', 'O' };

struct Point {
	int x, y;

	Point() { ; }
	Point(int ax, int ay) {
		x = ax;
		y = ay;
	}
};

class CBoard {
private:
	int board[BOARDSIZE][BOARDSIZE];
	int currentPosition;
	int winner;
	int checkedCell;
	int bestPosition[2];
	const int maxDepth = 9; // c++ 11부터는 class안에서 초기화가 가능하다.

public:
	CBoard() { ; }
	~CBoard() {	}
	void InitBoard();
	void InitData();
	void SetCell(int position, int player);
	void SetZero(int position);
	void GetEmptyPosition(int* emptyPosition);
	void SetBestPosition(int pos, int score);
	bool isFill(int position);
	bool isWin(int player);
	bool isSamePlayer(Point p, int player);
	bool isDraw() { return checkedCell == BOARDSIZE * BOARDSIZE; }
	int  GetCount(const Point direction[2], int position, int player);
	int  Evaluation();
	int  MinimaxAlphaBeta(int depth, int player, int alpha, int beta);
	int  GetBestPosotion();
	int  GetMaxDepth() { return maxDepth; }
	Point GetPoint(int position);
};

// 입출력 도구 
class CTools {
private:
	char strNumber[10];

public:
	CTools() { ; }
	~CTools() { ; }
	void InitStrNumber() { strncpy(strNumber, "123456789", 10); }
	void SetPosition(int position, int player) { strNumber[position] = symbol[player]; }
	void PrintBoard();
	void ShowMessage(int msgType);
	bool isFill(int position);
	int  GetPosition();
};

class CPlayer {
public:
	static CBoard* pBoard;
	static CTools* pTools;
	int ID;

public:
	CPlayer() {	}
	virtual ~CPlayer() {  }
	virtual int Action() = 0;

	void SetMember(CBoard* ptrBoard, CTools* ptrTools) {
		pBoard = ptrBoard;
		pTools = ptrTools;
	}
};
CBoard* CPlayer::pBoard = NULL;
CTools* CPlayer::pTools = NULL;

class CUser : public CPlayer {
public:
	CUser() { ID = USER; }
	virtual int Action();
};

class CAI : public CPlayer {
public:
	CAI() { ID = COMPUTER; }
	virtual int Action();
};

class CTictactoe {
private:
	CBoard board;
	CTools tools;
	CUser user;
	CAI AI;
	CPlayer* Player[2] = { &AI, &user };

public:
	CTictactoe() {
		user.SetMember(&board, &tools);
	}
	~CTictactoe() { }
	bool isFinish(int player);
	bool isContinue();
	void RandomPlay(int player);
	void ShowBoard(int position, int player);
	void InitGame();
	void PlayGame();
	CPlayer* GetPlayer();
};
