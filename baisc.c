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
// 2020.11.08 작성자: 차명진

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

int DetectCollision(int posX, int posY)					// 해당 좌표의 유형에 따라 다른 값 출력
{ 
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;			// 0 현재 블록의 게임판 내 x좌표
	int arrY = posY - GBOARD_ORIGIN_Y;					// 1 현재 블록의   게임판 내 y좌표
	if (gameBoardInfo[arrY][arrX] == BLOCK)				// 블록이 존재
		return BLOCK;
	else if (gameBoardInfo[arrY][arrX] == BULLET)		// 적의 탄환이 존재
		return BULLET;
	else if (gameBoardInfo[arrY][arrX] == EMPTY)		// 비어있음
		return EMPTY;
	else if (gameBoardInfo[arrY][arrX] == PC)			// PC가 존재
		return PC;
	else if (gameBoardInfo[arrY][arrX] == NPC)			// NPC가 존재
		return NPC;
	else if (gameBoardInfo[arrY][arrX] == PCBULLET)		// PC의 탄환이 존재
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

void InitGame()														// 게임 실행 부분
{
	int enemynumber = life * WEIGHTLIFE + wave * WEIGHTWAVE;		// wave와 life의 가중치 만큼 NPC 생성
	EnemyList enemylist;											// NPC 리스트 생성
	int cnt = 0;													// 임시로 게임을 진행시키기위한 변수 선언

	MakeEnemy(&enemylist, enemynumber);								// NPC생성
	SetEnemy(&enemylist);											// NPC 설정
	while (enemylist.numberofexistEnmey > 0)						// NPC의 수가  0이되면 break;
	{ 
		TextColor(15);
		PrintEnemy(&enemylist);										// NPC출력
		ProcessKeyInput(&enemylist);								// 키입력 부분
	}
	DeleteEnemy(&enemylist);
}
void CallNextWave()															// 다음 WAVE를 호출하기 위한 함수
{
	ResetGameBoard();
	wave++;
	PrintStatus();
	CurPcX = GBOARD_WIDTH + GBOARD_ORIGIN_X, CurPcY = GBOARD_HEIGHT / 2;	// PC 위치 초기화
	DirPcX = 1, DirPcY = 0;
	SetCurrentCursorPos(CurPcX, CurPcY);
	printf("★");
}

/*
* 작성자: 고현종
void Render(int x, int y)
{
	HDC hDC;			// 실제화면의 DC(Device Context) 핸들값을 받는 변수
	HDC hMemDC;			// 이미지를 담을 DC 핸들값을 받는 변수
	static HDC hBackDC;	// 후면 버퍼
	HBITMAP hBitmap, hOldBitmap, hBackBitmap;		// 이미지 비트맵의 핸들값을 저장할 변수
	BITMAP Bitmap;									// 핸들값으로부터 얻어올 실제 비트맵 구조체
	RECT WindowRect;								// 현재 윈도우의 Rect값을 얻어옴
	GetWindowRect(hWnd, &WindowRect);

	hDC = GetDC(hWnd);								// 현재 윈도우의 DC 핸들값을 얻어옴
	hBackDC = CreateCompatibleDC(hDC);				// hDC와 호환되는 DC를 메모리에 만들어 핸들값 반환
	hMemDC = CreateCompatibleDC(hDC);

	hBackBitmap = CreateCompatibleBitmap(hDC, WindowRect.right, WindowRect.bottom);		// 비트맵 메모리를 할당, 핸들 반환
	hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);							// 비트맵을 그릴 곳
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));							// 비트맵을 로드, 핸들을 반환, resource.h에 define된 리소스를 로드
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);										// 비트맵의 크기를 받기 위해 비트맵 구조체를 비트맵 핸들로 부터 생성
	SelectObject(hMemDC, hBitmap);														// 읽어온 비트맵 리소스를 메모리 DC에 선택

	BitBlt(hBackDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);		// hMemDC의 이미지를 hBackDC의 원하는 위치로 복사
	BitBlt(hDC, x, y, x + Bitmap.bmWidth, y + Bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);	// hBackDC의 이미지를 화면으로 복사

	DeleteObject(SelectObject(hBackDC, hBackBitmap));									// 메모리와 오브젝트 해지
	DeleteObject(hBitmap);
	DeleteDC(hBackDC);
	DeleteDC(hMemDC);

	ReleaseDC(hWnd, hDC);
}
*/