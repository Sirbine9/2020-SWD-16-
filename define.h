#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
/*-------------------------GameBoard Value------------------------*/

#define GBOARD_WIDTH 40							// GameBoard�� �ʺ�
#define GBOARD_HEIGHT 40						// GameBoard�� ����

#define GBOARD_ORIGIN_X 4						// GameBoard�� ����� x ��ǥ
#define GBOARD_ORIGIN_Y 2						// GameBoard�� ����� y ��ǥ

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

#define WEIGHTLIFE 1							// NPC���� ����ġ=> ������
#define WEIGHTWAVE 1							// NPC���� ����ġ=> WAVE���

#define BULLET 2								// GameBoard�� NPC�� ���������� ��������� �ǹ�
#define EMPTY 0									// GameBoard�� �ش� ������ �̵��������� �ǹ�
#define BLOCK 1									// GameBoard�� �ش� ������ ���������� �ǹ�
#define PCBULLET 4								// GameBoard�� PC�� ������ �ǹ�
#define PC 5									// GameBoard�� PC���ǹ�
#define NPC 6									// GameBoard�� NPC�� �ǹ�

/*-------------------------Global Variable------------------------*/

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];		// GameBoard�� �� ���ο��� PC�� NPC�� �浹 �˻縦 ���� ������ �迭
int wave;													// ���� ���� ��������
int life;													// ���
int score;													// ȹ���� ����
//int num;													// GameBoard�� ��¦��¦�ϰ� �ϴ� ����
int CurPcX, CurPcY;											// ���� PC�� ��ǥ
int DirPcX, DirPcY;											// BULLET�� ������ �����ִ� ����
/*
* Render �Լ� ���� ���� ����
static HWND hWnd;											// �ܼ� ������ â�� �ڵ鰪
static HINSTANCE hInst;										// ���α׷��� �ν��Ͻ� �ڵ鰪
*/

/*-------------------------Global Variable------------------------*/


/*--------------------------Structures----------------------------*/

typedef struct Bullet 
{
	int CurBulletX;				// ���� Bullet�� x ��ǥ
	int CurBulletY;				// ���� Bullet�� y ��ǥ
	int TargetX;
	int TargetY;
	struct Bullet *next;		// ���� Bullet
	struct Bullet *prev;		// ���� Bullet
}bullet;

typedef struct Enemy
{
	int type;					// ���� Ÿ��.
	int x, y;					// ���� ��ǥ 
	int dest;
	int life;					// ���� ü��
	int speed;
}Enemy;

typedef struct EnemyList
{
	int numberofEnemy;			// NPC�� �� ��
	int numberofexistEnmey;		// ��ȿ�� NPC�� ��
	Enemy* enemy;
}EnemyList;

bullet *BulletH, *BulletT;

/*--------------------------Structures----------------------------*/