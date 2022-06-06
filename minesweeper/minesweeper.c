#include "minesweeper.h"

void setMouseInput();
void printBG();
void setMineSweeper();
void setMineSweeperCount();
void testPrint();
void showMinesweeper(int x, int y);
void showEmyptAllRood(int x, int y);

int mapState[MAPSIZE][MAPSIZE] = { 0, };

void clickRemoveMineSweeper() {
	if (mapState[position.y][position.x] == NONE) {
		setCursorPosition(position.x * 2, position.y);
		mapState[position.y][position.x] = FLAG;
		printf("▣");
		usedFlagCount--;

		printUsedFlagCount();
	}
}

void printBG() {
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			printf("□");
		}
		printf("\n");
	}
}

void setMineSweeper() {
	srand(time(NULL));
	leftRoomCount = MAPSIZE * MAPSIZE;
	usedFlagCount = MINESWEEPERCOUNT;

	bool isAllready = false;

	for (int i = 0; i < MINESWEEPERCOUNT; i++) {
		while (1) {
			int x = rand() % MAPSIZE;
			int y = rand() % MAPSIZE;

			if (map[y][x] != -1) {
				map[y][x] = -1;
				leftRoomCount--;
				break;
			}
		}
	}
}

void setMineSweeperCount() {
	for (int y = 0; y < MAPSIZE; y++) {
		for (int x = 0; x < MAPSIZE; x++) {
			if (map[y][x] == -1) {
				int tempY = y - 1;
				int tempX = x - 1;

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (map[tempY][tempX] != -1) {
							if (tempX > -1 && tempX < MAPSIZE && tempY > -1 && tempY < MAPSIZE)
								map[tempY][tempX] += 1;
						}

						tempX += 1;
					}

					tempY += 1;
					tempX = x - 1;
				}
			}
		}
	}
}

void testPrint() {
	position = (Position){ -1, -1 };

	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}

	printUsedFlagCount();
}

void setMouseInput() {
	DWORD mode;

	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
}

void initGame() {
	printBG();
	setMineSweeper();
	setMineSweeperCount();
	printf("\n\n");
	//testPrint();
	setMouseInput();
	printUsedFlagCount();
}

DWORD onClickEvent() {
	INPUT_RECORD record;
	DWORD read;

	ReadConsoleInput(CIN, &record, 1, &read);

	if (record.EventType == MOUSE_EVENT) {
		if ((!(record.Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
			&& !(record.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK)) && (
				record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
				|| record.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)) {

			position.x = record.Event.MouseEvent.dwMousePosition.X;
			position.y = record.Event.MouseEvent.dwMousePosition.Y;

			if (position.x % 2 != 0) {
				position.x--;
			}

			position.x /= 2;

			return record.Event.MouseEvent.dwButtonState;
		}
	}

	return 0x00;
}

void clickMineSweeper() {
	showMinesweeper(position.x * 2, position.y);
	for (int y = 0; y < MAPSIZE; y++) {
		for (int x = 0; x < MAPSIZE; x++) {
			if ((x != position.x || y != position.y)) {
				if (map[y][x] == -1 && mapState[y][x] != FLAG) {
					showMinesweeper(x * 2, y);
				}
				if (mapState[y][x] == FLAG && map[y][x] != -1) {
					setCursorPosition(x * 2, y);
					setTextColor(YELLOW);
					printf("※");
				}
			}
		}
	}

	position = (Position){ -1, -1 };
}

void setCursorPosition(int x, int y) {
	COORD cur;

	cur.X = x;
	cur.Y = y;

	SetConsoleCursorPosition(COUT, cur);
}

void setTextColor(Color color) {
	SetConsoleTextAttribute(COUT, color);
}

void clickEmpyt() {
	if (checkAlreadyClearBox(position.x, position.y))
		return;

	if (map[position.y][position.x] == 0) {
		showEmyptAllRood(position.x, position.y, -1, -1);
	}
	else {
		setCursorPosition(position.x * 2, position.y);
		printf("%2d", map[position.y][position.x]);
		mapState[position.y][position.x] = CLEAR;
		leftRoomCount--;
	}

	if (leftRoomCount == 0) {
		gameEnd(true);
	}

	position = (Position){ -1, -1 };
}


void showMinesweeper(int x, int y) {
	setTextColor(RED);
	setCursorPosition(x, y);
	printf("●");
	Sleep(500);
}

void showEmyptAllRood(int x, int y) {
	int tempY = y - 1;
	int tempX = x - 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			setCursorPosition(tempX * 2, tempY);

			if (tempX > -1 && tempX < MAPSIZE && tempY > -1 && tempY < MAPSIZE) {
				if (!checkAlreadyClearBox(tempX, tempY)) {
					mapState[tempY][tempX] = CLEAR;
					leftRoomCount--;
					if (map[tempY][tempX] == 0) {
						printf("  ", map[tempY][tempX]);
						showEmyptAllRood(tempX, tempY);
					}
					else {
						printf("%2d", map[tempY][tempX]);
					}
				}
			}
			tempX++;
		}

		tempY++;
		tempX = x - 1;
	}
}

bool checkAlreadyClearBox(int x, int y) {
	return mapState[y][x] == CLEAR;
}

void gameEnd(bool isClear) {
	setCursorPosition(0, MAPSIZE + 2);

	if (isClear) {
		printf("승리하였습니다.\n");
	}
	else {
		printf("패배하였습니다.\n");
	}

	system("pause");
	exit(0);
}

void printUsedFlagCount() {
	setCursorPosition(MAPSIZE * 2 + 3, 0);
	printf("깃발 수 : %2d", usedFlagCount);
}