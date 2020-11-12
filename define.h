#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
/*-------------------------GameBoard Value------------------------*/

#define GBOARD_WIDTH 40							// GameBoard의 너비
#define GBOARD_HEIGHT 40						// GameBoard의 높이

#define GBOARD_ORIGIN_X 4						// GameBoard를 출력할 x 좌표
#define GBOARD_ORIGIN_Y 2						// GameBoard를 출력할 y 좌표

/*-------------------------GameBoard Value------------------------*/

/*----------------------Keyboard ASCII Value----------------------*/

#define LEFT 97
#define RIGHT 100
#define UP 119
#define DOWN 115
#define LKEY 75
#define RKEY 77
#define UPKEY 72
#define DOWNKEY 80
#define SPACE 32

/*----------------------Keyboard ASCII Value----------------------*/

#define WEIGHTLIFE 1							// NPC등장 가중치=> 목숨비례
#define WEIGHTWAVE 1							// NPC등장 가중치=> WAVE비례

#define BULLET 2								// GameBoard에 NPC의 공격정보가 담겨있음을 의미
#define EMPTY 0									// GameBoard에 해당 구역은 이동가능함을 의미
#define BLOCK 1									// GameBoard에 해당 구역은 막혀있음을 의미
#define PCBULLET 4								// GameBoard에 PC의 공격을 의미
#define PC 5									// GameBoard에 PC를의미
#define NPC 6									// GameBoard에 NPC를 의미

/*-------------------------Global Variable------------------------*/

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];		// GameBoard와 그 내부에서 PC와 NPC의 충돌 검사를 위한 이차원 배열
int wave;													// 진행 중인 스테이지
int life;													// 목숨
int score;													// 획득한 점수
//int num;													// GameBoard를 반짝반짝하게 하는 변수
int CurPcX, CurPcY;											// 현재 PC의 좌표
int DirPcX, DirPcY;											// BULLET의 방향을 정해주는 변수
/*
* Render 함수 관련 전역 변수
static HWND hWnd;											// 콘솔 윈도우 창의 핸들값
static HINSTANCE hInst;										// 프로그램의 인스턴스 핸들값
*/

/*-------------------------Global Variable------------------------*/


/*--------------------------Structures----------------------------*/

typedef struct Bullet 
{
	int CurBulletX;				// 현재 Bullet의 x 좌표
	int CurBulletY;				// 현재 Bullet의 y 좌표
	int TargetX;
	int TargetY;
	struct Bullet *next;		// 다음 Bullet
	struct Bullet *prev;		// 이전 Bullet
}bullet;

typedef struct Enemy
{
	int type;					// 적의 타입.
	int x, y;					// 적의 좌표 
	int dest;
	int life;					// 적의 체력
	int speed;
}Enemy;

typedef struct EnemyList
{
	int numberofEnemy;			// NPC의 총 수
	int numberofexistEnmey;		// 유효한 NPC의 수
	Enemy* enemy;
}EnemyList;

bullet *BulletH, *BulletT;

/*--------------------------Structures----------------------------*/