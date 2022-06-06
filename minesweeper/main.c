#include "minesweeper.h"
#include <stdio.h>

int main() {
	initGame();

	while (1) {
		DWORD buttonState = onClickEvent();

		if (0 <= position.x && 0 <= position.y && MAPSIZE > position.x && MAPSIZE > position.y) {
			if (buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				if (map[position.y][position.x] == -1) {
					clickMineSweeper();
					gameEnd(false);
				}
				else {
					clickEmpyt();
				}
			}
			else if (buttonState == RIGHTMOST_BUTTON_PRESSED) {
				clickRemoveMineSweeper();
			}
		}
	}
}