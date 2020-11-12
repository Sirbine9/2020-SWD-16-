#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "define.h"
#include "basic.h"
#include "Map.h"
// 2020.11.08 �ۼ���: ������

void TextColor(int color_number)				// �ܼ�â�� ��µǴ� �ؽ�Ʈ�� ���� ���� (0 <= color_number <= 15)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void DrawBoard()
{
	TextColor(8);								// �ܼ�â�� �⺻ �ؽ�Ʈ �÷�
	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_ORIGIN_Y][x] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
		//TextColor(((x + num) % 7) + 8);
		printf("��");
	}

	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_ORIGIN_Y+2][x] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + 4);
		//TextColor(((x + num) % 7) + 8);
		printf("��");
	}

	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		//TextColor(((x + num) % 7) + 8);
		printf("��");
	}

	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		gameBoardInfo[y][0] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
		//TextColor(((y + num) % 7) + 8);
		printf("��");
	}

	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		gameBoardInfo[y][GBOARD_WIDTH + 1] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
		//TextColor(((y + num) % 7) + 8);
		printf("��");
	}
	// num++;
}

void PrintStatus()
{
	SetCurrentCursorPos(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 2);
	printf("WAVE %d", wave);

	SetCurrentCursorPos(GBOARD_ORIGIN_X + 32, GBOARD_ORIGIN_Y + 2);
	printf("SCORE: %d", score);

	SetCurrentCursorPos(GBOARD_ORIGIN_X + 62, GBOARD_ORIGIN_Y + 2);
	printf("LIFE: ");
	TextColor(12);													// �ؽ�Ʈ �÷� RED
	for (int i = 0; i < life; i++)
		printf("��");
}

// �ۼ���: ������
void ResetGameBoard()												//���Ӻ��� �缳���� ���� �Լ�
{																		

	for (int y = 5; y < GBOARD_HEIGHT; y++)							//������ ���� ��� NPC, PC�� �����ϱ� ���� �κ�
	{						
		for (int x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
			printf("  ");
		}
	}
	for (int y = 5; y < GBOARD_HEIGHT; y++)							//�������� ���� ����� ��ǥ�� 5,1�Դϴ�.���� ���� y���� 5~39 x���� 1~40���� ��� 0�ǰ����� �ʱ�ȭ ��ŵ�ϴ�. 0=> �������.    
	{						
		for (int x = 1; x < GBOARD_WIDTH + 1; x++)					//���Ӻ��带 ������ ���� �ʱ�ȭ�ϱ� ���� EMPTY 0 ���� �����մϴ�. 
		{
			gameBoardInfo[y][x] = EMPTY;							
		}
	}
	// SetCurrentCursorPos(GBOARD_ORIGIN_X*2, GBOARD_HEIGHT+3);
}
