#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "define.h"
#include "basic.h"
#include "PcMove.h"
#include "BulletMove.h"
#include "DetectCollision.h"
// 2020.11.08 작성자: 차명진

void ShiftRight()
{
	if (PcDetectCollision(CurPcX + 2, CurPcY)==FALSE)
		return;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("  ");
	CurPcX += 2;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("★");
}

void ShiftLeft()
{
	if (PcDetectCollision(CurPcX - 2, CurPcY)==FALSE)
		return;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("  ");
	CurPcX -= 2;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("★");
}

void ShiftUp()
{
	if (PcDetectCollision(CurPcX, CurPcY - 1)==FALSE)
		return;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("  ");
	CurPcY -= 1;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("★");
}

void ShiftDown()
{
	if (PcDetectCollision(CurPcX, CurPcY + 1)==FALSE)
		return;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("  ");
	CurPcY += 1;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("★");
}

void ProcessKeyInput(EnemyList* in)
{
	int z;
	for (int i = 0; i < 10; i++) {
		if (i == 0)
			z = 0;
		if (_kbhit() != 0) {
			int key = _getch();
			switch (key) {
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case UP:
				ShiftUp();
				break;
			case DOWN:
				ShiftDown();
				break;
			case UPKEY:
				DirPcY = -1;
				DirPcX = 0;
				if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
					DirPcX = 1;
				if (GetAsyncKeyState(VK_LEFT) & 0x8000)
					DirPcX = -1;
				break;
			case DOWNKEY:
				DirPcY = 1;
				DirPcX = 0;
				if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
					DirPcX = 1;
				if (GetAsyncKeyState(VK_LEFT) & 0x8000)
					DirPcX = -1;
				break;
			case RKEY:
				DirPcX = 1;
				DirPcY = 0;
				if (GetAsyncKeyState(VK_UP) & 0x8000)
					DirPcY = -1;
				if (GetAsyncKeyState(VK_DOWN) & 0x8000)
					DirPcY = 1;
				break;
			case LKEY:
				DirPcX = -1;
				DirPcY = 0;
				if (GetAsyncKeyState(VK_UP) & 0x8000)
					DirPcY = -1;
				if (GetAsyncKeyState(VK_DOWN) & 0x8000)
					DirPcY = 1;
				break;
			case SPACE:
				if (z == 0) {
					BulletAdd();
					z = 1;
				}
				break;
			}
		}
		Sleep(50);
		BulletPrint(in);
	}
}