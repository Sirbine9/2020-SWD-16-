#pragma once
#include"define.h"

int NpcDetectCollision(Enemy* in);								// NPC가 움직일때 충돌검사
int PcDetectCollision(int posX, int posY);						// PC가 움직일때 충돌검사
int NpcBulletDetectCollision(int poxX, int posY);				// NPCBULLET의 충돌검사 
int PcBulletDetectCollision(int posX, int posY, EnemyList* in); // PCBULLET의 충돌검사