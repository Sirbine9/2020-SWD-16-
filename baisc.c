#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "define.h"
#include "basic.h"
#include "BulletMove.h"
#include "enemy.h"
#include "PcMove.h"
#include "Map.h"
// 2020.11.08 �ۼ���: ������

void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void SetCurrentCursorPos(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

COORD GetCurrentCursorPos(void)
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

int DetectCollision(int posX, int posY)					// �ش� ��ǥ�� ������ ���� �ٸ� �� ���
{ 
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;			// 0 ���� ����� ������ �� x��ǥ
	int arrY = posY - GBOARD_ORIGIN_Y;					// 1 ���� �����   ������ �� y��ǥ
	if (gameBoardInfo[arrY][arrX] == BLOCK)				// ����� ����
		return BLOCK;
	else if (gameBoardInfo[arrY][arrX] == BULLET)		// ���� źȯ�� ����
		return BULLET;
	else if (gameBoardInfo[arrY][arrX] == EMPTY)		// �������
		return EMPTY;
	else if (gameBoardInfo[arrY][arrX] == PC)			// PC�� ����
		return PC;
	else if (gameBoardInfo[arrY][arrX] == NPC)			// NPC�� ����
		return NPC;
	else if (gameBoardInfo[arrY][arrX] == PCBULLET)		// PC�� źȯ�� ����
		return PCBULLET;
}

void Init()
{
	wave = 1;
	life = 5;
	score = 0;
	//num = 0;

	CurPcX = GBOARD_WIDTH+GBOARD_ORIGIN_X, CurPcY = GBOARD_HEIGHT / 2;
	DirPcX = 1, DirPcY = 0;

	for (int i = 0; i < GBOARD_HEIGHT + 1; i++)
		for (int x = 0; x < GBOARD_WIDTH + 2; x++)
			gameBoardInfo[i][x] = EMPTY;

	BulletH = GetNode(); BulletT = GetNode();
	BulletH->next = BulletT; BulletT->prev = BulletH;
}

void InitGame()														// ���� ���� �κ�
{
	int enemynumber = life * WEIGHTLIFE + wave * WEIGHTWAVE;		// wave�� life�� ����ġ ��ŭ NPC ����
	EnemyList enemylist;											// NPC ����Ʈ ����
	int cnt = 0;													// �ӽ÷� ������ �����Ű������ ���� ����

	MakeEnemy(&enemylist, enemynumber);								// NPC����
	SetEnemy(&enemylist);											// NPC ����
	while (enemylist.numberofexistEnmey > 0)						// NPC�� ����  0�̵Ǹ� break;
	{ 
		TextColor(15);
		PrintEnemy(&enemylist);										// NPC���
		ProcessKeyInput(&enemylist);								// Ű�Է� �κ�
	}
	DeleteEnemy(&enemylist);
}
void CallNextWave()															// ���� WAVE�� ȣ���ϱ� ���� �Լ�
{
	ResetGameBoard();
	wave++;
	PrintStatus();
	CurPcX = GBOARD_WIDTH + GBOARD_ORIGIN_X, CurPcY = GBOARD_HEIGHT / 2;	// PC ��ġ �ʱ�ȭ
	DirPcX = 1, DirPcY = 0;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("��");
}

/*
* �ۼ���: ������
void Render(int x, int y)
{
	HDC hDC;			// ����ȭ���� DC(Device Context) �ڵ鰪�� �޴� ����
	HDC hMemDC;			// �̹����� ���� DC �ڵ鰪�� �޴� ����
	static HDC hBackDC;	// �ĸ� ����
	HBITMAP hBitmap, hOldBitmap, hBackBitmap;		// �̹��� ��Ʈ���� �ڵ鰪�� ������ ����
	BITMAP Bitmap;									// �ڵ鰪���κ��� ���� ���� ��Ʈ�� ����ü
	RECT WindowRect;								// ���� �������� Rect���� ����
	GetWindowRect(hWnd, &WindowRect);

	hDC = GetDC(hWnd);								// ���� �������� DC �ڵ鰪�� ����
	hBackDC = CreateCompatibleDC(hDC);				// hDC�� ȣȯ�Ǵ� DC�� �޸𸮿� ����� �ڵ鰪 ��ȯ
	hMemDC = CreateCompatibleDC(hDC);

	hBackBitmap = CreateCompatibleBitmap(hDC, WindowRect.right, WindowRect.bottom);		// ��Ʈ�� �޸𸮸� �Ҵ�, �ڵ� ��ȯ
	hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);							// ��Ʈ���� �׸� ��
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));							// ��Ʈ���� �ε�, �ڵ��� ��ȯ, resource.h�� define�� ���ҽ��� �ε�
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);										// ��Ʈ���� ũ�⸦ �ޱ� ���� ��Ʈ�� ����ü�� ��Ʈ�� �ڵ�� ���� ����
	SelectObject(hMemDC, hBitmap);														// �о�� ��Ʈ�� ���ҽ��� �޸� DC�� ����

	BitBlt(hBackDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);		// hMemDC�� �̹����� hBackDC�� ���ϴ� ��ġ�� ����
	BitBlt(hDC, x, y, x + Bitmap.bmWidth, y + Bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);	// hBackDC�� �̹����� ȭ������ ����

	DeleteObject(SelectObject(hBackDC, hBackBitmap));									// �޸𸮿� ������Ʈ ����
	DeleteObject(hBitmap);
	DeleteDC(hBackDC);
	DeleteDC(hMemDC);

	ReleaseDC(hWnd, hDC);
}
*/