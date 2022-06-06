#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

#define MAPSIZE 8
#define MINESWEEPERCOUNT MAPSIZE * MAPSIZE / 5
#define COUT GetStdHandle(STD_OUTPUT_HANDLE)
#define CIN GetStdHandle(STD_INPUT_HANDLE)

typedef enum {
	BLUE = 1,
	GREEN = 2,
	RED = 4,
	YELLOW = 6,
	WHITE = 7,
	GREY = 8,
} Color;

typedef enum {
	FLAG = 1,
	NONE = 0,
	CLEAR = -1,
} MapStateInfomation;

typedef struct _Postition {
	int x;
	int y;
} Position;


Position position;
int map[MAPSIZE][MAPSIZE];
int mapState[MAPSIZE][MAPSIZE];
int leftRoomCount;
int usedFlagCount;

void initGame();
DWORD onClickEvent();
void clickMineSweeper();
void setCursorPosition(int x, int y);
void setTextColor(Color color);
void clickEmpyt();
void clickRemoveMineSweeper();
bool checkAlreadyClearBox(int x, int y);
void gameEnd(bool isClear);
void printUsedFlagCount();

#endif // !__MINESWEEPER_H__