#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "Map.h"			// �ʿ� ���õ� �Լ���(���������� �Լ�)
#include "basic.h"   		// �⺻������ ����ϴ� �Լ���
#include "define.h"			// �Լ����� ���� ���� �� �����Լ��� ����
#include "PCMove.h"			// PC�� �̵��� ���� �Լ�
#include "BulletMove.h"		// źȯ�� �̵��� ���� �Լ�
#include "enemy.h"			// NPC ���� �Լ�

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
	printf("��");

	while (1)
	{	
		RemoveCursor();
		InitGame();
		CallNextWave();
		//ProcessKeyInput();
	}
	return 0;
}