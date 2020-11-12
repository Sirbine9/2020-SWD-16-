#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "Map.h"			// 맵에 관련된 함수들(고현종님의 함수)
#include "basic.h"   		// 기본적으로 사용하는 함수들
#include "define.h"			// 함수들의 원형 선언 및 전역함수의 선언
#include "PCMove.h"			// PC의 이동에 관한 함수
#include "BulletMove.h"		// 탄환의 이동에 관한 함수
#include "enemy.h"			// NPC 관련 함수

int main() {
	/*DrawBoard();
	for (int i = 0; i < GBOARD_HEIGHT+1; i++) {
		for (int x = 0; x < GBOARD_WIDTH + 2; x++) {
			printf("%d ", gameBoardInfo[i][x]);
		}
		printf("\n");
	}*/
	system("mode con cols=92 lines=50");
	Init();
	PrintStatus();
	DrawBoard();
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("★");

	while (1)
	{	
		RemoveCursor();
		InitGame();
		CallNextWave();
		//ProcessKeyInput();
	}
	return 0;
}