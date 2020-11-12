#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "define.h"
#include "basic.h"
#include "Map.h"
// 2020.11.08 작성자: 고현종

void TextColor(int color_number)				// 콘솔창에 출력되는 텍스트의 색을 결정 (0 <= color_number <= 15)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void DrawBoard()
{
	TextColor(8);								// 콘솔창의 기본 텍스트 컬러
	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_ORIGIN_Y][x] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
		//TextColor(((x + num) % 7) + 8);
		printf("■");
	}

	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_ORIGIN_Y+2][x] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + 4);
		//TextColor(((x + num) % 7) + 8);
		printf("■");
	}

	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		//TextColor(((x + num) % 7) + 8);
		printf("■");
	}

	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		gameBoardInfo[y][0] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
		//TextColor(((y + num) % 7) + 8);
		printf("■");
	}

	for (int y = 0; y <= GBOARD_HEIGHT; y++)
	{
		gameBoardInfo[y][GBOARD_WIDTH + 1] = BLOCK;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
		//TextColor(((y + num) % 7) + 8);
		printf("■");
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
	TextColor(12);													// 텍스트 컬러 RED
	for (int i = 0; i < life; i++)
		printf("♥");
}

// 작성자: 차명진
void ResetGameBoard()												//게임보드 재설정을 위한 함수
{																		

	for (int y = 5; y < GBOARD_HEIGHT; y++)							//게임판 위의 모든 NPC, PC를 제거하기 위한 부분
	{						
		for (int x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y);
			printf("  ");
		}
	}
	for (int y = 5; y < GBOARD_HEIGHT; y++)							//게임판의 좌측 상단의 좌표는 5,1입니다.게임 판의 y범위 5~39 x범위 1~40까지 모두 0의값으로 초기화 시킵니다. 0=> 비어있음.    
	{						
		for (int x = 1; x < GBOARD_WIDTH + 1; x++)					//게임보드를 정보를 전부 초기화하기 위해 EMPTY 0 값을 삽입합니다. 
		{
			gameBoardInfo[y][x] = EMPTY;							
		}
	}
	// SetCurrentCursorPos(GBOARD_ORIGIN_X*2, GBOARD_HEIGHT+3);
}
